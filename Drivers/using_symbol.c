#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
int simple_module_func(void);
__init int init_a_module(void)
{
	printk( KERN_ALERT " Hello world im going to initilised this utility and after i release the RAM ");
	simple_module_func();
	return 0;
}


void cvam_exit_kernel(void)
{
	printk( KERN_ALERT " Time to leave the planet kernel ");

}

module_init(init_a_module);
module_exit(cvam_exit_kernel);

