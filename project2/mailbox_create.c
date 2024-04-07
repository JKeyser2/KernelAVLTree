#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE1(mailbox_create, unsigned long, id) {
    write_lock(&mailbox_lock);
    
    // Checks if the node already exists
    struct tree_node* node = find_node(root, id);
   
    // If the node does not exist
    if(node == NULL){
        // Delete the node
        insert_node(root, id);
        
        printk(KERN_INFO "Node inserted with id %lu\n", id);
        //printk(KERN_INFO "\n");
        //in_order_traversal(root);
        //printk(KERN_INFO "\n");
        write_unlock(&mailbox_lock);
        return 0;
    // If the node does exist
    }else{
        printk(KERN_INFO "Node already exists\n");
        write_unlock(&mailbox_lock);
        return -1;
    }



}
