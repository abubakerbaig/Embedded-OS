#include <stdio.h>


int main (int argc, char const *argv[]) {
    
    FILE *fd;
    long long int size=0;

    fd=fopen(argv[1], "r");

    if(fd == NULL)  {
        printf("\n File unable to Open.\n");
        return -1;
    }
    else
        printf("\n File Opened\n");

    fseek( fd, 0, SEEK_END);
    size = ftell(fd);

    printf("The size of the \"%s\" is : %lld bytes\n ",argv[1],size);

    return 0;

}