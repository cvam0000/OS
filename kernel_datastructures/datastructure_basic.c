/* Linux Kernel is one of the biggest project of the time and i love linux because it is free and opensource.So anyone
 * can change the source according to his/her.So there are lots of datastructures are predefined so Kernel developers
 * can reuse that code and not "ROLE YOUR OWN " solutions . 

1. Doubly linklist 
2. Queues 
3. Maps
4. Binary Trees

we can conclude this on the basis of Algorithm complexity to scale to support ever larger inputs.


Link List
Elements are not occupy at contigious region of memory unlike an static array. This enables the the management o fa
varying number of elements unknown at compile time.

Lets define a simple link list using a structure.

struct a_node{
    
    struct a_node * next; // A struct node type pointer for pointing next element.
    struct a_node * prev; // A struct node type pointer for pointing previous element.
    int data;             // A variable to store the data of the node.

};

* but linux kernel Apporach is different. Instead of turning a structure into linked list, the linux aproach is to embed
a link list node in the structure ..
in the old days there were multiple implimentations of the linklist . A single powerful API was needed at that time to
reduce the code base, during the kernel developement series 2.1 the official API was introduced .

so  the embed a link list in the structure means 

struct list_head {
    struct list_head *next , *prev;
};

which is declare in <linux/types.h>

lets do an example.

struct pid_list
{
    pid_t pid;
    struct list_head pointer;
};
 in this struct pointer.next points the next element and pointer.prev points the previous element.now this gets
 better.Kernel provides lots of pre implemented  methods for eg list_add() which adds new node to the existing list and
 there are more than 40 other generic methods are defined in <linux/list.h> they accept only the list_head structures   


// Initialization of a node for a list 

static int add_pid(pid_t pid)
{
    struct pid_list *pointer = kmalloc(sizeof *pointer , GFP_KERNEL ); 
    //allocate the memory to the node.
    if(!pointer)
        return -ENOMEM;
    pointer->pid = pid ;
    list_add(pointer , &cvam_list)
    //read this what is sentinel of the list.
    return 0;
}

// Declare a head pointer to point the link list as whole 
static LIST_HEAD(cvam_list); // it is also a list_head type


