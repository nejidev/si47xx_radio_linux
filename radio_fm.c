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

#define BAROD_BUF_SIZE (1024*1024)
int si47xx_fd, barod_fd;
//保存配置信息和频道信息
unsigned char  *barod_buf;
//频道信息
unsigned short *barod_ch;

//配置信息
struct si47xx_cfg{
	int max_ch;
	int ch;
	int vol;
};

struct si47xx_cfg *cfg;

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

void set_ch(int ch)
{
	fm_tune(barod_ch[ch]);
		
	//读取电台信息显示给用户
	printf("ch: %d %.1f Mhz \n", ch, barod_ch[ch]/100.0);
}

void serach()
{
	int frequency;
	//设定开始搜索频率
	fm_tune(8800);
	//配置信息最大频道清0
	cfg->max_ch = 0;
	while(1)
	{
		frequency = ioctl(si47xx_fd, IOCTL_CMD_FM_SERACH, 0);
		if(0 < frequency)
		{
			printf("serach: %.1f Mhz\n", frequency/100.0);
			//保存频率信息
			barod_ch[cfg->max_ch] = frequency;
			cfg->max_ch++;
		}
		else
		{
			break;
		}
	}
	printf("serach done find %d radio\n", cfg->max_ch);
}

void mute()
{
	static int is_mute=0;
	ioctl(si47xx_fd, IOCTL_CMD_MUTE, is_mute%2);
	is_mute++;
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

	struct stat barod_stat;
	
	//打印使用信息
	welcome();

	//打开设备
	si47xx_fd = open("/dev/si47xx", O_RDWR);
	if(0 > si47xx_fd)
	{
		printf("cat't open si47xx \n");
		return 0;
	}

	//打开或创建一个保存频率的文件
	barod_fd = open("./barod_info.txt", O_RDWR | O_CREAT, 0777);

	//如果文件大小为0就填充
	if(-1 == fstat(barod_fd, &barod_stat))
	{
		printf("get barod_info stat err\n");
		return 0;
	}
	if(0 == barod_stat.st_size)
	{
		ftruncate(barod_fd, BAROD_BUF_SIZE+1024);
	}
	
	barod_buf = mmap(NULL, BAROD_BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, barod_fd, 0);
	if(barod_buf == MAP_FAILED)
	{
		printf("cat't mmap barod_buf \n");
		return 0;
	}

	//barod_buf = malloc(BAROD_BUF_SIZE);
	
	
	//读取配置信息
	cfg = (struct si47xx_cfg *)barod_buf;
	
	//读取频道配置信息
	barod_ch = (unsigned short *)(barod_buf + sizeof(struct si47xx_cfg));
	
	if(0 == barod_stat.st_size)
	{
		memset(barod_buf, 0, BAROD_BUF_SIZE);
		cfg->ch  = 0;
		cfg->vol = 35;
	}
	
	//初始化FM模式
	fm_mode();
	mute();

	//读取保存的电台
	set_ch(cfg->ch);
	set_vol(cfg->vol);

	while('q' != (cmd = getchar()))
	{
		switch(cmd)
		{
			case 't': test();              break;
			case 's': serach();            break;
			case '+': set_vol(cfg->vol+=5); break;
			case '-': set_vol(cfg->vol-=5); break;
			case 'm': mute();               break;
			case 'p': set_ch(--cfg->ch);    break;
			case 'n': set_ch(++cfg->ch);    break;
			case 'h': welcome();            break;
		}
	}

	munmap(barod_buf, BAROD_BUF_SIZE);
	close(si47xx_fd);
	close(barod_fd);
	return 0;
}

