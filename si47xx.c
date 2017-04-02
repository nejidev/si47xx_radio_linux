#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/sysfs.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-samsung.h>
#include <mach/hardware.h>
#include <plat/gpio-cfg.h>

#include "si47xx.h"

//主设备号
static int major;
//类描述为创建设备使用
static struct class *cls;
//i2c client 发送接收数据使用
static struct i2c_client *si47xx_client;

//i2c table 和 board 中进行比较 相同调用 probe
static struct i2c_device_id si47xx_idtable[] = {
	{"si47xx", 0},{}
};

//全局使用发送和接收
static unsigned char cmd[6];

/* 硬件相关函数 方便 移值 */
static void si47xx_handware_reset(void)
{
	//Camera 中的 EINT20 中断引脚 GPG12 用做复位
	//低电平复位 需要保持300ns
	s3c_gpio_cfgpin(S3C2410_GPG(12), S3C2410_GPIO_OUTPUT);
	ndelay(300);
	gpio_set_value(S3C2410_GPG(12), 0);
	ndelay(300);
	gpio_set_value(S3C2410_GPG(12), 1);
	ndelay(300);
}
static void si47xx_handware_write(unsigned char *buf, int count)
{
	i2c_master_send(si47xx_client, buf, count);
	mdelay(300);
}

static void si47xx_handware_read(unsigned char *buf, int count)
{
	i2c_master_recv(si47xx_client, buf, count);
	mdelay(300);
}

static void si47xx_fm_mode(void)
{
	cmd[0] = SI47xx_POWER_UP;
	cmd[1] = 0xd0;
	cmd[2] = 0x05;
	si47xx_handware_write(cmd, 3);

	//设置FM去加重为中国制式50US
	cmd[0] = SI47xx_SET;
	cmd[1] = 0x00;
	cmd[2] = SI47xx_FM_DEEMPHASIS >> 8;
	cmd[3] = SI47xx_FM_DEEMPHASIS & 0xff;
	cmd[4] = 0x00;
	cmd[5] = 0x01;
	si47xx_handware_write(cmd, 6);	
}

static int si47xx_fm_serach(void)
{
	int frequency = 0;
	cmd[0] = SI47xx_FM_SEEK_START;
	cmd[1] = 0<<2 | 1<<3; //向上搜索 搜到108后就停止
	si47xx_handware_write(cmd, 2);

	//读取搜台状态
	do{
		si47xx_fm_tune_status(cmd);
	} //cmd0 搜台中断位 cmd1 搜台到了最高处
	while((! (cmd[0] & (1<<7))) && (! (cmd[1] & (1<<7))));
	frequency = (cmd[1] & (1<<7)) ? 0 : cmd[2]<<8 | cmd[3];
	return frequency;
}

static void si47xx_fm_tune_status(unsigned char *buf)
{
	cmd[0] = SI47xx_FM_TUNE_STATUS;
	//cmd[1] = 0;//1<<1 | 1<<0; //清除 搜到台 中断位 继续搜台
	
	cmd[1] = 1<<1 | 1<<0; //清除 搜到台 中断位 继续搜台
	si47xx_handware_write(cmd, 2);
	//读取状态 频率 信号强度
	si47xx_handware_read(cmd, 6);
}

static void si47xx_fm_tune(int frequency)
{
	cmd[0]= SI47xx_FM_TUNE_FREQ;
	cmd[1]= 0x00;
	//例 10240 对应 102.4
	cmd[2] = frequency >> 8;    //写入高字节
	cmd[3] = frequency & 0xff; //写入低字节
	cmd[4]= 0x00;
	si47xx_handware_write(cmd, 5);
}

static void si47xx_am_mode(void)
{
	unsigned char cmd[6];
	cmd[0] = SI47xx_POWER_UP;
	cmd[1] = 0xd1;
	cmd[2] = 0x05;
	si47xx_handware_write(cmd, 3);
}

static int si47xx_am_serach(void)
{
	int frequency = 0;
	return frequency;
}

