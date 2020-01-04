#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h> // for char driver support 





int cvam_open( struct inode *pinode , struct file *pfile)
{
	printk(KERN_ALERT " Opening the file");
	return 0;
}
ssize_t cvam_read( struct file *pfile ,char __user *buffer , size_t length, loff_t *offset)
{
	printk(KERN_ALERT " reading  the file");
	return 0;
}

ssize_t cvam_write( struct file *pfile ,const char __user *buffer , size_t lenght  , loff_t *offset)
{
	printk(KERN_ALERT " Writing the file");
	return lenght;
}

int cvam_close (struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT " closing the file");
	return 0;
}
	
struct file_operations operation_file=
{
	.owner = THIS_MODULE,
	.open = cvam_open,
	.read = cvam_read,
	.write = cvam_write,
	.release = cvam_close,

};


int cvam_char_drv_init(void)
	{
		printk(KERN_ALERT "initilized the driver");
		register_chrdev( 240 		      /*Major no*/,
				  "cvam_char_driver", /*Name of the driver*/
				  &operation_file     /* function pointer */	);

		return 0;
	}

void cvam_char_drv_exit(void)
	{
		printk(KERN_ALERT " Time to leave the planet kernel XD ");
		unregister_chrdev(240, "cvam_char_driver");
	}

module_init(cvam_char_drv_init);
module_exit(cvam_char_drv_exit);
