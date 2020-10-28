#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])  {
    
    pid_t id,parent_id;

    printf("before fork\n");
    id=fork();
    printf("after fork\n");

    if(0==id)   {
        printf("returned 0(%d): pid-%d\tppid-%d\n",getpid(),getppid());
    }
    else    {
         printf("returned 1(%d): pid-%d\tppid-%d\n",getpid(),getppid());
    }

    return 0;
}