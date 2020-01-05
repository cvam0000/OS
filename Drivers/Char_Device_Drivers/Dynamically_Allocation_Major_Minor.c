#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CVAM");
MODULE_VERSION("0.1");

dev_t dev=0; 

static int static_init_no(void)
{
    if(alloc_chrdev_region(&dev,0,1,"ohmyarch_dev")<0)
    {
        printk(KERN_ALERT "NOT ABLE TO ALLOCATE THE MAJOR NO FOR THE DEVICE");
        return -1;
    }
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
