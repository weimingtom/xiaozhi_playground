/ # ls /sys/class/leds/
ls /sys/class/leds/
[1;36msunxi_led0b[m  [1;36msunxi_led0g[m  [1;36msunxi_led0r[m

D:\adt-bundle-windows-x86-20140624\sdk\platform-tools>adb shell
/ # echo 10 > /sys/class/leds/sunxi_led0g/brightness
echo 10 > /sys/class/leds/sunxi_led0g/brightness
/ # echo 0 > /sys/class/leds/sunxi_led0g/brightness
echo 0 > /sys/class/leds/sunxi_led0g/brightness
/ # echo 10 > /sys/class/leds/sunxi_led0r/brightness
echo 10 > /sys/class/leds/sunxi_led0r/brightness
/ # echo 10 > /sys/class/leds/sunxi_led0g/brightness
echo 10 > /sys/class/leds/sunxi_led0g/brightness
/ # echo 10 > /sys/class/leds/sunxi_led0b/brightness
echo 10 > /sys/class/leds/sunxi_led0b/brightness
/ #

关闭的话echo 0即可
------------------



gaviarhandhelda_patch_20230828.tar (1).7z

	ledc_pins_a: ledc@0 {
		pins = "PE5";
		function = "ledc";
		drive-strength = <10>;
	};

	ledc_pins_b: ledc@1 {
		pins = "PE5";
		function = "gpio_in";
	};
	
---

https://d1s.docs.aw-ol.com/hard/hard_3boarduse/

RGB LED
开发板板载了 3 颗 RGB LED，型号是 WS2812。



可以通过下列命令点亮 RGB LED 灯


echo 255 > /sys/class/leds/sunxi_led0r/brightness
echo 255 > /sys/class/leds/sunxi_led1g/brightness
echo 255 > /sys/class/leds/sunxi_led2b/brightness


也可以关闭 RGB LED 灯


echo 0 > /sys/class/leds/sunxi_led0r/brightness
echo 0 > /sys/class/leds/sunxi_led1g/brightness
echo 0 > /sys/class/leds/sunxi_led2b/brightness


GPADC 按键
开发板板载了 4 颗按键，使用 GPADC 连接主控，可以运行 getevent 并按下按键查看键值。


getevent


GPIO 点灯
可以使用下面的命令点亮这一颗 LED 灯


echo 139 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio139/direction
echo 1 > /sys/class/gpio/gpio139/value


---

https://bbs.aw-ol.com/topic/3650/gaviar-handheld-小志掌機/30?page=1


---

https://bbs.aw-ol.com/assets/uploads/files/1687619296554-小志掌机原理图-gaviar-handheld-v1.0_2023-06-09.pdf

WS2812C-2020-V1
PE5

--


https://cloud.tencent.com/developer/article/2192216

全志D1-H Tina Linux LEDC开发指南
发布于 2022-12-13 17:39:29
8090
举报
介绍全志LEDC 驱动的使用方法，方便LEDC 驱动维护和应用开发。

1.2 适用范围

表1-1: 适用产品列表

产品名称：D1-H

内核版本： Linux-5.4

驱动文件：leds-sunxi.c

1.3 相关人员

LEDC 驱动和应用开发人员。

2 模块介绍

2.1 相关术语说明

表2-1: 术语说明表

术语说明

LED Light Emitting Diode

LEDC Light Emitting Diode Controller

2.2 源码结构说明

本模块借助于标准Linux LED 子系统。其代码路径为：

<div>tina/lichee/linux5.4/drivers/leds/
</div>
复制
led-core.c：为led子系统的核心文件。
ledtrigger-xxx.c：为trigger相关的文件。
leds-sunxi.c：LEDC驱动实现代码。
leds-sunxi.h：定义全志LEDC驱动数据结构。
复制
2.3 模块配置说明

2.3.1 内核配置

在tina 根目录下，执行makekernel_menuconfig，配置路径如下：

Device Drivers
└─>LED_Support
└─>LED support for Allwinner platforms
复制
操作图示：

ledc 配置界面
ledc 配置界面
图2-1: ledc 配置界面

如果需要用到trigger 的话，需要选择相对应的配置项。配置路径如下：

Device Drivers
└─>LED_Support
└─>LED Trigger support
复制
操作图示：

trigger 配置界面
trigger 配置界面
trigger 配置界面

2.3.2 DTS 配置

2.3.2.1 DTS 路径

通过cdts 命令可跳转到平台dts 路径：

tina/lichee/linux-5.4/arch/riscv/boot/dts/sunxi/sun20iw1p1.dtsi
复制
tina/device/config/chips/d1-h/configs/nezha/linux/board.dts
复制
ledc: ledc@2008000 {
#address-cells = <1>;
#size-cells = <0>;
compatible = "allwinner,sunxi-leds";
reg = <0x0 0x02008000 0x0 0x400>;
interrupts = <GIC_SPI 20 IRQ_TYPE_LEVEL_HIGH>;
interrupt-names = "ledcirq";
clocks = <&ccu CLK_LEDC>, <&ccu CLK_BUS_LEDC>;
clock-names = "clk_ledc", "clk_cpuapb";
dmas = <&dma 42>, <&dma 42>;
dma-names = "rx", "tx";
resets = <&ccu RST_BUS_LEDC>;
reset-names = "ledc_reset";
status = "disabled";
};
复制
板级dts:

&pio {
....................//省略
ledc_pins_a: ledc@0 {
pins = "PC0";
function = "ledc";
drive-strength = <10>;
};
ledc_pins_b: ledc@1 {
pins = "PC0";
function = "gpio_in";
};
...................//省略
};
&ledc {
pinctrl-names = "default", "sleep";
pinctrl-0 = <&ledc_pins_a>;
pinctrl-1 = <&ledc_pins_b>;
led_count = <1>;
output_mode = "GRB";
reset_ns = <84>;
t1h_ns = <800>;
t1l_ns = <320>;
t0h_ns = <300>;
t0l_ns = <800>;
wait_time0_ns = <84>;
wait_time1_ns = <84>;
wait_data_time_ns = <600000>;
status = "okay";
};
复制
3 接口描述

3.1 内部接口

LEDC 驱动主要的内部接口如下表所示：

sunxi_ledc_set_length： 设置LED 的数量

sunxi_ledc_set_output_mode： 设置LEDC 的输出模式（R、G、B 的排布顺序）

sunxi_ledc_set_cpu_mode： 设置CPU 的传输模式

sunxi_ledc_set_dma_mode： 设置DMA 的传输模式

sunxi_ledc_enable： 使能LEDC

sunxi_ledc_trans_data： 设置LEDC 相关寄存器；将RGB 数据搬到LEDCFIFO中，启动LEDC

sunxi_ledc_set_time： 模块初始化时设置reset_ns、t1h_ns、t1l_ns 等的时间

sunxi_ledc_reset 将transmitted_data： 置为0；释放系统资源；对LEDC做soft reset 操作

sunxi_set_led_brightness： 设置LED 亮度，范围为0~255

sunxi_register_led_classdev： 模块初始化时注册led_classdev 设备

sunxi_unregister_led_classdev： 模块卸载时注销led_classdev 设备

3.2 外部接口

3.2.1 brightness 调节说明

每个RGB LED 在/sys/class/leds 目录下对应有3 个led_classdev 设备目录，分别如下：

/sys/class/leds/sunxi_led[n]r
/sys/class/leds/sunxi_led[n]g
/sys/class/leds/sunxi_led[n]b
复制
其中n 表示LED 的编号，n 最小值为0。

完整全志D1-H Tina Linux LEDC开发指南请到一牛网论坛下载

https://bbs.16rd.com/thread-598793-1-1.html

本文系转载，前往查看

如有侵权，请联系 cloudcommunity@tencent.com 删除。

------------------
https://bbs.16rd.com/thread-598793-1-1.html



 全志D1-H Tina Linux LEDC开发指南[复制链接]

498416
 已绑定手机
楼主
 发表于 2022-12-13 09:45 | 只看该作者  来自 广东深圳
介绍全志LEDC 驱动的使用方法，方便LEDC 驱动维护和应用开发。

1.2 适用范围
表1-1: 适用产品列表
产品名称：D1-H
内核版本： Linux-5.4
驱动文件：leds-sunxi.c

1.3 相关人员
LEDC 驱动和应用开发人员。

2 模块介绍
2.1 相关术语说明
表2-1: 术语说明表
术语说明
LED Light Emitting Diode
LEDC Light Emitting Diode Controller

2.2 源码结构说明
本模块借助于标准Linux LED 子系统。其代码路径为：

<div>tina/lichee/linux5.4/drivers/leds/
</div>
复制代码
led-core.c：为led子系统的核心文件。
ledtrigger-xxx.c：为trigger相关的文件。
leds-sunxi.c：LEDC驱动实现代码。
leds-sunxi.h：定义全志LEDC驱动数据结构。
复制代码

2.3 模块配置说明
2.3.1 内核配置
在tina 根目录下，执行make kernel_menuconfig，配置路径如下：
Device Drivers
└─>LED_Support
└─>LED support for Allwinner platforms
复制代码
操作图示：

图2-1: ledc 配置界面

如果需要用到trigger 的话，需要选择相对应的配置项。配置路径如下：
Device Drivers
└─>LED_Support
└─>LED Trigger support
复制代码
操作图示：

trigger 配置界面

2.3.2 DTS 配置
2.3.2.1 DTS 路径
通过cdts 命令可跳转到平台dts 路径：
tina/lichee/linux-5.4/arch/riscv/boot/dts/sunxi/sun20iw1p1.dtsi
复制代码
tina/device/config/chips/d1-h/configs/nezha/linux/board.dts
复制代码
ledc: ledc@2008000 {
#address-cells = <1>;
#size-cells = <0>;
compatible = "allwinner,sunxi-leds";
reg = <0x0 0x02008000 0x0 0x400>;
interrupts = <GIC_SPI 20 IRQ_TYPE_LEVEL_HIGH>;
interrupt-names = "ledcirq";
clocks = <&ccu CLK_LEDC>, <&ccu CLK_BUS_LEDC>;
clock-names = "clk_ledc", "clk_cpuapb";
dmas = <&dma 42>, <&dma 42>;
dma-names = "rx", "tx";
resets = <&ccu RST_BUS_LEDC>;
reset-names = "ledc_reset";
status = "disabled";
};
复制代码
板级dts:
&pio {
....................//省略
ledc_pins_a: ledc@0 {
pins = "PC0";
function = "ledc";
drive-strength = <10>;
};
ledc_pins_b: ledc@1 {
pins = "PC0";
function = "gpio_in";
};
...................//省略
};
&ledc {
pinctrl-names = "default", "sleep";
pinctrl-0 = <&ledc_pins_a>;
pinctrl-1 = <&ledc_pins_b>;
led_count = <1>;
output_mode = "GRB";
reset_ns = <84>;
t1h_ns = <800>;
t1l_ns = <320>;
t0h_ns = <300>;
t0l_ns = <800>;
wait_time0_ns = <84>;
wait_time1_ns = <84>;
wait_data_time_ns = <600000>;
status = "okay";
};
复制代码

3 接口描述
3.1 内部接口
LEDC 驱动主要的内部接口如下表所示：
sunxi_ledc_set_length： 设置LED 的数量
sunxi_ledc_set_output_mode： 设置LEDC 的输出模式（R、G、B 的排布顺序）
sunxi_ledc_set_cpu_mode： 设置CPU 的传输模式
sunxi_ledc_set_dma_mode： 设置DMA 的传输模式
sunxi_ledc_enable： 使能LEDC
sunxi_ledc_trans_data： 设置LEDC 相关寄存器；将RGB 数据搬到LEDC FIFO中，启动LEDC
sunxi_ledc_set_time： 模块初始化时设置reset_ns、t1h_ns、t1l_ns 等的时间
sunxi_ledc_reset 将transmitted_data： 置为0；释放系统资源；对LEDC做soft reset 操作
sunxi_set_led_brightness： 设置LED 亮度，范围为0~255
sunxi_register_led_classdev： 模块初始化时注册led_classdev 设备
sunxi_unregister_led_classdev： 模块卸载时注销led_classdev 设备

3.2 外部接口
3.2.1 brightness 调节说明
每个RGB LED 在/sys/class/leds 目录下对应有3 个led_classdev 设备目录，分别如下：
/sys/class/leds/sunxi_led[n]r
/sys/class/leds/sunxi_led[n]g
/sys/class/leds/sunxi_led[n]b
复制代码
其中n 表示LED 的编号，n 最小值为0。


-----------------------------





