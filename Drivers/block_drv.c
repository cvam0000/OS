#include<linux/fs.h>
#include<linux/genhd.h> //provides the function to register and alocate disk 


# define MAJOR		240
# define NAME		"cvam_block_drv"
# define MINOR          1
# define NR_SECTOR      1024

static struct my_block_dev              // Recommended to use to store all the important elements describing about the block device .
{
	struct genhd *gd; // The gendisk structure
	spinlock_t lock ; // for mutual exclusion 
	struct request_queue *queue // for device request queue 
	
}dev;

/*
 * struct gendisk structure
 * has all the information about a disk  
 * obtained after calling the alloc_disk() function 
 * has such fields 
 *  --major no 
 *  --minor no / first minor (if partition is possible than only be the minor no > 1 
 *  -- disk name as it appears in /proc/partitions and /sys/block 
 *  --fops operation associalted with the disk 
 *  --queue of request 
 *  --capacity , disk capacity in 512 byte setors . initialized using set_capacity() function.
 *  --private_data , a pointer to private data.
 *  
 */


static int create_block_device(struct my_block_dev *dev)
{ 	
	dev->gd = alloc_disk( MINOR ); //Allocate the disk at gd

	if(!dev->gd)
	{		printk( kERN_NOTICE "Allocate disc failure");
			return -ENOMEM;
	}
	
	dev->gd->major = MAJOR;
	dev->gd->first_minor = 0;
	dev->gd->fops = &my_block_ops;
	dev->gd->queue =dev->queue;
	dev->gd->privte_data =dev;
	snprintf(dev->gd->disk_name , 32 , "myblock");
	set_capacity(dev->gd , NR_SECTORS );

	add_disk(dev->gd); // Adding the disk ( now disk is active for the operations )

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
		create_block_device(&dev); // create_block_device is called after the fully initialization of the driver and when it is ready to respond to a register disk.
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


