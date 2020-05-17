# virt_input

#### 介绍
完成一个虚拟的input设备驱动，该设备驱动可实现案件操作

#### 软件架构
软件架构说明
虚拟input device驱动实现说明
	此处我们实现的input device，主要支持如下功能：
	1. 我们实现EV_KEY类型的事件，主要是实现key的上报；
	2. 因是虚拟设备，因此我们通过向sysfs的属性文件写入数据，模拟按键事件的发生（即模拟按键中断），而在sysfs的store接口中，我们通过调用input_report_key，实现事件的分发；
	3. 在应用层通过打开/dev/input/eventX文件，并通过读取事件，监控按键事件；
	4. 我们在platform driver的probe接口中，完成input device的注册、sysfs属性文件的注册操作。
数据结构
如下即为虚拟input device定义的数据结构，其中key表示key id，key_value用于记录key值
	typedef struct virtual_input_info_s
	{
	    struct input_dev *input_dev;
	    int key_value;
	    int key;
	
	}virtual_input_info_t;
	


#### 安装教程

1.  make
2.  make install
3.  在 ./images中即为生成的驱动及应用程序

#### 使用说明

1.  insmod virtual_input_platform_dev.ko
2.  insmod virtual_input_dev.ko
3. ./usr_test
4. 重新打开一个终端，然后进入/sys/devices/platform/virtual_input_dev.0目录下，可查看到文件vinput_key
5.向vinput_key中写入数据如echo 1 > vinput_key。则usr_test监控到vinput_key的值变化，即模拟了按键的按下动作。
6.也可以结合模拟i2c 控制器、i2c设备，通过修改i2c设备的sysfs文件，从而触发虚拟按键的按下操作（可参考https://gitee.com/jerry_chg/virt_input实现）。


#### 参与贡献



#### 码云特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5.  码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
