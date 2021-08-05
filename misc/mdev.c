#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

static void mem_release(struct device *dev)
{
     return;
}
static struct platform_device mem_device =
{
    .name = "arm.mali.c71",
    .id = -1,
    .dev.release = mem_release,
};
static int mem_init(void)
{
    printk("mem_init \n");
    return platform_device_register(&mem_device);
}
static void mem_exit(void)
{
    printk("mem_exit \n");
    platform_device_unregister(&mem_device);
    return;
}
module_init(mem_init);
module_exit(mem_exit);
MODULE_INFO(intree, "Y");
MODULE_LICENSE("GPL v2");