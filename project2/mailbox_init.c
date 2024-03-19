#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE0(mailbox_init) {
    // Get ID for node
    unsigned long random_number = generate_random_number();
    
    printk(KERN_INFO "Random Number: %lu\n", random_number);
   
    // Insert first node into BST
    root = insert_node(root, random_number);
    
    // If memory allocation error
    if(root == NULL){
        printk(KERN_ERR "Error: Root node is NULL\n");
        return -ENOMEM;
    }
    
    printk(KERN_INFO "Random Number Again: %lu\n", root->id);
    
    in_order_traversal(root);
    printk("hello world!\n");
   
    return 0;
}
