#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(mailbox_recv, unsigned long, id, unsigned char __user *, msg, long, len) {
    write_lock(&mailbox_lock);
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
   
    // If the node exists
    if(node != NULL){
        unsigned char* message_string = dequeue(node->queue);
        
        //printk(KERN_INFO "Kernel Message: %s\n", message_string);
        //printk(KERN_INFO "Message Length: %zu\n", strlen(message_string));
        //printk(KERN_INFO "msg: %s\n", msg);
        //printk(KERN_INFO "msg Length: %zu\n", strlen(msg));
        //printk(KERN_INFO "long len: %ld\n", len);
        
        
        // Gets length of message that was retreived
        size_t message_len = strlen(message_string);
        
        // If len is greater than length of message, change len to length of message
        if(message_len < len){
            len = message_len;
        }
        
        // If there is a message in the queue of the node
        if(message_string != NULL){
            // Copy message from kernel space to user space
            if(copy_to_user(msg, message_string, len) != 0){
                printk(KERN_ERR "Failed to copy message to user space\n");
                kfree(message_string);
                write_unlock(&mailbox_lock);
                return -EFAULT;
            }
        
            //printk(KERN_INFO "Message (USER-SPACE): %s\n", msg);
            //printk(KERN_INFO "Message: %s\n", message_string);
            //kfree(message_string);
            write_unlock(&mailbox_lock);
            return strlen(msg);  
        // If the queue is empty
        }else{
            printk(KERN_INFO "Mailbox is empty\n");
            write_unlock(&mailbox_lock);
            return -1;
        }
    // If the node does not exist
    }else{
    printk(KERN_INFO "Node does not exist\n");
    write_unlock(&mailbox_lock);
    return -1;
    }





}
