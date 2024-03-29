#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdbool.h>
#include <stdlib.h>


#define __NR_mailbox_init 548
#define __NR_mailbox_shutdown 549
#define __NR_mailbox_create 550
#define __NR_mailbox_send 551
#define __NR_mailbox_delete 552
#define __NR_mailbox_recv 553
#define __NR_mailbox_destroy 554
#define __NR_message_count 555
#define __NR_message_length 556


long mailbox_init(void) {
    return syscall(__NR_mailbox_init);
}

long mailbox_shutdown(void) {
    return syscall(__NR_mailbox_shutdown);
}

long mailbox_create(unsigned long id) {
    return syscall(__NR_mailbox_create, id);
}

long mailbox_send(unsigned long id, unsigned char *msg, long len) {
    return syscall(__NR_mailbox_send, id, msg, len);
}

long message_count(unsigned long id) {
    return syscall(__NR_message_count, id);
}

long message_length(unsigned long id) {
    return syscall(__NR_message_length, id);
}

long mailbox_delete(unsigned long id) {
    return syscall(__NR_mailbox_delete, id);
}
long mailbox_recv(unsigned long id, unsigned char *msg, long len) {
    return syscall(__NR_mailbox_recv, id, msg, len);
}

long mailbox_destroy(unsigned long id) {
    return syscall(__NR_mailbox_destroy, id);
}




int main(int argc, char *argv[]) {
    bool end_loop = false;
    int user_input = -1;
    int user_input2 = -2;
    unsigned char *user_input_string = malloc(100 * sizeof(unsigned char)); 
    //unsigned char user_input_string[100];
    long len_size = -1;
    
    printf("COOL!\n");
    
    while(end_loop == false){
        strcpy(user_input_string, "");
        
        printf("These are the options. Pick a number 1 through 10\n");
        printf("1. mailbox_init\n");
        printf("2. mailbox_shutdown\n");
        printf("3. mailbox_create\n");
        printf("4. mailbox_destroy\n");
        printf("5. mailbox_send\n");
        printf("6. mailbox_recv\n");
        printf("7. mailbox_delete\n");
        printf("8. message_count\n");
        printf("9. message_length\n");
        printf("10. exit\n");
        scanf("%d", &user_input);
        
        if(user_input == 1){
            printf("You selected mailbox_init\n");
            mailbox_init();
        }else if(user_input == 2){
            printf("You selected mailbox_shutdown\n");
            mailbox_shutdown();
        }else if(user_input == 3){
            printf("You selected mailbox_create. Give me a number for the ID\n");
            scanf("%d", &user_input2);
            user_input2 = (unsigned long)user_input2;
            mailbox_create(user_input2);
        }else if(user_input == 4){
            printf("You selected mailbox_destroy. Give me a number for the ID\n");
            scanf("%d", &user_input2);
            getchar();
            user_input2 = (unsigned long)user_input2;
            mailbox_destroy(user_input2);
      }else if(user_input == 5){
            printf("You selected mailbox_send. Give me a number for the ID ");
            scanf("%d", &user_input2);
            user_input2 = (unsigned long)user_input2;
            printf("You selected mailbox_send. Give me a string, or type empty, or type null ");
            scanf("%s", user_input_string);
            if(strcmp(user_input_string, "empty") == 0){
                printf("You selected mailbox_send. Give me a value for length ");
                scanf("%ld", &len_size);
                mailbox_send(user_input2, "", len_size);
            }
            else if(strcmp(user_input_string, "null") == 0){
                printf("You selected mailbox_send. Give me a value for length ");
                scanf("%ld", &len_size);
                mailbox_send(user_input2, NULL, len_size);
            }else{
                printf("You selected mailbox_send. Give me a value for length ");
                scanf("%ld", &len_size);
                printf("WOW 0.5: %s\n", user_input_string);
                mailbox_send(user_input2, user_input_string, len_size);
            }
        }else if(user_input == 6){
            printf("You selected mailbox_recv. Give me a number for the ID ");
            scanf("%d", &user_input2);
            user_input2 = (unsigned long)user_input2;
            printf("You selected mailbox_recv. Give me a string, or type empty, or type null ");
            scanf("%s", user_input_string);
            if(strcmp(user_input_string, "empty") == 0){
                strcpy(user_input_string, "");
                printf("WOW: %s\n", user_input_string);
                printf("You selected mailbox_recv. Give me a value for length ");
                scanf("%ld", &len_size);
                mailbox_recv(user_input2, user_input_string, len_size);
            }
            else if(strcmp(user_input_string, "null") == 0){
                strcpy(user_input_string, "");
                printf("You selected mailbox_recv. Give me a value for length ");
                scanf("%ld", &len_size);
                mailbox_recv(user_input2, NULL, len_size);
            }else{
                printf("You selected mailbox_recv. Give me a value for length ");
                scanf("%ld", &len_size);
                mailbox_recv(user_input2, user_input_string, len_size);
            }
            printf("Message received: %s\n", user_input_string);
         }else if(user_input == 7){
            printf("You selected mailbox_delete. Give me a number for the ID\n");
            scanf("%d", &user_input2);
            user_input2 = (unsigned long)user_input2;
            mailbox_delete(user_input2);
         }else if(user_input == 8){
            printf("You selected message_count. Give me a number for the ID\n");
            scanf("%d", &user_input2);
            user_input2 = (unsigned long)user_input2;
            message_count(user_input2);
         }else if(user_input == 9){
            printf("You selected message_length. Give me a number for the ID\n");
            scanf("%d", &user_input2);
            user_input2 = (unsigned long)user_input2;
            message_length(user_input2);
         }else{
             end_loop = true;
         }
    }
    return 0;
}




