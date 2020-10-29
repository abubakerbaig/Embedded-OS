#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int add(int x,int y)    {
    return x+y;
}

void *thread(void *args)    {

    int s=add(10,20);
    printf("Thread add-%d\n",s);

}

int main(int argc, char const *argv[])  {

    pthread_t tid;
    printf("Main - %d\n",add(50,40));

    pthread_create(&tid, NULL, thread, NULL);
    
    return 0;
}