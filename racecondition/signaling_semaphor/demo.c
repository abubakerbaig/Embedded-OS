#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore1,semaphore2;
int a=0, b=0;
int sum;

void *input_thread(void *argc)  {

    printf("in input thread\n");
    
    sem_wait(&semaphore1);
    
    printf("Enter a and b values: \n");
    scanf("%d %d",&a, &b);
    
    
    sem_post(&semaphore2);
    
}

void *exe_thread( void *agrc )  {
    
    sem_wait(&semaphore2);
    printf("in execution thread\n");
    sum=a+b;
    //printf("sum= %d\n",sum);
    sem_post(&semaphore1);
    return (int*)(&sum);
    

}

int main (int argc, char const *argv[] )    {
    pthread_t ip,ex;
    void *sum1;
    
    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 0);

    pthread_create(&ip, NULL, input_thread, NULL);
    pthread_create(&ex, NULL, exe_thread, NULL);

    pthread_join(ip, NULL);
  //  pthread_join(ex, NULL);
    pthread_join(ex, &sum1);
    
    printf("result sum: %d\n", *(int*)sum1);

    return 0;
    }