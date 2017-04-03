# si47xx_radio_linux
软件环境：linux4.1.36  arm-linux-gcc 4.3.2

实现功能：自动搜台，上一台， 下一台， 音量大小控制，保存设置到文件，断电开机后自动恢复，之前收音状态。

用法：
先加载驱动
insmod si47xx/si47xx.ko
insmod si47xx/si47xx_dev.ko

在执行 FM 测试程序

si47xx/radio_fm

功能

#t 测试模式接收996M 交通台

#s 自动搜台

#n 下一台

#p 上一台

#+ 加音量

#- 减音量

其它的 AM SW 功能，以后在实现。

模块及接线介绍及我的博客
http://www.cnblogs.com/ningci/p/6659104.html