static void si47xx_am_tune(int frequency)
{
	
}

static void si47xx_vol(int val)
{
	cmd[0] = SI47xx_SET;
	cmd[1] = 0x00;
	cmd[2] = SI47xx_RX_VOLUME >>8 ;
	cmd[3] = SI47xx_RX_VOLUME & 0xff;
	cmd[4] = 0x00;
	cmd[5] = (val > 0x3f) ? 0x3f : val;
	si47xx_handware_write(cmd, 6);
}

static void si47xx_mute(int mute)
{
	
}

static void si47xx_reset(void)
{
	si47xx_handware_reset();
}

static void si47xx_power_on(void)
{
	
}

static void si47xx_power_off(void)
{
	
}

//io ctrl 命令
#define IOCTL_CMD_RESET      101
#define IOCTL_CMD_POWER_ON   102
#define IOCTL_CMD_POWER_OFF  103
#define IOCTL_CMD_FM_MODE    104
#define IOCTL_CMD_AM_MODE    105
#define IOCTL_CMD_MUTE       106
#define IOCTL_CMD_VOL        107
#define IOCTL_CMD_FM_TUNE    108
#define IOCTL_CMD_AM_TUNE    109
#define IOCTL_CMD_FM_SERACH  110
#define IOCTL_CMD_AM_SERACH  111

static long si47xx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	switch(cmd){
	case IOCTL_CMD_RESET: si47xx_reset(); 
		break;
	case IOCTL_CMD_POWER_ON: si47xx_power_on(); 
		break;
	case IOCTL_CMD_POWER_OFF: si47xx_power_off(); 
		break;
	case IOCTL_CMD_FM_MODE: si47xx_fm_mode(); 
		break;
	case IOCTL_CMD_AM_MODE: si47xx_am_mode(); 
		break;
	case IOCTL_CMD_MUTE: si47xx_mute((int)arg); 
		break;
	case IOCTL_CMD_VOL: si47xx_vol((int)arg); 
		break;
	case IOCTL_CMD_FM_TUNE: si47xx_fm_tune((int)arg); 
		break;
	case IOCTL_CMD_AM_TUNE: si47xx_am_tune((int)arg); 
		break;
	case IOCTL_CMD_FM_SERACH: ret = si47xx_fm_serach(); 
		break;	
	default:break;
	}
	return ret;
}

//当程序调用open时执行 si47xx reset
static int si47xx_open(struct inode *inode, struct file *file)
{
	si47xx_reset();
	return 0;
}

static struct file_operations si47xx_ops = {
	.owner = THIS_MODULE,
	.open = si47xx_open,
	.unlocked_ioctl = si47xx_ioctl,
};

//当idtab中比较相同以后调用这个
static int si47xx_probe(struct i2c_client *client,const struct i2c_device_id *dev)
{
	//设给全局变量
	si47xx_client = client;
	//创建字库设备
	cls   = class_create(THIS_MODULE, "si47xx");
	major = register_chrdev(0, "si47xx", &si47xx_ops);
	device_create(cls, NULL, MKDEV(major, 0), NULL, "si47xx");
	return 0;
}

static int si47xx_remove(struct i2c_client *client)
{
	device_destroy(cls, MKDEV(major, 0));
	class_destroy(cls);
	unregister_chrdev(major, "si47xx");
	return 0;
}

static struct i2c_driver si47xx_drv = {
	.driver = {
		.name  = "si47xx",
		.owner = THIS_MODULE,
	},
	.probe  = si47xx_probe,
	.remove = si47xx_remove,
	.id_table = si47xx_idtable,
};

static int si47xx_init(void)
{
	//需要 RST 后才可以使用 I2C 协议
	si47xx_handware_reset();
	i2c_add_driver(&si47xx_drv);
	return 0;
}

static void si47xx_exit(void)
{
	i2c_del_driver(&si47xx_drv);
}

module_init(si47xx_init);
module_exit(si47xx_exit);
MODULE_LICENSE("GPL");

