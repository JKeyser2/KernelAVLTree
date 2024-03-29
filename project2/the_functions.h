#ifndef THE_FUNCTIONS_H
#define THE_FUNCTIONS_H





#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <linux/rwlock.h>




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
// Global variable for the read-write lock
extern rwlock_t mailbox_lock;



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
// For freeing all memory of the BST
void free_bst(struct tree_node* root);
// For freeing memory of all the queues
void free_queue(struct the_queue* queue);
// For finding a node
struct tree_node* find_node(struct tree_node* node, unsigned long id);
// Adds message to end of queue
void enqueue(struct the_queue* queue, unsigned char* data);
// Gets how many messages are in the queue
long get_amount_messages(struct the_queue* queue);
// Gets length of oldest message in the queue
long get_length_oldest(struct the_queue* queue);
// Deletes oldest message in the queue
long delete_oldest(struct the_queue* queue);
// Retrieves message from front of queue
unsigned char* dequeue(struct the_queue* queue);
// Deletes a node from BST 
struct tree_node* delete_node(struct tree_node* node, unsigned long id);



#endif
