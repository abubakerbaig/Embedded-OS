#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//use mkfifo -m 0666 file_name to create fifo 

int main(int argc,char const *argv[])   {

    int fd,num[2],sum=0;
    
    fd=open("pipe",O_RDONLY);
    read(fd, num, sizeof(num));
    printf("received:%d %d\n",num[1],num[0]);
    
    for(int i=0;i<2;i++)
        sum += num[i];
         
    close(fd);
    

    fd = open ("pipe2",O_WRONLY);
    write(fd,&sum,sizeof(sum));
    close(fd);

    return 0;
    
}