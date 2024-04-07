#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(mailbox_send, unsigned long, id, unsigned char __user *, msg, long, len) {
    write_lock(&mailbox_lock);
    // Checks if the node already exists
    struct tree_node* node = find_node(root, id);
   
    // If the node does exist
    if(node != NULL){
    	// Validate user space pointer
    	if(!access_ok(msg,len)){
    	    printk(KERN_INFO "Invalid user space pointer\n");
    	    write_unlock(&mailbox_lock);
    	    return -EFAULT;
    	}
    	
    	
    	// Allocate kernel space buffer for message
    	unsigned char* kernel_msg = kmalloc(len + 1, GFP_KERNEL);
    	// If memory allocation failed
    	if(!kernel_msg){
    	    printk(KERN_ERR "Failed to allocate memory for the message\n");
    	    write_unlock(&mailbox_lock);
    	    return -ENOMEM;
    	}
    
    
    	// Copy message from user space to kernel space
    	if(copy_from_user(kernel_msg, msg, len)){
    	    printk(KERN_ERR "Failed to copy message from user space\n");
    	    kfree(kernel_msg);
    	    write_unlock(&mailbox_lock);
    	    return -EFAULT;
    	}
    	
    	
    	// Null-terminate the string
    	kernel_msg[len] = '\0';
    	
    	
    	
    
        enqueue(node->queue, kernel_msg);
        printk(KERN_INFO "Successfully added messsage to end of queue: %s\n", kernel_msg);
        
        //kfree(kernel_msg);
        write_unlock(&mailbox_lock);
        return 0;
    // If the node does not exist
    }else{
        printk(KERN_INFO "Node does not exist\n");
        write_unlock(&mailbox_lock);
        return -1;
    }




}
