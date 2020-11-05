#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>

//#define SNAME1 "/mysem1"
//#define SNAME2 "/mysem2"

char *str;
char data[10];

int main(int argc, char const *argv[])  {

    //sem_t *sem_id1 = sem_open(SNAME1, O_CREAT, 0644, 1);
    //sem_t *sem_id2 = sem_open(SNAME2, O_CREAT, 0644, 0);
    
    int shmfd = shm_open("/CDACshmry", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    ftruncate(shmfd, 10*sizeof(char)); 
    
    str= (char *) mmap(NULL, 10*sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    printf("mmap return - %x\n", str);

    while(1)    {

      //sem_wait(SNAME1);
        printf("enter string to store in shared memory:\n");
        scanf("%s",data);
        strcpy(str, data);
        printf("mmap return - %x", str);
      //sem_post(SNAME2);
        //printf("%s\n",str);

    }
   // sem_close(SNAME1);
   // sem_close(SNAME2);
    shm_unlink("/CDACshmry");

    return 0;

}