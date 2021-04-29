#include <stdio.h>  
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])  {
    int pipefd[2],pipefd2[2];

    pipe(pipefd);   //-1 if failed
    pipe(pipefd2);  //opening two pipe's

    int fork_id;
 
    fork_id=fork();//-1 if failed
  /*  
    if(fork_id<0)    {
        perror("ERROR!:\n");
    }
*/
    if(0==fork_id)  {   //child process

        int val[2],sum;
        
        printf("TWO NUMBERS Whos Sum is needed:\n");
        
        for(int i=0;i<2;i++)
            scanf(" %d",&val[i]);
        
        write(pipefd[1],val,sizeof(val));       //integer tx'd and sum rx'd
        close(pipefd[1]);


        wait(NULL);     //wait for parent to sned data     

        read(pipefd2[0],&sum,sizeof(sum));
        printf("Sum received form parent is : %d \n",sum);     
        close(pipefd2[0]);   
        

    }
    else    {   //parent process

        int val[2],sum=0;        
        read(pipefd[0],&val,sizeof(val));

        for(int i=0;i<2;i++)    {
           printf("\nReceived string in parent is: %d.\n",val[i]);
            sum+=val[i];
        }
        close(pipefd[0]);

        write(pipefd2[1],&sum,sizeof(sum));

        close(pipefd2[1]);

    }

    return 0;

}