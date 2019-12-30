#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>


/* Because Doubly Link List is often used in the Kernel dev so the Kernel API provides a unified way to defining and using list.
 * also kernel gives you RedBlack so dont worry you dont have to write your own list and tree 
 * struct list_head is consider as list node defined in include/linux/list.h
 * along with all the function which are useful to manipulate the list.
 *
 * in include/linux/types.h line 181
 * you can find the defination of the struct list_head
 *
 	struct list_head {
  		struct list_head *next , *prev;
  		};
 *
 *there are more than 40 pre-defined function for list manipulation in include/linux/list.h.
 *for eg. 
 	
	 list_add(struct list_head *new, struct list_head *head) //for a new entry after a specified head. it is a good option for stack implimentation  
	 {
	 	__list_add(new,head,head->next);
	 }

	 static inline void __list_add( // insert a node bw two known entries
	 				struct list_head *new,
					struct list_head *prev,
					struct list_head *next)

					{	if(!__list_add_valid(new,prev,next)  // just another predefined function which checks that the aruments are correct.
							return;

						next->prev = new ;
						new->next = next;
						new->prev = prev;
						WRITE_ONCE(prev->next,new);
					}	



 another eaxmple 

	static inline void list_add_tail ( // insert a node before the specified head.It is good option for queue implementation.
					   struct list_head *new;
				   	   struct list_head *head)
					   {
						__list_add(new,head->prev,head);
				           }		
 * there are many more functions have a look at /include/linux/list.h 
 *
 *
 */



struct pid_list{
	pid_t pid;
	struct list_head list;
	};

LIST_HEAD(cvam_list);  /* is used to declare the sentinel of a list */

static int add_pid(pid_t pid)
	{
	struct pid_list *pointer = kmalloc(sizeof *pointer ,GFP_KERNEL);
	if(!pointer)
		return -ENOMEM;
	pointer->pid=pid;
	list_add(pointer,&cvam_list); /* as we declare cvam_list as sentinel to the list */
	
	return 0;
	}


static int del_pid(pid_t pid)
	{
	struct list_head *tmp,*smp;
	struct pid_list *pointer;

	list_for_each_safe(smp,tmp,&cvam_list){
		pointer =list_entry(smp,struct pid_list , list);
		if(pointer->pid ==pid)
		{
			list_del(smp);
			kfree(pointer);
			return 0;
		}
	}	



static int  __list_init__(void)
{
	printk(KERN_ALERT"Lets do an example to create a list and use some function form list.h");
	struct pid_list a=1;
    add_pid(a);
	del_pid(a);
	return 0;

}	

static void  __list_exit__(void)
{
	printk(KERN_ALERT"Time To Leave The Planet Kernel");
}


module_init(__list_init__);
module_exit(__list_exit__);

