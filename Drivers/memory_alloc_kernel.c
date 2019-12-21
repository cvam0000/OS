#include<linux/slab.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

#define size 10

MODULE_LICENSE("GPL");

int alloc_init(void)
{
	void *pointer;
	pointer = kmalloc(size, GFP_KERNEL);  
	
	/*
 	 * When we call the Kmalloc we are going to get only certain predefined, fixed 
	 * size of memory in physical memory unit. each byte of the array is smaller than page size.
	 * The smallest allocation that kmalloc() can handles is as big as 32 or 64 byte and this is Achitecture dependent.
	 *
	 * $ getconf PAGESIZE or $ getconf PAGE_SIZE you can find the page size using these commands 
	 *
	 * if you want to know the max size of the page of your kernel you should visit 
	 * /usr/src/linux/include/linux/slab.h
	 *
	 *The first argument is in kmalloc func is for the @size of the array 
	 *The second argument is a @flag defined at /usr/src/linux/include/linux/slab.h.
	 *@flag is the type of memory which we are going to allocate.
	 *
	 * Counter function to free the memory is Kfree() that receives the area of allocated memory by Kalloc(). Also this function does not suspend any process.

		 

	
		
	*/

	if(!pointer)
	{	printk(KERN_ALERT"he he nahi mili jagh");
		//report error 
	}

	printk(" I got : %zu Byes", ksize(pointer));
	kfree(pointer);
	return 0;
}




void alloc_exit(void)
{
	printk(KERN_ALERT"Time to exit with clear the memory");
	
}

module_init(alloc_init);
module_exit(alloc_exit);
