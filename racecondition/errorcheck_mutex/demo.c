#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t count_mutex;
pthread_mutexattr_t count_mutex_attr;
int count;
int error_check;

void *inc_thread(void *argc)    {

    while(1)    {
        
        error_check=pthread_mutex_lock(&count_mutex);
        printf("2. Errorcheck-%d\n",error_check);
        error_check=pthread_mutex_lock(&count_mutex);
        
        if( error_check>0 ) {
            printf("Mutex is already locked!!Errorcheck-%d\n",error_check);
            sleep(2);

        }
        count ++;

        printf("inc_thread: %d \n",count);
        
        pthread_mutex_unlock(&count_mutex);
    }
    
}

void *dec_thread(void *argc)    {

    while(1)    {
        pthread_mutex_lock(&count_mutex);
        count --;
        printf("dec_thread: %d \n",count);
        pthread_mutex_unlock(&count_mutex);
    }

}

int main(int argc, char const argv[])   {

    pthread_t inc_tid, dec_tid;

    pthread_mutexattr_init(&count_mutex_attr);
    pthread_mutexattr_settype(&count_mutex_attr, PTHREAD_MUTEX_ERRORCHECK);

    pthread_mutex_init( &count_mutex, &count_mutex_attr);

    pthread_create(&inc_tid, NULL, inc_thread, NULL);
    pthread_create(&dec_tid, NULL, dec_thread, NULL);

    pthread_join(inc_tid, NULL);
    pthread_join(dec_tid, NULL);

    pthread_mutex_destroy(&count_mutex);   
    pthread_mutexattr_destroy(&count_mutex_attr);

    return 0;

}