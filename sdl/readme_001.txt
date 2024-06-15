riscv d1 framebuffer, 小心alpha通道
https://www.iteye.com/blog/weimingtom-1113103
https://bbs.elecfans.com/jishu_2228992_1_1.html



我昨晚试了一下，在芒果派MQ（基于全志F133-A，基于4.3寸屏幕固件）上运行framebuffer程序大概是可行的，以后研究好再详细说，大概是这样子的情况：（1）用bootlin的riscv gcc工具链静态链接的elf可以在mq上运行（gcc必须加上-static开关）（2）通过adb push推送到/tmp目录，然后chmod +x，然后运行（3）framebuffer（/dev/fb0）是32位像素，字节格式是BGRA（如果按字节数组0到3索引排列），而且A字节（透明通道）最好赋值为255，如果是0会显示成黑色（这个可能与debian不同）。网上有人提及到透明通道必须是255这个问题：《如何对D1哪吒开发板的frambuffer进行测试呢》。芒果派作者提供的固件中甚至有directfb的测试程序，但不清楚是tina自带还是作者后来加进去的。等我移植完SDL和LVGL后再讨论具体的细节


/dev/input/mice和/dev/psaux
https://www.iteye.com/blog/weimingtom-1113103


https://commandnotfound.cn/linux/1/209/halt-命令
sudo apt-get install sysvinit-core
sudo apt-get install systemd-sysv <-建议用这个
/sbin/reboot
/sbin/halt
/sbin/shutdown

unable to open mouse
/dev/psaux没有权限
su; 执行
或者su; chown wmt:wmt /dev/psaux
或者su; chown wmt /dev/psaux
我试了一下，在debian 11上关于/dev/psaux的SDL鼠标输入问题其实没那么简单。如果是qemu的话，因为只有一个用户root，不会有什么问题，但debian 11会出现一种情况，每次重启之后/dev/psaux的权限都会变成root，如果直接执行SDL的例子会提示unable to open mouse。解决方法有两种，一种是用su或者sudo执行SDL例程，另一种就是常见的做法chown myusername /dev/psaux，但每次重启都会变回去root


