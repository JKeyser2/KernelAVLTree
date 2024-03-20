#include "the_functions.h"

#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE0(mailbox_shutdown) {
    free_bst(root);
    
    root = NULL;
   
    return 0;
}
