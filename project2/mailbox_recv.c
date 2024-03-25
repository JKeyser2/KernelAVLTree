#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(mailbox_recv, unsigned long, id, unsigned char __user *, msg, long, len) {
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
   
    // If the node exists
    if(node != NULL){
        unsigned char* message_string = dequeue(node->queue);
        
        printk(KERN_INFO "Kernel Message: %s\n", message_string);
        printk(KERN_INFO "Message Length: %zu\n", strlen(message_string));
        printk(KERN_INFO "msg: %s\n", msg);
        printk(KERN_INFO "msg Length: %zu\n", strlen(msg));
        printk(KERN_INFO "long len: %ld\n", len);
        
        // If there is a message in the queue of the node
        if(message_string != NULL){
            // Copy message from kernel space to user space
            if(copy_to_user(msg, message_string, len) != 0){
                printk(KERN_ERR "Failed to copy message to user space\n");
                kfree(message_string);
                return -EFAULT;
            }
        
            printk(KERN_INFO "Message (USER-SPACE): %s\n", msg);
            printk(KERN_INFO "Message: %s\n", message_string);
            //kfree(message_string);
            return strlen(msg);  
        // If the queue is empty
        }else{
            printk(KERN_INFO "Mailbox is empty\n");
            return -1;
        }
    // If the node does not exist
    }else{
    printk(KERN_INFO "Node does not exist\n");
    return -1;
    }





}
