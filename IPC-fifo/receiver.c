#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char const *argv[])   {

//    char buff[64];
    int fd;
    int num[2],sum=0;
    printf("Enter two Numbers:\n");
    for( int i=0; i<2; i++) {
        scanf ("%d",&num[i]);
    }
    
    fd=open("pipe", O_WRONLY);
    write(fd, num, sizeof(num));
    close(fd);

    fd=open("pipe2",O_RDONLY);
    read(fd, &sum, sizeof(sum));
    printf("RESULT FROM OTHER PROCESS:\t%d\n",sum);
    close (fd);
    return 0;

}
