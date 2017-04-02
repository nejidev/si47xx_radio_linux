#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

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

int si47xx_fd;

//当前频道号
int ch = 0;

void welcome()
{
	printf("/////////////////////////////////////////\n");
	printf("/ Power By: Ning Ci                     /\n");
	printf("/ Press key 's' To Auto Serach All Band /\n");
	printf("/ Press key 'm' To Redio Mute           /\n");
	printf("/ Press key 'p' To Set Redio Prev CH    /\n");
	printf("/ Press key 'n' To Set Redio Next CH    /\n");
	printf("/ Press key 'q' To Quit Close Radio     /\n");
	printf("/////////////////////////////////////////\n");
}

void fm_mode()
{
	ioctl(si47xx_fd, IOCTL_CMD_FM_MODE, 0);
}

void fm_tune(int frequency)
{
	ioctl(si47xx_fd, IOCTL_CMD_FM_TUNE, frequency);
}

//最大值是63
void set_vol(int vol)
{
	ioctl(si47xx_fd, IOCTL_CMD_VOL, vol);
}

void serach()
{
	ioctl(si47xx_fd, IOCTL_CMD_FM_SERACH, 0);
}

//测试用
void test()
{
	fm_mode();
	fm_tune(10240);
	set_vol(30);
}

int main(int argc, char **argv)
{
	//控制命令
	char cmd;
	int vol = 40;
	
	//打印使用信息
	welcome();

	//打开设备
	si47xx_fd = open("/dev/si47xx", O_RDWR);
	if(0 > si47xx_fd)
	{
		printf("cat't open si47xx \n");
		return 0;
	}
	test();
	//读取保存的电台
	while('q' != (cmd = getchar()))
	{
		switch(cmd)
		{
			case 't': test();       break;
			case 's': serach();     break;
			case '+': set_vol(++vol);     break;
			case '-': set_vol(--vol);     break;
			/*
			case 'm': mute();       break;
			case 'p': set_ch(--ch); break;
			case 'n': set_ch(++ch); break;*/
			case 'h': welcome();    break;
		}
	}
	
	close(si47xx_fd);
	return 0;
}

