#include "ej3_common.h"

void funcionLog(char *);
FILE *fLog = NULL;

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
    char msgbuff[200];   

    sprintf(reqQueue, "%s-%s", REQ_QUEUE, getenv("USER"));
    printf("[SERVER]: Request queue name: %s\n", reqQueue);

    sprintf(msgbuff, "[SERVER]: Request queue name: %s\n", reqQueue);
    funcionLog(msgbuff);

    sprintf(resQueue, "%s-%s", RES_QUEUE, getenv("USER"));
    printf("[SERVER]: Respond queue name: %s\n", resQueue);

    sprintf(msgbuff, "[SERVER]: Respond queue name: %s\n", resQueue);
    funcionLog(msgbuff);

    mq_req = mq_open(reqQueue, O_CREAT | O_RDONLY, 0644, &attr);

    if(mq_req == (mqd_t)-1){
        perror("Can't open server request queue");
        funcionLog("Can't open server request queue");
        exit(-1);
    }

    do {
        ssize_t bytes_read;

        bytes_read = mq_receive(mq_req, buffer, MAX_SIZE, NULL);

        if(bytes_read < 0){
            perror("Can't recibe request");
            funcionLog("Can't recibe request");
            exit(-1);
        }

        buffer[bytes_read] = '\0';

        if(strncmp(buffer, STOP_MSG, strlen(STOP_MSG)) == 0){
            stop = 1;
        } else {
            printf("[CLIENT]: %s\n", buffer);
            sprintf(msgbuff, "[CLIENT]: %s\n", buffer);
            funcionLog(msgbuff);

            int charsNum = strlen(buffer) - 1;

            mq_res = mq_open(resQueue, O_WRONLY);

            if(mq_res == (mqd_t)-1){
                perror("Can't open server respond queue");
                funcionLog("Can't open server respond queue");
                exit(-1);
            }

            if(mq_send(mq_res, (char*) &charsNum, MAX_SIZE, 0)){
                perror("Can't send respond");
                funcionLog("Can't send respond");
                exit(-1);
            }
        }
    } while (!stop);

    if(mq_close(mq_req) == (mqd_t)-1){
        perror("Can't close request queue");
        funcionLog("Can't close request queue");
        exit(-1);
    }

    if(mq_close(mq_res) == (mqd_t)-1){
        perror("Can't close request queue");
        funcionLog("Can't close request queue");
        exit(-1);
    }

    if(mq_unlink(reqQueue) == (mqd_t)-1){
        perror("Can't remove request queue");
        funcionLog("Can't remove request queue");
        exit(-1);
    }

   if(mq_unlink(resQueue) == (mqd_t)-1){
        perror("Can't remove respond queue");
        funcionLog("Can't remove respond queue");
        exit(-1);
    }

    return 0;
}

void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-servidor.txt");
    if (fLog == NULL) {
        fLog = fopen(nombreFichero, "at");
        if (fLog == NULL) {
            perror("Error abriendo el fichero de log");
            exit(1);
        }
    }

    // Obtener la hora actual
    t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

    // Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);

    // Escribir finalmente en el fichero
    resultado = fputs(mensajeAEscribir, fLog);
    if (resultado < 0)
        perror("Error escribiendo en el fichero de log");

    fclose(fLog);
    fLog = NULL;
}