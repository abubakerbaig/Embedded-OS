/*  Using pipes write a program for communication between three processes,
    paret, child and grand child. Parent reads a message and sends it to 
    the child through pipe. Child reds it and send to its own Child to 
    encrypt the message by using message[i] = message[i]+5 and encrypted 
    message sent back to its own parent. Child possess after receiving 
    encrypted message from own child decrypt the messsage and if it matches 
    with the original message it received from main parent, then it send 
    "MATCHED" else "NOT MATCHED " to parent process.

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
                                //pipe[1] - write end 
                                //pipe[0] - read end
int main()
{   
    int pipefds1[2], pipefds2[2], pipefds3[2], pipefds4[2];
    char parent_str[20], child_str[20], ctp[20], grandchild_str[20], encrypted_child_str[20], decrypt[20], encrypt[20];
    int pid1, pid2;
    pipe(pipefds1);
    pipe(pipefds2);
    pipe(pipefds3);
    pipe(pipefds4);

    /*
    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 0);
    */
    pid1 = fork();
    if (pid1 != 0) //parent
    {
        printf("Enter string to send to child and grand child:\n");
        scanf("%s", parent_str);
        printf("Parent string you entered is ---> %s \n", parent_str);
 
        write(pipefds1[1], parent_str, sizeof(parent_str));
        close(pipefds1[1]);

        //sleep(1); //allowing child process to execute

        read(pipefds4[0], ctp, sizeof(ctp));
        close(pipefds4[0]);

        printf("final string at parent ----> %s\n", ctp);
    }
    else
    { //child

        pid2 = fork();
        if (pid2 != 0)  //parent
        {
                //read string from parent
            read(pipefds1[0], child_str, sizeof(child_str));
            close(pipefds1[0]);
            printf("String received from parent-->%s\n", child_str);
                //writing reveived string to grand child for encryption
            write(pipefds2[1], child_str, sizeof(child_str));
            close(pipefds2[1]);
            //sleep(1); //allowing grandchild to run

            read(pipefds3[0], encrypted_child_str, sizeof(encrypted_child_str));
            close(pipefds3[0]);

            printf("Encrypted msg received from grand child to child ---> %s \n", encrypted_child_str);
            
            for (int i = 0; i < strlen(encrypted_child_str); i++)
            {
                encrypted_child_str[i] = encrypted_child_str[i] - 5;
            }

            printf("Child string after decryption of grandchild string ---> %s\n", encrypted_child_str);

            printf("child string received from parent was --->%s \n", child_str);

            for (int i = 0; i < strlen(encrypted_child_str); i++)
            {
                if (encrypted_child_str[i] == child_str[i])
                    continue;
                else
                {
                    write(pipefds4[1], "NOT MATCHED", 13);
                    close(pipefds4[1]);
                    return 0;
                }   
            }
            write(pipefds4[1], "MATCHED", 8);
            close(pipefds4[1]);
            return 0;
        }
        else    //child
        {
            read(pipefds2[0], grandchild_str, sizeof(grandchild_str));
            close(pipefds2[0]);
            printf("Grand chaild string received form child--->%s \n", grandchild_str);
            int i = 0;
            for (i = 0; i < strlen(grandchild_str); i++)
            {
                grandchild_str[i] = grandchild_str[i] + 5;
            }
            printf("String after encryption ---> %s \n", grandchild_str);
            write(pipefds3[1], grandchild_str, sizeof(grandchild_str));
            close(pipefds3[1]);
        }
        return 0;
    }
}