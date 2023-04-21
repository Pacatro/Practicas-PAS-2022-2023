#include "ej3_common.h"

int main(int argc, char **argv){
    mqd_t mq_req;
    mqd_t mq_res;

    struct mq_attr attr;

    char buffer[MAX_SIZE];

    int stop = 0;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;

    char reqQueue[200];
    char resQueue[200];    

    sprintf(reqQueue, "%s-%s", REQ_QUEUE, getenv("USER"));
    printf("[SERVER]: Request queue name: %s\n", reqQueue);

    sprintf(resQueue, "%s-%s", RES_QUEUE, getenv("USER"));
    printf("[SERVER]: Respond queue name: %s\n", resQueue);

    mq_req = mq_open(reqQueue, O_CREAT | O_RDONLY, 0644, &attr);

    if(mq_req == (mqd_t)-1){
        perror("Can't open server request queue");
        exit(-1);
    }

    do {
        ssize_t bytes_read;

        bytes_read = mq_receive(mq_req, buffer, MAX_SIZE, NULL);

        if(bytes_read < 0){
            perror("Can't recibe request");
            exit(-1);
        }

        buffer[bytes_read] = '\0';

        if(strncmp(buffer, STOP_MSG, strlen(STOP_MSG)) == 0){
            stop = 1;
        } else {
            printf("Req: %s\n", buffer);

            int charsNum = strlen(buffer) - 1;

            mq_res = mq_open(resQueue, O_WRONLY);

            if(mq_res == (mqd_t)-1){
                perror("Can't open server respond queue");
                exit(-1);
            }

            if(mq_send(mq_res, (char*) &charsNum, MAX_SIZE, 0)){
                perror("Can't send respond");
                exit(-1);
            }
        }
    } while (!stop);

    if(mq_close(mq_req) == (mqd_t)-1){
        perror("Can't close request queue");
        exit(-1);
    }

    if(mq_close(mq_res) == (mqd_t)-1){
        perror("Can't close request queue");
        exit(-1);
    }

    if(mq_unlink(reqQueue) == (mqd_t)-1){
        perror("Can't remove request queue");
        exit(-1);
    }

   

    return 0;
}