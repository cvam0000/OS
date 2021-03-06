/*
 * If want to get some info form kernel there are multiple ways to do it 
 * 1. System calls 
 * 2. proc File System and sysfs file system 
 * 3. netlink kernel Socket
 *
 * What we gonna do is Writing and understanding our own Proc file system . proc interface is being used by kernel to communicate with the userspace , take input from user space . There is a file at /proc/mounts 
 * which has a list of all the mounted file systems.
 * also it is used for communicating some information to the kernel space as well.
 * for eg.
 *
 * echo 1 > /proc/sysrqx-trigger // wiil print all the backtraces of all the CPUs
 * this file gives you ability to work differnetly  
 * 
 * if you want more dig out about proc file system 
 * https://www.kernel.org/doc/Documentation/filesystems/proc.txt
 *
 */

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/mm.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/types.h>
#include<linux/sched.h>

#define DATA_SIZE 1024 //lets keep 1024 byte data with us 
#define MY_PROC_ENTRY "cvam"
#define PATH_TO_PROC "/proc/cvam"
#define PERMISSION 0444
struct proc_dir_entry *proc_cvam;  // proc entry
int len;
char *msg;


/*Function to read from Kernel space*/

static ssize_t proc_read(struct file *fp , char *buf , size_t len , loff_t *off)
{
    static int finished=0;
    if(finished)
    {   finished=0;
        return 0;
    }
     finished=1;
     strcpy(buf, "Merry Chritmas \n");
     return strlen(buf);
}

/* Initialized File operations structure for reading operation */

static struct file_operations read_the_proc={
    .owner = THIS_MODULE ,
    .read  = proc_read,
    };


static int proc_init(void)
{   /* Proc create API */
    proc_cvam = proc_create( "proc_cvam" , PERMISSION , NULL ,&read_the_proc);
    if(proc_cvam == NULL)
    {
        printk(KERN_ALERT" Error could not initialize the Proc");
    }
    return 0;
}

static void proc_exit(void)
{
    remove_proc_entry("proc_cvam",NULL);
}

module_init(proc_init);
module_exit(proc_exit);


/*






/* function to write  to proc. using write system call 
 * what it does, writes data from a buffer declared by the user to a given device.
*/
/*
static ssize_t my_proc_write(struct file *flip, //
			     const char __user *buffer,
			     size_t count,
			     loff_t *pso)
{

}

*/


