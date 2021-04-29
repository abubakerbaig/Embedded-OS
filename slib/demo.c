#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "fileop.h"


int main()  {
    int fd;
    char s[10],wstr[64];
            
    printf("Enter file name to open:\n");
    scanf("%s",s);
   
    fd=opening(s,X);
    writing(fd);
    close(fd);

    fd=opening(s,Y);
    reading(fd);
    close(fd);

    return 0;
}



