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


