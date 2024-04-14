#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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





// Global variable to store the root of the BST
struct tree_node* root = NULL;






// Generates a random number between 1 and a million
unsigned long generate_random_number();
// Creates a new queue
struct the_queue* create_queue();
// Adds message to end of queue
void enqueue(struct the_queue* queue, unsigned char* data);
// Retrieves message from front of queue
unsigned char* dequeue(struct the_queue* queue);
// Deletes oldest message in the queue
long delete_oldest(struct the_queue* queue);
// Gets length of oldest message in the queue
long get_length_oldest(struct the_queue* queue);
// Gets how many messages are in the queue
long get_amount_messages(struct the_queue* queue);
// Creates a new node
struct tree_node* create_node(unsigned long id);
// For inserting node into the BST
struct tree_node* insert_node(struct tree_node* root, unsigned long id);
// For freeing all memory of the BST
void free_bst(struct tree_node* root);
// For freeing memory of all the queues
void free_queue(struct the_queue* queue);
// For finding a node
struct tree_node* find_node(struct tree_node* node, unsigned long id);
// For finding node with smallest ID. For rebalancing after deleting a node
struct tree_node* find_min_id(struct tree_node* root);
// Deletes a node from BST 
struct tree_node* delete_node(struct tree_node* node, unsigned long id);
// For displaying all of node IDs
void in_order_traversal(struct tree_node* node);


// Set up initial state of BST. Add a root node. Return 0 on success
long mailbox_init(void);
// Destroys BST. Returns 0 on success
long mailbox_shutdown(void);
// Creates a new node. Returns 0 on success
long mailbox_create(unsigned long id);
// Deletes a node. Returns 0 on success
long mailbox_destroy(unsigned long id);
// Sends a message to a node. Returns 0 on success
long mailbox_send(unsigned long id, unsigned char *msg, long len);
// Retrieves a message from a node. Returns length of message on success
long mailbox_recv(unsigned long id, unsigned char *msg, long len);
// Deletes oldest message in the queue. Returns 0 on success
long mailbox_delete(unsigned long id);
// Counts how many messages are in the mailbox
long message_count(unsigned long id);
// Retrieves length of oldest message in mailbox
long message_length(unsigned long id);


int main (int argc, char **argv){
    mailbox_init();
    
    //mailbox_create(50);
    //mailbox_create(25);
    //mailbox_create(75);
    //mailbox_create(65);
    //mailbox_create(64);
    //mailbox_create(66);
    //mailbox_create(80);
    //mailbox_send(50, "Hello world2", strlen("Hello world2"));
    //mailbox_send(50, "Hello world3", strlen("Hello world3"));
    //mailbox_send(50, "Hello world4", strlen("Hello world4"));
    //mailbox_send(64, "Hello world5", strlen("Hello world5"));
    //mailbox_send(64, "Hello world6", strlen("Hello world6"));
    //mailbox_destroy(50);
    
    //in_order_traversal(root);
    
    //mailbox_shutdown();
    

    mailbox_create(5);
    mailbox_create(5);
    mailbox_create(10);
    mailbox_create(17);
    mailbox_create(15);
    
    mailbox_destroy(17);
    mailbox_destroy(18);
    
    mailbox_send(10, "Hello world", strlen("Hello world"));
    
    mailbox_recv(10, "Message", strlen("Message"));
    mailbox_recv(10, "Message", strlen("Message"));
    mailbox_recv(11, "Message", strlen("Message"));
    
    mailbox_send(5, "Hello world", strlen("Hello world"));
    
    mailbox_delete(5);
    mailbox_delete(5);
    mailbox_delete(6);
    
    mailbox_send(5, "Car", strlen("Car"));
    mailbox_send(5, "Hello world2", strlen("Hello world2"));
    mailbox_send(5, "Hello world3", strlen("Hello world3"));
    mailbox_send(5, "Hello world4", strlen("Hello world4"));
    mailbox_send(5, "Hello world5", strlen("Hello world5"));
    
    message_count(5);
    
    message_length(5);
    
    in_order_traversal(root);
    
    mailbox_destroy(5);
    
    in_order_traversal(root);
    
    
    mailbox_shutdown();
    
}




// Creates a new queue
struct the_queue* create_queue(){
    // Allocates memory
    struct the_queue* queue = (struct the_queue*)malloc(sizeof(struct the_queue));
    
    // Queue is empty
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}






