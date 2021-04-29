#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;

int add(int x,int y)    {
    return x+y;
}

void *thread(void *args)    {

    pthread_mutex_lock(&lock);
    int s=add(10,20);
    printf("Thread add-%d\n",s);
    pthread_mutex_unlock(&lock);
}

int main(int argc, char const *argv[])  {

    pthread_t tid;
    
    
    pthread_mutex_init(&lock,NULL);
    

    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);

    pthread_mutex_lock(&lock);
    printf("Main - %d\n",add(50,40));
    pthread_mutex_unlock(&lock);

    pthread_mutex_destroy(&lock);
    return 0;
}