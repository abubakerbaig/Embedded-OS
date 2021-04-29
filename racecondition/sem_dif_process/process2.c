#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>
#include <unistd.h>


const char *semName = "asdfsd";
extern int count;


void child(void)
{
    sem_t *sem_id = sem_open(semName, O_CREAT, 0600, 1);
    if (sem_id == SEM_FAILED){
        perror("Child   : [sem_open] Failed\n"); 
        return;        
    }
    while(1)    {
    sem_wait(sem_id);
        printf("Inside semaphore in process 2(child) for decrementing count.%d\n",count);
        //count--;
        printf("Child   : I am done! Release Semaphore\n");
    if (sem_post(sem_id) < 0)
        printf("Child   : [sem_post] Failed \n");
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    child();
    return 0;
}