// Adds message to end of queue
void enqueue(struct the_queue* queue, unsigned char* data){
    // Allocates memory for a new node
    struct queue_node* new_node = (struct queue_node*)malloc(sizeof(struct queue_node));
    
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
    free(temp);
    
    // If the queue is empty, gotta make rear NULL also
    if(queue->front == NULL){
        queue->rear = NULL;
    }
    
    // Return the message
    return data;
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
    free(temp);
    
    // If the queue is empty, gotta make rear NULL also
    if(queue->front == NULL){
        queue->rear = NULL;
    }
    
    return 0;
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




// Creates a new node
struct tree_node* create_node(unsigned long id){
    // Allocates memory
    struct tree_node* new_node = (struct tree_node*)malloc(sizeof(struct tree_node));
    
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
        free(root);
    }
    
}





// For freeing memory of all the queues
void free_queue(struct the_queue* queue){
    // If queue is not empty
    if(queue != NULL){
        //printf("Queue is not NULL\n");
        // Get head of queue
        struct queue_node* curr = queue->front;
        // For storing node to be deleted
        struct queue_node* temp;
        
        
        // Free each node in the queue
        while(curr != NULL){
            //printf("Freeing node\n");
            
            // Stash node to be deleted
            temp = curr;
            // Make the next node the new current
            curr = curr->next;
            // Free the node
            //free(temp->data);
            free(temp);
        }
        free(queue);
        queue = NULL;
    }else{
        printf("Queue is NULL\n");
    }
    
    // Free the queue structure
    //free(queue);
}




