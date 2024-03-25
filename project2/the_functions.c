#include "the_functions.h"



#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/random.h>





// Global variable for root of BST
struct tree_node* root = NULL;




// Generates a random number between 1 and a million
unsigned long generate_random_number(void){
    // For storing random number
    unsigned long random_number;
    
    // For getting random number
    get_random_bytes(&random_number, sizeof(random_number));
    
    // Return number that is between 1 and a million
    return (random_number % 1000000) + 1;

}





// For inserting node into the BST
struct tree_node* insert_node(struct tree_node* node, unsigned long id){
   
    // If BST is empty
    if(node == NULL){
        return create_node(id);
    }
   
   
    // If ID is smaller than current ID, go left
    if(id < node->id){
        node->left = insert_node(node->left, id);
    // If ID is larger than current ID, go right
    }else if(id > node->id){
        node->right = insert_node(node->right, id);
    }
   
    return node;
}






// Creates a new node
struct tree_node* create_node(unsigned long id){
    // Allocates memory
    struct tree_node* new_node = kmalloc(sizeof(struct tree_node), GFP_KERNEL);
    
    // If memory allocation error
    if(new_node == NULL){
        printk(KERN_ERR "Failed to allocate memory for new node\n");
        return NULL;
    }
   
   
    // Stores ID in new node
    new_node->id = id;
    // Creates a new queue in the node
    new_node->queue = create_queue();
    // Set left and right children to NULL for now
    new_node->left = NULL;
    new_node->right = NULL;
   
    // Return the newly created node
    return new_node;
}





// Creates a new queue
struct the_queue* create_queue(void){
    // Allocates memory
    struct the_queue* queue = kmalloc(sizeof(struct the_queue), GFP_KERNEL);
    
    // If memory allocation error
    if(queue == NULL){
        printk(KERN_ERR "Failed to allocate memory for new node\n");
        return NULL;
    }
   
   
    // Queue is empty
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}





// For displaying all of node IDs
void in_order_traversal(struct tree_node* node){
    if(node != NULL){
        // Left subtree
        in_order_traversal(node->left);
     
        printk(KERN_INFO "%lu ", node->id);
        struct queue_node* temp = node->queue->front;
        while(temp != NULL){
            // Gets and prints the message
            //unsigned char* data = temp->data;
            printk(KERN_INFO " %s ", temp->data);
   
            // Goes to next message
            temp = temp->next;
        }
     
        // Right subtree
        in_order_traversal(node->right);
    }
    
}   
    
    
    
// For freeing all memory of the BST
void free_bst(struct tree_node* root){
    // If tree is not empty
    if(root != NULL){
        // Free left subtree
        free_bst(root->left);
        // Free right subtree
        free_bst(root->right);
     
        // Free queue in current node
        free_queue(root->queue);
     
        // Free current node
        kfree(root);
    }

}





// For freeing memory of all the queues
void free_queue(struct the_queue* queue){
    // If queue is not empty
    if(queue != NULL){
        // Get head of queue
        struct queue_node* curr = queue->front;
        // For storing node to be deleted
        struct queue_node* temp;
     
        // Free each node in the queue
        while(curr != NULL){
            // Stash node to be deleted
            temp = curr;
            // Make the next node the new current
            curr = curr->next;
            // Free the node
            //free(temp->data);
            kfree(temp);
        }    
    }
   
    // Free the queue structure
    kfree(queue);
}  





// For finding a node
struct tree_node* find_node(struct tree_node* node, unsigned long id){
   // If we reached the end of the BST or found the node we are looking for
   if(node == NULL || node->id == id){
       return node;
   }
   // If ID is smaller than ID at current node, go left
   if(id < node->id){
       return find_node(node->left, id);
   // If ID is larger than ID at current node, go right
   }else{
       return find_node(node->right, id);
   }
   
}







// Adds message to end of queue
void enqueue(struct the_queue* queue, unsigned char* data){
    // Allocates memory for a new node
    struct queue_node* new_node = kmalloc(sizeof(struct queue_node), GFP_KERNEL);
    
    
    if(new_node == NULL){
        printk(KERN_ERR "Failed to allocate memory for new node\n");
        return;
    }
   
    // Stores message in node
    new_node->data = data;
    // Is last in queue
    new_node->next = NULL;
    
   
    // If queue is empty, node is front and rear
    if(queue->rear == NULL){
        queue->front = new_node;
        queue->rear = new_node;
    // If queue is not empty
    }else{
        // Adds node to end of queue
        queue->rear->next = new_node;
        // Identifies node as new rear
        queue->rear = new_node;
    }
}





// Gets how many messages are in the queue
long get_amount_messages(struct the_queue* queue){
    // If queue is empty
    if(queue->front == NULL){
        return 0;
    }
   
    // For storing how many messages are in the queue
    long amount_messages = 0;
   
    // Store front of the queue
    struct queue_node* temp = queue->front;
   
    // Loops through all messages, counting them
    while(temp != NULL){
        amount_messages++;
        temp = temp->next;
    }
   
   
    return amount_messages;


}





// Gets length of oldest message in the queue
long get_length_oldest(struct the_queue* queue){
    // If queue is empty
    if(queue->front == NULL){
        return -1;
    }
   
    // Store front of queue temporarily
    struct queue_node* temp = queue->front;
   
    long message_length =  strlen(queue->front->data);
   
    return message_length;
}





// Deletes oldest message in the queue
long delete_oldest(struct the_queue* queue){
    // If queue is empty
    if(queue->front == NULL){
        return -1;
    }
   
    // Store front of queue temporarily
    struct queue_node* temp = queue->front;
   
    // Make the second message the new front
    queue->front = queue->front->next;
   
    // Free the first node
    //free(temp->data);
    kfree(temp);
   
    // If the queue is empty, gotta make rear NULL also
    if(queue->front == NULL){
        queue->rear = NULL;
    }
   
    return 0;
}





// Retrieves message from front of queue
unsigned char* dequeue(struct the_queue* queue){
    // If queue is empty
    if(queue->front == NULL){
        return NULL;
    }
   
    // Store front of queue temporarily
    struct queue_node* temp = queue->front;
    // Retrieve data from front of queue
    unsigned char* data = temp->data;
   
    // Make the second message the new front
    queue->front = queue->front->next;
   
    // Free the first node
    //free(temp->data);
    kfree(temp);
   
    // If the queue is empty, gotta make rear NULL also
    if(queue->front == NULL){
        queue->rear = NULL;
    }
   
    // Return the message
    return data;
}


