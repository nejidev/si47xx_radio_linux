#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/sysfs.h>

static unsigned short const addr_list[] = {0x11, I2C_CLIENT_END};

static struct i2c_client *si47xx_client;

static int si47xx_dev_init(void)
{
	struct i2c_adapter *i2c_ada;
	struct i2c_board_info si47xx_info;
	memset(&si47xx_info, 0, sizeof(struct i2c_board_info));
	strlcpy(si47xx_info.type, "si47xx", I2C_NAME_SIZE);
	
	i2c_ada = i2c_get_adapter(0);
	//i2c_new_probed_device 会检查 设备是否存在
	si47xx_client = i2c_new_probed_device(i2c_ada, &si47xx_info, addr_list, NULL);
	i2c_put_adapter(i2c_ada);
	if(si47xx_client)
	{
		return 0;
	}
	else
	{
		printk("no si47xx i2c device\n");
		return -1;
	}
}

static void si47xx_dev_exit(void)
{
	i2c_unregister_device(si47xx_client);
}

module_init(si47xx_dev_init);
module_exit(si47xx_dev_exit);
MODULE_LICENSE("GPL");

