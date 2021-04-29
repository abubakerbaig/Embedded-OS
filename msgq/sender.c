#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <string.h>


struct mq_attr cdacmq_attr;
mqd_t mqfd;
char buffer[128];

int main(int argc, char const *argv[])  {

    cdacmq_attr.mq_flags=0;
    cdacmq_attr.mq_maxmsg=4;
    cdacmq_attr.mq_msgsize=128;
    cdacmq_attr.mq_curmsgs=0;

    mqfd = mq_open("/CDACmsgq", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, &cdacmq_attr);

    for(int i=1 ; ;i++ )  {
        printf("enter %d message:\n",i);
        scanf(" %[^\n]s", buffer);
        mq_send(mqfd, buffer, strlen(buffer), 0);
    }

    mq_close(mqfd);
    return 0;
}