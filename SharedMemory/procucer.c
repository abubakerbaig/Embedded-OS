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
#include <string.h>

#define SNAME1 "/mysem1"
#define SNAME2 "/mysem2"

char *str;
char data[10];

int main(int argc, char const *argv[])
{
//opening semaphore
  sem_t *sem_prod = sem_open(SNAME1, 0);
    if(sem_prod == SEM_FAILED)  {
        perror("sen_open/producer");
        exit(EXIT_FAILURE);
    }

  sem_t *sem_cons = sem_open(SNAME2, 1);

    if(sem_cons == SEM_FAILED)  {
        perror("sen_open/consumer");
        exit(EXIT_FAILURE);
    }

  int shmfd = shm_open("/CDACshmry", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

  ftruncate(shmfd, 10 * sizeof(char));

  str = (char *)mmap(NULL, 10 * sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
  printf("producer: mmap return - %x\n", str);

  while (1)
  {
    printf("producer: checking for lock\n");
    sem_wait(sem_cons); //wait for consumer to have an open slot
    printf("producer: Inside producer, accquired lock\nproducer: enter string to store in shared memory:\n");
    scanf("%s", data);
    strcpy(str, data);
    //printf("producer: mmap return - %x", str);
    printf("producer: Realising lock");

    sem_post(sem_prod); //signal that something is being produced
    printf("producer: realising Lock\n");
  }
   sem_close(sem_prod);
   sem_close(sem_cons);
  shm_unlink("/CDACshmry");

  return 0;
}