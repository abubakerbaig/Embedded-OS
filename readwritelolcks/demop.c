#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count;
pthread_rwlock_t count_rwlock;

void *thread1(void *argc)   {
    printf("thread1 - before write lock\n");
    pthread_rwlock_wrlock(&count_rwlock);
    printf("thread1 - inside write lock\n");
    count++;
    pthread_rwlock_unlock(&count_rwlock);
    printf("thread1 - after write unlock\n");
}

void *thread2(void *argc)   {

    printf("thread2 - before read lock\n");
    pthread_rwlock_rdlock(&count_rwlock);
    printf("thread2 - inside read lock\n");
    
    printf("Thread 2: count = %d\n ",count);
    sleep(1);
    pthread_rwlock_unlock(&count_rwlock);
    printf("thread2 - after read unlock\n");

}

void *thread3(void *argc)   {
    printf("thread3 - before read lock\n");
    pthread_rwlock_rdlock(&count_rwlock);
    printf("thread3 - inside read lock\n");
    printf("Thread 3: count = %d\n ",count);
    pthread_rwlock_unlock(&count_rwlock);
    printf("thread3 -after read unlock\n");

}

void *thread4(void *argc)   {
    printf("thread4 - before read lock\n");
    pthread_rwlock_rdlock(&count_rwlock);
    printf("thread4 - inside read lock\n");
    printf("Thread 4: count = %d\n ",count);
    pthread_rwlock_unlock(&count_rwlock);
    printf("thread4 - after read unlock\n");

}



int main (int argv, char const *agrc[])     {
    pthread_t t1,t2,t3,t4;

    pthread_rwlock_init(&count_rwlock, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);
    pthread_create(&t4, NULL, thread4, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);


    return 0;
} 
