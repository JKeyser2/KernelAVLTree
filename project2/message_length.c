#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE1(message_length, unsigned long, id) {
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
   
    // If the node exists
    if(node != NULL){
        // Gets length of oldest message
        long message_length = get_length_oldest(node->queue);
        // If queue was empty
        if(message_length == -1){
            printk(KERN_INFO "Queue was empty\n");
            return -2;
        // If queue wasn't empty
        }else{
            printk(KERN_INFO "Message length: %ld\n", message_length);
            return message_length;
        }
    // If the node does not exist
    }else{
        printk(KERN_INFO "Node does not exist\n");
        return -1;
    }
}

