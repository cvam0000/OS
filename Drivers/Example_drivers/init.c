#include<linux/init.h>
#include<linux/module.h>

int __init__(void)
{
	printk(" Im inside your kernel now ");
	return 0;
}

module_init(__init__);
