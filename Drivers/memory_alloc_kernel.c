#include<linux/slab.h>

pointer = kmalloc(sizeInBytes, GFP_KERNEL);
if(!pointer)
{
	//report error 
}
