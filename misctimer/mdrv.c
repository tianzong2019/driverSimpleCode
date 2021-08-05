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
#include <linux/uaccess.h>

static struct timer_list tm;
struct timeval oldtv;
static struct fasync_struct *button_async;
static unsigned char key_val = 9;

void callback(unsigned long arg)
{
    struct timeval tv;
    char *strp = (char*)arg;
    
    printk("%s: %lu, %s\n", __func__, jiffies, strp);

    do_gettimeofday(&tv);
    printk("%s: %ld, %ld\n", __func__,
        tv.tv_sec - oldtv.tv_sec,        //与上次中断间隔 s
        tv.tv_usec- oldtv.tv_usec);        //与上次中断间隔 ms

	kill_fasync (&button_async, SIGIO, POLL_IN);

    oldtv = tv;
    tm.expires = jiffies+1*HZ;    
    add_timer(&tm);        //重新开始计时
}

static int dmisc_open(struct inode *inode, struct file *filp)
{
    printk ("driver in: %s\n", __func__);
	init_timer(&tm);    //初始化内核定时器
	do_gettimeofday(&oldtv);        //获取当前时间
    tm.function= callback;            //指定定时时间到后的回调函数
    tm.data    = (unsigned long)"hello world";        //回调函数的参数
    tm.expires = jiffies+1*HZ;        //定时时间
    add_timer(&tm);        //注册定时器
    return 0;
}

static int dmisc_release(struct inode *inode, struct file *filp)
{
    printk ("driver in: %s\n", __func__);
	del_timer(&tm);        //注销定时器
    return 0;
}

static ssize_t dmisc_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int ret = 0;
    printk ("driver in: %s\n", __func__);
	ret = copy_to_user(buf, &key_val, 1);
    return 1;
}

static ssize_t dmisc_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	int ret = 0;
    printk ("driver in: %s\n", __func__);
	ret = copy_from_user(&key_val, buf, count);
    return 1;
}

static long dmisc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk ("driver in: %s\n", __func__);
    return 1;
}

static int fifth_drv_fasync (int fd, struct file *filp, int on)  
{  
    printk("driver: fifth_drv_fasync\n");  
    //初始化/释放 fasync_struct 结构体 (fasync_struct->fa_file->f_owner->pid)  
    return fasync_helper (fd, filp, on, &button_async);  
}

static struct file_operations dmisc_fops =
{
    .owner            = THIS_MODULE,
    .open            = dmisc_open,
    .read            = dmisc_read,
    .write            = dmisc_write,
    .compat_ioctl        = dmisc_ioctl,
    .release            = dmisc_release,
	.fasync  =  fifth_drv_fasync,
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