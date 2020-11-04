#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main ( int argvc, char const *argv[])   {

    pid_t id;

    id = fork();

    if(id == 0) {
                    //child process
        printf("Child process starting.process id:5=%d , its p:%d\n",getpid(),getppid());
        sleep(2);
        printf("Child process Exiting.\n");
        

    }
    else {
                    //parent process
        printf("Parent process starting.process id: %d, its p:%d\n",getpid(),getppid());
        sleep(12);
        printf("parent process Exiting.\n");
        
    }

    return 0;
}  
