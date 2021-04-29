#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mq_attr msgq_attr;
mqd_t mqfd;
int buff[10];
unsigned int priority;

int main (int argc, char const *argv[]) {
    int num, avg=0; 
    msgq_attr.mq_flags = 0;
    msgq_attr.mq_maxmsg = 10;
    msgq_attr.mq_msgsize = 8;
    msgq_attr.mq_curmsgs = 0;

    mqfd = mq_open("/MessageQueue", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &msgq_attr );
    mq_receive(mqfd, buff, 10, &priority);
    for(int i=0 ; i<10; i++ )    {
        avg = avg + buff[i];
    }
    avg/=10;
    printf("average = %d\n",avg);
    mq_close(mqfd);
    return 0;
}
