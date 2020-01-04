#include<linux/init.h>
#include<linux/module.h>

void  __exit__(void)
{
	printk(" I can't Init but can escape ");

}

module_exit(__exit__);

