#include<linux/init.h>
#include<linux/module.h>


int cvam_module_init(void)
{
	printk(KERN_ALERT " Hello world %s im inside your kernel \n",__FUNCTION__);
	return 0;

	}

void cvam_module_exit(void)

{
	printk(KERN_ALERT " Have to leave the kernel %s ", __FUNCTION__);

}

module_init(cvam_module_init);
module_exit(cvam_module_exit);

