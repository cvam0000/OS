#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/list.h>


struct cvam_list{
    int data;
    struct list_head list;
};

static LIST_HEAD(root);

static int add_node(int data)
{
    struct cvam_list *node= kmalloc(sizeof(struct cvam_list),GFP_KERNEL);
    if(!node)
        return -ENOMEM;
    node->data=data;
    list_add(node , &root);
       
    return 0;
}

static int _list_init(void)
{
    int a=10;
    add_node(a);
    printk(KERN_ALERT"Hello my first program to link list");
    return 0;
}

static void _list_exit(void)
{
    printk(KERN_ALERT"Time to leave the planet kernel");
}    
module_init(_list_init);
module_exit(_list_exit);




