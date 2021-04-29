#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>
#include <unistd.h>


const char *semName = "asdfsd";
int count=0;

void parent(void){
    sem_t *sem_id = sem_open(semName, O_CREAT, 0600, 1);
    if (sem_id == SEM_FAILED){
        perror("Parent  : [sem_open] Failed\n"); return;
    }
    while(1){
        printf("Parent  : Wait for Child to Print\n");
        if (sem_wait(sem_id) < 0)
            printf("Parent  : [sem_wait] Failed\n");
        printf("Parent  : Child Printed! \n");
        if(sem_post(sem_id) < 0)
            printf("Parent : [sem_post] failed\n");
    }
    
    if (sem_close(sem_id) != 0){
        perror("Parent  : [sem_close] Failed\n"); 
        return;
    }
    if (sem_unlink(semName) < 0){
        printf("Parent  : [sem_unlink] Failed\n"); 
        return;
    }
}


int main(int argc, char *argv[])
{
    pid_t pid;
    parent();
   
    return 0;
}