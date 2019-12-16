#include<linux/fs.h>
#include<linux/genhd.h> //provides the function to register and alocate disk 


# define MAJOR		240
# define NAME		"cvam_block_drv"
# define MINOR          1
static struct my_block_dev
{
	struct genhd *gd;

}dev;


static int create_block_device(struct my_block_dev *dev)
{ 	
	dev->gd = alloc_disk( MINOR ); //Allocate the disk at gd 
	add_disk(dev->gd); 	       //Adding the disk 	
}	


static int block_init(void)
{
	int status = register_clkdev( MAJOR , NAME ); // from kernel version 4.9 onward there is no need of this function 
	if(status < 0)
	{
		printk( KERN_ALERT " Unable to register the Block driver " );
		return -EBUSY ; // Device or resource is busy 
	}
	else
	{	printk( KERN_ALERT " Driver loaded sucessfully " );
		create_block_device(&dev);
	}
return 0;

}

static delete_block_device(struct my_block_dev *dev)
{
	if(dev->gd)
		del_gendisk(dev->gd);

}


static void blok_exit(void)
{
	unregister_blkdev( MAJOR , NAME ); // also unmount the disk 
	delete_block_device(&dev);
}


