#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE0(mailbox_init) {
    // Initialize the spinlock
    rwlock_init(&mailbox_lock);
    
    write_lock(&mailbox_lock);
    
    // Get ID for node
    unsigned long random_number = generate_random_number();
    
   
    // Insert first node into BST
    root = insert_node(root, random_number);
    
    // If memory allocation error
    if(root == NULL){
        printk(KERN_ERR "Error: Root node is NULL\n");
        write_unlock(&mailbox_lock);
        return -ENOMEM;
    }
    
    //printk(KERN_INFO "Random Number Again: %lu\n", root->id);
    
    //in_order_traversal(root);
    //printk("hello world!\n");
    
    
    
    
    printk(KERN_INFO "Mailbox initiated with first node with id %lu\n", random_number);
    
    
    write_unlock(&mailbox_lock);
    return 0;
}
