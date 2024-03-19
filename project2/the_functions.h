#ifndef THE_FUNCTIONS_H
#define THE_FUNCTIONS_H





#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/random.h>




// Stores individual message in the queue
struct queue_node{
    // String of the message
    unsigned char* data;
    // Points to next message in the queue
    struct queue_node* next;
};





// Stores all messages in the queue
struct the_queue{
    // First message in queue
    struct queue_node* front;
    // last message in queue
    struct queue_node* rear;
};






// Creates a mailbox node for the BST
struct tree_node{
    // Used to identify the mailbox
    unsigned long id;
    // Stores the messages
    struct the_queue* queue;
    // Left child
    struct tree_node* left;
    // Right child
    struct tree_node* right;
};





// Global variable for root of BST
extern struct tree_node* root;




// Generates a random number between 1 and a million
unsigned long generate_random_number(void);
// For inserting node into the BST
struct tree_node* insert_node(struct tree_node* root, unsigned long id);
// Creates a new node
struct tree_node* create_node(unsigned long id);
// Creates a new queue
struct the_queue* create_queue(void);
// For displaying all of node IDs
void in_order_traversal(struct tree_node* node);





#endif
