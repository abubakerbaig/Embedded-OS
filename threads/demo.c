#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void *thread(void *a)   {
    printf("Inside Trhead\n");
}

int main(int argc, char const *argv[])  {

    pthread_t tid;
    printf("before creation\n");
    pthread_create(&tid, NULL, thread, NULL);
    printf("after creation\n");
    sleep(1);
    return 0;
}