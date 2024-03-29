#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE1(message_count, unsigned long, id) {
    read_lock(&mailbox_lock);
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
   
    // If node exists
    if(node != NULL){
        long amount_messages = get_amount_messages(node->queue);
        printk(KERN_INFO "Ammount of messages: %ld\n", amount_messages);
        read_unlock(&mailbox_lock);
        return amount_messages;
    // If node does not exist
    }else{
        printk(KERN_INFO "Node does not exist\n");
        read_unlock(&mailbox_lock);
        return -1;
    }
}

