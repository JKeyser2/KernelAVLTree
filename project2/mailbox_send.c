#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(mailbox_send, unsigned long, id, unsigned char __user *, msg, long, len) {
    // Checks if the node already exists
    struct tree_node* node = find_node(root, id);
   
    // If the node does exist
    if(node != NULL){
        enqueue(node->queue, msg);
        printk(KERN_INFO "Successfully added messsage to end of queue\n");
        return 0;
    // If the node does not exist
    }else{
        printk(KERN_INFO "Node does not exist\n");
        return -1;
    }




}
