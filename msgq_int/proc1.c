#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

struct mq_attr msgq_attr;
mqd_t mqfd;
char *buff;

int main (int argc, char const *argv[]) {
    msgq_attr.mq_flags = 0;
    msgq_attr.mq_maxmsg = 10;
    msgq_attr.mq_msgsize = 8;
    msgq_attr.mq_curmsgs = 0;

    mqfd = mq_open("/MessageQueue", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, &msgq_attr );
    buff = (char *)malloc(sizeof(char)*10);
    printf("Enter 10 Integers whose avg is to be calculated:\n");
    
    for(int i=0; i<10; i++) {
        
        scanf("%s",buff);
        mq_send(mqfd, &buff[i], sizeof(int),0);
    }
    
    mq_close(mqfd);
    return 0;
    
}