#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>



static int hello_probe(struct platform_device *pdev)
{
	printk("xiaobo match ok!\n");

	return 0;
}

static int hello_remove(struct platform_device *pdev)
{
	return 0;
}
 
static struct platform_driver hello_driver=
{
    .driver.name = "arm.mali.c71",
    .probe = hello_probe,
    .remove = hello_remove,
};
 
 
static int hello_init(void)
{
	printk("hello_init\n");
	
	return platform_driver_register(&hello_driver);
}
 
static void hello_exit(void)
{
	printk("hello_exit\n");
	platform_driver_unregister(&hello_driver);
	
	return;
}
 
 
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
