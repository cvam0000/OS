#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CVAM");
MODULE_VERSION("0.1");

dev_t dev=MKDEV(235,0); // dev is the dev_t structure variable for major and minor no.

static int static_init_no(void)
{
    register_chrdev_region(dev,1,"ohmyarch_dev");
    printk(KERN_INFO "Major = %d Minor = %d \n", MAJOR(dev),MINOR(dev));
    printk(KERN_ALERT "Module Inserted Successfully");
    return 0;
}

static void exit_driver(void)
{
    unregister_chrdev_region(dev,1);
    printk(KERN_INFO "Time to leave the planet kernel");
}

module_init(static_init_no);
module_exit(exit_driver);
