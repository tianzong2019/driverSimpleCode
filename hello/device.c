#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
 
#define prki(fmt,arg...) printk(KERN_INFO "%s %d " fmt, __FUNCTION__, __LINE__, ##arg)
 
static void hello_release(struct device *dev)
{
	prki("hello_release\n");
	return ;
}
 
static struct platform_device hello_device=
{
	.name = "arm.mali.c71",
    .id = -1,
    .dev.release = hello_release,
};
 
static int hello_init(void)
{
	prki("hello_init\n");
	return platform_device_register(&hello_device);
}
 
static void hello_exit(void)
{
	prki("hello_exit\n");
	platform_device_unregister(&hello_device);
	return;
}
 
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
