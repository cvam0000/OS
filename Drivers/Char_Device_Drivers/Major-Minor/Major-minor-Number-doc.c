/*
Introduction

What is so special about the character drivers ?
For byte oriented operation majority of the drivers are char device drivers for example serial drivers , Audio drivers ,
camera drivers and basic I/O drivers.Also we cant back and forth the char in the file.in fact all the drivers that
neither storage nor network device drivers are some type of char device drivers.

Steps to access a hardware device.
1. Application will open the device file which is created by device drivers.
2. Then this device file will find the corresponding device using major and minor number.
3. Then this Device Driver will talk to hardware device.

One of the main feature of the Linux Kernel is to abstract and handling of the devices.To Linux every thing is a file
and all the hardware devices act like a file which can be manipulated using system calls, for example to write to a
hard disk you write to a file, To read the inputs from the keyboard you need to read a file .

Driver will create a special file for every hardware device, to communicate to the hardware using those files.(Device
Files )


MAJOR and MINOR Numbers 
The Linux Kernel represent char and block device driver as pair of numbers <major> and <minor>
<major> Number identifies the driver associated with the device and major numbers can be shared by the multiple device
drivers. See cat /proc/devices how major numbers are assigned on running instance.

As many Device Drives share a Major number so we have to assign different numbers to the devices which are using same major
number to distinguish individual physical or logical devices .So this is the <MINOR> number.

Allocation of Major and Minor no.
tow ways of allocation 
1. Statically Allocated
2. Dynamically Allocated

If we want to set particular available major number to your driver, you can use this method this will allocate the
major no if it is available . Otherwise it won't.

int register_chrdev_region(dev_t first , unsigned int count , char *name);
first // The beginning no of the range we want 
count // The total number of contiguous device no we are requesting.

if(count is too large)
    it could spill over the next major no, but it'll work as long as the number range we request is available.

name // the device name which is associate with the number range.it'll appear in /proc/devices.

the function register_chrdev_region will return 0 if the mission is successful if not it will give some negative error
code.

dev_t structure :
it is typedef of __kernel_dev_t which is again typedef u32 which is again a typedef of unsigned int which holds 32 bit.
here 12 bits set aside for major no and 20 for minor no .


MKDEV(int major , int minor) //create a dev_t structure variable for the major and minor no.

MAJOR(dev_t dev);
MINOR(dev_t dev);
// all these macros are defined in <linux/kdev_t.h>


Dynamically Allocating:
If we don't want to fix the major and minor no, we can use this method. This method will allocate the available major number
dynamically. 

int alloc_chrdev_region(dev_t *dev, unsigned int minor, unsigned int count, char *name);

dev // Output only parameter. On success it holds the first number in the allocate range.
minor // first Minor number, Usually 0.
count // total requested number of contiguous device.
*/

















