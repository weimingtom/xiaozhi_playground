riscv d1 framebuffer, С��alphaͨ��
https://www.iteye.com/blog/weimingtom-1113103
https://bbs.elecfans.com/jishu_2228992_1_1.html



����������һ�£���â����MQ������ȫ־F133-A������4.3����Ļ�̼���������framebuffer�������ǿ��еģ��Ժ��о�������ϸ˵������������ӵ��������1����bootlin��riscv gcc��������̬���ӵ�elf������mq�����У�gcc�������-static���أ���2��ͨ��adb push���͵�/tmpĿ¼��Ȼ��chmod +x��Ȼ�����У�3��framebuffer��/dev/fb0����32λ���أ��ֽڸ�ʽ��BGRA��������ֽ�����0��3�������У�������A�ֽڣ�͸��ͨ������ø�ֵΪ255�������0����ʾ�ɺ�ɫ�����������debian��ͬ�������������ἰ��͸��ͨ��������255������⣺����ζ�D1��߸�������frambuffer���в����ء���â���������ṩ�Ĺ̼���������directfb�Ĳ��Գ��򣬵��������tina�Դ��������ߺ����ӽ�ȥ�ġ�������ֲ��SDL��LVGL�������۾����ϸ��


/dev/input/mice��/dev/psaux
https://www.iteye.com/blog/weimingtom-1113103


https://commandnotfound.cn/linux/1/209/halt-����
sudo apt-get install sysvinit-core
sudo apt-get install systemd-sysv <-���������
/sbin/reboot
/sbin/halt
/sbin/shutdown

unable to open mouse
/dev/psauxû��Ȩ��
su; ִ��
����su; chown wmt:wmt /dev/psaux
����su; chown wmt /dev/psaux
������һ�£���debian 11�Ϲ���/dev/psaux��SDL�������������ʵû��ô�򵥡������qemu�Ļ�����Ϊֻ��һ���û�root��������ʲô���⣬��debian 11�����һ�������ÿ������֮��/dev/psaux��Ȩ�޶�����root�����ֱ��ִ��SDL�����ӻ���ʾunable to open mouse��������������֣�һ������su����sudoִ��SDL���̣���һ�־��ǳ���������chown myusername /dev/psaux����ÿ������������ȥroot


