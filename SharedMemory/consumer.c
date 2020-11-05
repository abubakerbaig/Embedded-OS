#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>

//#define SNAME1 "/mysem1"
//#define SNAME2 "/mysem2"

char *data;

int main(int argc, char const *argv[])  {

   // sem_t *sem_id1 = sem_open(SNAME1, 1);
   // sem_t *sem_id2 = sem_open(SNAME2, 0);

    int shmfd = shm_open("/CDACshmry", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    ftruncate(shmfd, 10*sizeof(char)); 
    
    data = (char *) mmap(NULL, 10*sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

    while(1)    {
//        sem_wait(SNAME2);
        printf("string received from shared memory is : %s\n", data);  
        sleep(1);  
//        sem_post(SNAME1);
    }
 //   sem_close(SNAME1);
//    sem_close(SNAME2);

    shm_unlink("/CDACshmry");

       return 0;

}