#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <asm/irq.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>
#include <linux/platform_device.h>

static int dmisc_open(struct inode *inode, struct file *filp)
{
    printk ("driver in: %s\n", __func__);
    return 0;
}
static int dmisc_release(struct inode *inode, struct file *filp)
{
    printk ("driver in: %s\n", __func__);
    return 0;
}
static ssize_t dmisc_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk ("driver in: %s\n", __func__);
    return 1;
}
static ssize_t dmisc_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    printk ("driver in: %s\n", __func__);
    return 1;
}
static long dmisc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk ("driver in: %s\n", __func__);
    return 1;
}
static struct file_operations dmisc_fops =
{
    .owner            = THIS_MODULE,
    .open            = dmisc_open,
    .read            = dmisc_read,
    .write            = dmisc_write,
    .compat_ioctl        = dmisc_ioctl,
    .release            = dmisc_release
};
static struct miscdevice misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "arm.mali.c71",
    .fops = &dmisc_fops,
};
static int hello_probe(struct platform_device *pdev)
{
    int ret = misc_register(&misc);
	if (ret < 0)
		return -EFAULT;
    printk("match ok \n");
    return 0;
}
static  int hello_remove(struct platform_device *pdev)
{
    printk("hello_remove \n");
    misc_deregister(&misc);
    return 0;
}
static struct platform_driver hello_driver =
{
    .probe = hello_probe,
    .driver.name = "arm.mali.c71",
    .remove = hello_remove,     
};
static int hello_init(void)
{
    printk("hello_init \n");
    return platform_driver_register(&hello_driver);
}
static void hello_exit(void)
{
    printk("hello_exit \n");
    platform_driver_unregister(&hello_driver);
    return;
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_INFO(intree, "Y");
MODULE_LICENSE("GPL v2");