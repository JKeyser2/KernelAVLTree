#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE1(mailbox_delete, unsigned long, id) {
    write_lock(&mailbox_lock);
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
   
    // If the node exists
    if(node != NULL){
        // Attemps to remove oldest message from queue
        long functionReturn = delete_oldest(node->queue);
        // If queue was already empty
        if(functionReturn == -1){
            printk(KERN_INFO "Queue was already empty\n");
            write_unlock(&mailbox_lock);
            return -2;
        // If queue was not already empty
        }else{
            printk(KERN_INFO "Oldest message deleted\n");
            write_unlock(&mailbox_lock);
            return 0;
        }
    // If the node does not exist
    }else{
        printk(KERN_INFO "Node does not exist\n");
        write_unlock(&mailbox_lock);
        return -1;
    }

}
