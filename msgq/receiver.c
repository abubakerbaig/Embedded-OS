#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

struct mq_attr cdacmq_attr;
mqd_t mqfd;
char buffer[128];
unsigned int prio;

int main(int argc, char const *argv[])  {

    cdacmq_attr.mq_flags=0;
    cdacmq_attr.mq_maxmsg=4;
    cdacmq_attr.mq_msgsize=128;
    cdacmq_attr.mq_curmsgs=0;

    mqfd = mq_open("/CDACmsgq", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &cdacmq_attr);

    mq_receive(mqfd, buffer, 128, &prio);

    printf("%s\n",buffer);

    mq_close(mqfd);
    return 0;
}