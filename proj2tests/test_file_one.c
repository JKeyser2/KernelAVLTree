#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>


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



void mailbox_init_test(){
    long rv = mailbox_init();
    
    if(rv == 0){
        printf("Mailbox initialize test passed!\n");
    }else{
        printf("Mailbox initialize test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_shutdown_test(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_create(999999);
    rv = mailbox_shutdown();
    
    
    if(rv == 0){
        printf("Mailbox shutdown test passed!\n");
    }else{
        printf("Mailbox shutdown test failed!\n");
    }
}



void mailbox_create_test_one(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_create(50);
    
    if(rv == -1){
        printf("Mailbox create with duplicate ID test passed!\n");
    }else{
        printf("Mailbox create with duplicate ID test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_create_test_two(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    
    if(rv == 0){
        printf("Mailbox create test passed!\n");
    }else{
        printf("Mailbox create test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_destroy_test_one(){
    long rv = mailbox_init();
    rv = mailbox_destroy(50);
    
    if(rv == -1){
        printf("Mailbox destroy on nonexistant node test passed!\n");
    }else{
        printf("Mailbox destroy on nonexistant node test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_destroy_test_two(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_destroy(50);
    
    if(rv == 0){
        printf("Mailbox destroy test passed!\n");
    }else{
        printf("Mailbox destroy test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_send_test_one(){
    long rv = mailbox_init();
    rv = mailbox_send(50, (unsigned char *)"car", strlen("car"));
    
    
    if(rv == -1){
        printf("Mailbox send to nonexistant mailbox test passed!\n");
    }else{
        printf("Mailbox send to nonexistant mailbox test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_send_test_two(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_send(50, (unsigned char *)"car", strlen("car"));
    
    if(rv == 0){
        printf("Mailbox send test passed!\n");
    }else{
        printf("Mailbox send test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_send_test_three(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_send(50, NULL, strlen("car"));
    
    if(rv == -1){
        printf("Sending NULL to mailbox test passed!\n");
    }else{
        printf("Sending NULL to mailbox test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_recv_test_one(){
    long rv = mailbox_init();
    
    
    
    rv = mailbox_recv(50, (unsigned char *)"car", strlen("car"));
    
    if(rv == -1){
        printf("Receiving from nonexistant mailbox test passed!\n");
    }else{
        printf("Receiving from nonexistant mailbox test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_recv_test_two(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    
    char the_string[4] = "\0";
    
    rv = mailbox_recv(50, (unsigned char *)the_string, 3);
    
    
    if(rv == -1){
        printf("Receiving from empty mailbox test passed!\n");
    }else{
        printf("Receiving from empty mailbox test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_recv_test_three(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_send(50, (unsigned char *)"elephant", strlen("elephant"));
    
    
    rv = mailbox_recv(50, NULL, 3);
    
    
    
    if(rv == -1){
        printf("Receiving from mailbox when user string is NULL test passed!\n");
    }else{
        printf("Receiving from mailbox when user string is NULL test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_recv_test_four(){
    mailbox_init();
    mailbox_create(50);
    mailbox_send(50, (unsigned char *)"elephant", strlen("elephant"));
    
    char the_string[4] = "\0";
    
    mailbox_recv(50, (unsigned char *)the_string, 2);
    
    
    if(strcmp(the_string, "el\0") == 0){
        printf("Receiving from mailbox when length is less than total length of the string test passed!\n");
    }else{
        printf("Receiving from mailbox when length is less than total length of the string test failed!\n");
    }
    
    mailbox_shutdown();
}



void mailbox_recv_test_five(){
    mailbox_init();
    mailbox_create(50);
    mailbox_send(50, (unsigned char *)"elephant", strlen("elephant"));
    
    char the_string[9] = "\0";
    
    mailbox_recv(50, (unsigned char *)the_string, strlen("elephant"));
    
    
    
    if(strcmp(the_string, "elephant\0") == 0){
        printf("Receiving from mailbox test passed!\n");
    }else{
        printf("Receiving from mailbox test failed!\n");
    }
    
    mailbox_shutdown();
}



void mailbox_delete_test_one(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    
    rv = mailbox_delete(50);
    
    
    
    if(rv == -1){
        printf("Deleting mail from nonexistant mailbox test passed!\n");
    }else{
        printf("Deleting mail from nonexistant mailbox test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_delete_test_two(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_send(50, (unsigned char *)"elephant", strlen("elephant"));
    rv = mailbox_delete(50);
    
    
    if(rv == 0){
        printf("Deleting mail from mailbox test passed!\n");
    }else{
        printf("Deleting mail from mailbox test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_delete_test_three(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_delete(50);
    
    
    
    if(rv == -1){
        printf("Deleting mail from empty mailbox test passed!\n");
    }else{
        printf("Deleting mail from empty mailbox test failed!\n");
    }
    
    rv = mailbox_shutdown();
}



void mailbox_delete_test_four(){
    mailbox_init();
    mailbox_create(50);
    mailbox_send(50, (unsigned char *)"elephant", strlen("elephant"));
    mailbox_send(50, (unsigned char *)"elephant2", strlen("elephant2"));
    mailbox_delete(50);
    
    
    char the_string[10] = "\0";
    
    mailbox_recv(50, (unsigned char *)the_string, strlen("elephant2"));
    
    
    
    if(strcmp(the_string, "elephant2\0") == 0){
        printf("Pushing up next piece of mail after mailbox delete passed!\n");
    }else{
        printf("Pushing up next piece of mail after mailbox delete failed!\n");
    }


    mailbox_shutdown();
}



void message_count_test_one(){
    long rv = mailbox_init();
    rv = message_count(50);
    
    
    
    if(rv == -1){
        printf("Getting message count of nonexistant mailbox test passed!\n");
    }else{
        printf("Getting message count of nonexistant mailbox test failed!\n");
    }


    rv = mailbox_shutdown();
}



void message_count_test_two(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = message_count(50);
    
    
    
    if(rv == 0){
        printf("Getting message count of empty mailbox test passed!\n");
    }else{
        printf("Getting message count of empty mailbox test failed!\n");
    }


    rv = mailbox_shutdown();
}



void message_count_test_three(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_send(50, (unsigned char *)"elephant", strlen("elephant"));
    rv = mailbox_send(50, (unsigned char *)"car", strlen("car"));
    rv = mailbox_send(50, (unsigned char *)"buffalo", strlen("buffalo"));
    rv = mailbox_send(50, (unsigned char *)"dog", strlen("dog"));
    rv = message_count(50);
    
    
    
    if(rv == 4){
        printf("Getting message count of non-empty mailbox test passed!\n");
    }else{
        printf("Getting message count of non-empty mailbox test failed!\n");
    }


    rv = mailbox_shutdown();
}



void message_length_test_one(){
    long rv = mailbox_init();
    rv = message_length(50);
    
    
    
    
    if(rv == -1){
        printf("Getting message length of oldest message of nonexistant mailbox test passed!\n");
    }else{
        printf("Getting message length of oldest message of nonexistant mailbox test passed!\n");
    }


    rv = mailbox_shutdown();
}



void message_length_test_two(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = message_length(50);
    
    
    
    if(rv == -1){
        printf("Getting message length of oldest message of empty mailbox test passed!\n");
    }else{
        printf("Getting message length of oldest message of empty mailbox test failed!\n");
    }


    rv = mailbox_shutdown();
}



void message_length_test_three(){
    long rv = mailbox_init();
    rv = mailbox_create(50);
    rv = mailbox_send(50, (unsigned char *)"elephant", strlen("elephant"));
    rv = message_length(50);
    
    
    if(rv == 8){
        printf("Getting message length of oldest message of mailbox test passed!\n");
    }else{
        printf("Getting message length of oldest message of mailbox test failed!\n");
    }


    rv = mailbox_shutdown();
}

int main(int argc, char *argv[]) {
    printf("cool!");
    
    mailbox_init_test();
    
    mailbox_shutdown_test();
    
    mailbox_create_test_one();
    
    mailbox_create_test_two();
    
    mailbox_destroy_test_one();
    
    mailbox_destroy_test_two();
    
    mailbox_send_test_one();
    
    mailbox_send_test_two();
    
    mailbox_send_test_three();
    
    mailbox_recv_test_one();
    
    mailbox_recv_test_two();
    
    mailbox_recv_test_three();
    
    mailbox_recv_test_four();
    
    mailbox_recv_test_five();
    
    mailbox_delete_test_one();
    
    mailbox_delete_test_two();
    
    mailbox_delete_test_three();
    
    mailbox_delete_test_four();
    
    message_count_test_one();
    
    message_count_test_two();
    
    message_count_test_three();
    
    message_length_test_one();
    
    message_length_test_two();
    
    message_length_test_three();
    

    return 0;
}
