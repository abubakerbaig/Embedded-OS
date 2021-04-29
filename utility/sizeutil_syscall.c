#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *agrv[])  {

    struct stat buf;

    stat(agrv[1], &buf);

    printf("Side of the file \"%s\" is %lld bytes.\n", agrv[1], buf.st_size);

    return 0;
}