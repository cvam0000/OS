#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>


MODULE_LICENSE("GPL");

int count = 1;
module_param(count , int , 0); // name , type , permission  

__init int init_a_module(void)
{
	int index=0;
	for(index=0;index< count ; index ++)
		printk( KERN_ALERT " Hello world" );
	return 0;
}


void cvam_exit_kernel(void)
{
	printk( KERN_ALERT " Time to leave the planet kernel ");

}

module_init(init_a_module);
module_exit(cvam_exit_kernel);

