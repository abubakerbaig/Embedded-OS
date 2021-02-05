#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SNAME1 "/mysem1"
#define SNAME2 "/mysem2"

char *data;

int main(int argc, char const *argv[])
{
    //creating semaphore 
    sem_t *sem_prod = sem_open(SNAME1, O_CREAT, 0600, 0);
    if(sem_prod == SEM_FAILED)  {
        perror("sen_open/producer");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_cons = sem_open(SNAME2,O_CREAT, 0600, 1);

    if(sem_cons == SEM_FAILED)  {
        perror("sen_open/consumer");
        exit(EXIT_FAILURE);
    }

    int shmfd = shm_open("/CDACshmry", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    ftruncate(shmfd, 10 * sizeof(char));

    data = (char *)mmap(NULL, 10 * sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

    while (1)
    {
        printf("Consumer: waiting for lock\n");
        sem_wait(sem_prod); //wait for producer to produce something
        printf("Consumer: Accquiring lock \n Consumer: string received from shared memory is : %s\n", data);
        sleep(1);
        printf("Consumer: Realising lock\n");
        sem_post(sem_cons); //signal producer data read
        printf("Consumer: Relised lock\n");
    }
    //   sem_close(SNAME1);
    //    sem_close(SNAME2);

    shm_unlink("/CDACshmry");

    return 0;
}