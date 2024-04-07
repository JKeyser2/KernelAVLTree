#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE0(mailbox_shutdown) {
    write_lock(&mailbox_lock);
    
    free_bst(root);
    
    root = NULL;
    
    printk(KERN_INFO "All mailboxes destroyed\n");
    
    write_unlock(&mailbox_lock);
   
    return 0;
}
