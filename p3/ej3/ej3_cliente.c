#include "ej3_common.h"

int main(int argc, char **argv){
    mqd_t mq_req;
    mqd_t mq_res;

    int stop = 0;

    char reqBuffer[MAX_SIZE];
    char resBuffer[MAX_SIZE];

    struct mq_attr attr;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;

    char reqQueue[200];
    char resQueue[200];

    sprintf(reqQueue, "%s-%s", REQ_QUEUE, getenv("USER"));
    printf("[CLIENT]: Request queue name: %s\n", reqQueue);

    sprintf(resQueue, "%s-%s", RES_QUEUE, getenv("USER"));
    printf("[SERVER]: Respond queue name: %s\n", resQueue);

    mq_req = mq_open(reqQueue, O_WRONLY);

    if(mq_req == (mqd_t)-1){
        perror("Can't open server queue");
        exit(-1);
    }

    printf("Writing messages to the server (write \"%s\" to stop):\n", STOP_MSG);

    do {
        printf("> ");
        fgets(reqBuffer, MAX_SIZE, stdin);

        if(mq_send(mq_req, reqBuffer, MAX_SIZE, 0) != 0){
            perror("Can't send request");
            exit(-1);
        }

        if(strncmp(reqBuffer, STOP_MSG, strlen(STOP_MSG)) != 0){
            mq_res = mq_open(resQueue, O_CREAT | O_RDONLY, 0644, &attr);

            if(mq_res == (mqd_t)-1){
                perror("Can't open server respond queue");
                exit(-1);
            }

            ssize_t bytes_read;

            bytes_read = mq_receive(mq_res, resBuffer, MAX_SIZE, NULL);

            if(bytes_read < 0){
                perror("Can't recibe respond");
                exit(-1);
            }

            resBuffer[bytes_read] = '\0';

            printf("Respond: %d\n", (int) *resBuffer);
        }
    } while (!stop);

    if(mq_close(mq_req) == (mqd_t)-1){
        perror("Can't close server queue");
        exit(-1);
    }

    if(mq_close(mq_res) == (mqd_t)-1){
        perror("Can't close request queue");
        exit(-1);
    }

    return 0;
}