// Generates a random number between 1 and a million
unsigned long generate_random_number(){
    return (rand() % 1000000) + 1;
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


// For finding node with smallest ID. For rebalancing after deleting a node
struct tree_node* find_min_id(struct tree_node* node){
    // Starts at first node to right of node to be deleted
    struct tree_node* curr = node;
    // While there are still more nodes to the left
    while(curr->left != NULL){
        curr = curr->left;
    }
    //When at smallest node
    return curr;
}





// Deletes a node from BST 
struct tree_node* delete_node(struct tree_node* node, unsigned long id){
    // If BST is empty, nothing to delete
    if(node == NULL){
        return node;
    }
    
    // If node exists
    if(node != NULL){
        // If the node is the root, and doesn't have any children
        if(node->id == root->id && node->left == NULL && node->right == NULL){
            // Set the root to NULL
            free_queue(node->queue);
            free(node);
            root = NULL;
            return root;
        }
    }
    
    // Search for node to be deleted
    // If ID is smaller than ID of current node, go left
    if(id < node->id){
        node->left = delete_node(node->left, id);
        return node;
    // If ID is larger than ID of current node, go right
    }else if(id > node->id){
        node->right = delete_node(node->right, id);
        return node;
    // If we found the ID
    // If 1 of children is empty
    }
    if(node->left == NULL){
        struct tree_node* temp = node->right;
    
    	//printf("woah");
        //node->id = succ->id;
        
        
        // Free old queue
        //free_queue(node->queue);
        // Create fresh queue
        //node->queue = create_queue();
        // Copy over all messages from node that has taken old node's spot
        //while(succ->queue->front != NULL){
            //enqueue(node->queue, succ->queue->front->data);
            //dequeue(succ->queue);
        //}
        
        // !!!
        //node->queue = succ->queue;
        
        //free_queue(succ->queue);
        
        while(node->queue->front != NULL){
            dequeue(node->queue);
        }
        free(node->queue);
        
        free(node);
        return temp;
    }else if(node->right == NULL){
        //printf("no right child");
        struct tree_node* temp = node->left;
        
        //printf("woah");
        //node->id = temp->id;
        
        
        // Free old queue
        //free_queue(node->queue);
        // Create fresh queue
        //node->queue = create_queue();
        // Copy over all messages from node that has taken old node's spot
        //while(succ->queue->front != NULL){
            //enqueue(node->queue, succ->queue->front->data);
            //dequeue(succ->queue);
        //}    
        
        //free_queue(succ->queue);
        
        while(node->queue->front != NULL){
            dequeue(node->queue);
        }
        free(node->queue);
        
        free(node);
        
        
        return temp;
    // If both children exist
    }else{
        struct tree_node* succParent = node;
        
        // Find successor
        struct tree_node* succ = node->right;
        
        while(succ->left != NULL){
            succParent = succ;
            succ = succ->left;
        }
        
        // Delete successor
        if(succParent != node){
            succParent->left = succ->right;
        }else{
            succParent->right = succ->right;
        }
        //printf("woah");
        node->id = succ->id;
        
        
        // Free old queue
        free_queue(node->queue);
        // Create fresh queue
        node->queue = create_queue();
        // Copy over all messages from node that has taken old node's spot
        while(succ->queue->front != NULL){
            enqueue(node->queue, succ->queue->front->data);
            dequeue(succ->queue);
        }
        
        // !!!
        //node->queue = succ->queue;
        
        free_queue(succ->queue);
        free(succ);
        return node;
    }
        
        
}


// For displaying all of node IDs
void in_order_traversal(struct tree_node* node){
    if(node != NULL){
        // Left subtree
        in_order_traversal(node->left);
        
        printf("%lu ", node->id);
        struct queue_node* temp = node->queue->front;
        while(temp != NULL){
            // Gets and prints the message
            unsigned char* data = temp->data;
            printf(" %s ", data);
    
            // Goes to next message
            temp = temp->next;
        }
        
        // Right subtree
        in_order_traversal(node->right);
    }
}


// Set up initial state of BST. Add a root node. Return 0 on success
long mailbox_init(void){
    
    // Get ID for node
    unsigned long random_number = generate_random_number();
    
    // Insert first node into BST
    root = insert_node(root, random_number);
    
    return 0;


}





// Destroys BST. Returns 0 on success
long mailbox_shutdown(void){
    
    free_bst(root);
    
    root = NULL;
    
    return 0;


}





// Creates a new node. Returns 0 on success
long mailbox_create(unsigned long id){

    // Checks if the node already exists
    struct tree_node* node = find_node(root, id);
    
    // If the node does not exist
    if(node == NULL){
        // Delete the node
        insert_node(root, id);
        printf("Node inserted\n");
        return 0;
    // If the node does exist
    }else{
        printf("Node already exists\n");
        return -1;
    }


}





// Deletes a node. Returns 0 on success
long mailbox_destroy(unsigned long id){
    // Checks if the node already exists
    struct tree_node* node = find_node(root, id);
    
    // If the node does exist
    if(node != NULL){
        // Delete the node
        delete_node(root, id);
        printf("Node deleted\n");
        return 0;
    // If the node does not exist
    }else{
        printf("Node does not exist\n");
        return -1;
    }
}


// Sends a message to a node
long mailbox_send(unsigned long id, unsigned char *msg, long len){
    // Checks if the node already exists
    struct tree_node* node = find_node(root, id);
    
    // If the node does exist
    if(node != NULL){
        enqueue(node->queue, msg);
        printf("Successfully added messsage to end of queue\n");
        return 0;
    // If the node does not exist
    }else{
        printf("Node does not exist\n");
        return -1;
    }

}






// Retrieves a message from a node. Returns length of message on success
long mailbox_recv(unsigned long id, unsigned char *msg, long len){
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
    
    // If the node exists
    if(node != NULL){
        unsigned char* message_string = dequeue(node->queue);
        // If there is a message in the queue of the node
        if(message_string != NULL){
            printf("Message: %s\n", message_string);
            return strlen(message_string);  
        // If the queue is empty
        }else{
            printf("Mailbox is empty\n");
            return -1;
        }
    // If the node does not exist
    }else{
    printf("Node does not exist\n");
    return -1;
    }
}






// Deletes oldest message in the queue. Returns 0 on success
long mailbox_delete(unsigned long id){
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
    
    // If the node exists
    if(node != NULL){
        // Attemps to remove oldest message from queue
        long functionReturn = delete_oldest(node->queue);
        // If queue was already empty
        if(functionReturn == -1){
            printf("Queue was already empty\n");
            return -2;
        // If queue was not already empty
        }else{
            printf("Oldest message deleted\n");
            return 0;
        }
    // If the node does not exist
    }else{
        printf("Node does not exist\n");
        return -1;
    }
}






// Counts how many messages are in the mailbox
long message_count(unsigned long id){
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
    
    // If node exists
    if(node != NULL){
        long amount_messages = get_amount_messages(node->queue);
        printf("Ammount of messages: %ld\n", amount_messages);
        return amount_messages;
    // If node does not exist
    }else{
        printf("Node does not exist\n");
        return -1;
    }
}





// Retrieves length of oldest message in mailbox
long message_length(unsigned long id){
    // Checks if node exists
    struct tree_node* node = find_node(root, id);
    
    // If the node exists
    if(node != NULL){
        // Gets length of oldest message
        long message_length = get_length_oldest(node->queue);
        // If queue was empty
        if(message_length == -1){
            printf("Queue was empty\n");
            return -2;
        // If queue wasn't empty
        }else{
            printf("Message length: %ld\n", message_length);
            return message_length;
        }
    // If the node does not exist
    }else{
        printf("Node does not exist\n");
        return -1;
    }
}
