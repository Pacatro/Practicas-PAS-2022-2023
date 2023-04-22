#include "ej3_common.h"

void funcionLog(char *);
void exitChat(int signal, char resBuffer[MAX_SIZE]);
FILE *fLog = NULL;
mqd_t mq_req;
mqd_t mq_res;

int main(int argc, char **argv){
    int stop = 0;

    char reqBuffer[MAX_SIZE];
    char resBuffer[MAX_SIZE];

    struct mq_attr attr;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;

    char reqQueue[200];
    char resQueue[200];
    char msgbuff[200];

    sprintf(reqQueue, "%s-%s", REQ_QUEUE, getenv("USER"));
    printf("[CLIENT]: Request queue name: %s\n", reqQueue);
    
    sprintf(msgbuff, "[CLIENT]: Request queue name: %s\n", reqQueue);
    funcionLog(msgbuff);

    sprintf(resQueue, "%s-%s", RES_QUEUE, getenv("USER"));
    printf("[CLIENT]: Respond queue name: %s\n", resQueue);

    sprintf(msgbuff, "[CLIENT]: Respond queue name: %s\n", resQueue);
    funcionLog(msgbuff);

    mq_req = mq_open(reqQueue, O_WRONLY);

    if(mq_req == (mqd_t)-1){
        perror("Can't open server request queue");
        funcionLog("Can't open server request queue");
        exit(-1);
    }

    printf("[CLIENT]: Writing messages to the server (write \"%s\" to stop):\n", STOP_MSG);
    sprintf(msgbuff, "[CLIENT]: Writing messages to the server (write \"%s\" to stop):\n", STOP_MSG);
    funcionLog(msgbuff);

    if(signal(SIGTERM, exitChat) == SIG_ERR){
        perror("SIGTERM error");
        funcionLog("SIGTERM error");
        exit(-1);
    }

    if(signal(SIGINT, exitChat) == SIG_ERR){
        perror("SIGINT error");
        funcionLog("SIGINT error");
        exit(-1);
    }


    do {
        printf("> ");
        fgets(reqBuffer, MAX_SIZE, stdin);

        if(strncmp(reqBuffer, STOP_MSG, strlen(STOP_MSG)) == 0)
            exitChat(0, resBuffer);

        if(mq_send(mq_req, reqBuffer, MAX_SIZE, 0) != 0){
            perror("Can't send request");
            funcionLog("Can't send request");
            exit(-1);
        }

        mq_res = mq_open(resQueue, O_CREAT | O_RDONLY, 0644, &attr);

        if(mq_res == (mqd_t)-1){
            perror("Can't open server respond queue");
            funcionLog("Can't open server respond queue");
            exit(-1);
        }

        ssize_t bytes_read;

        bytes_read = mq_receive(mq_res, resBuffer, MAX_SIZE, NULL);

        if(bytes_read < 0){
            perror("Can't recibe respond");
            funcionLog("Can't recibe respond");
            exit(-1);
        }

        resBuffer[bytes_read] = '\0';

        printf("[SERVER]: Number of characters received: %d\n", (int) *resBuffer);
        sprintf(msgbuff, "[SERVER]: Number of characters received: %d\n", (int) *resBuffer);
        funcionLog(msgbuff);

    } while (!stop);

    return 0;
}

void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-cliente.txt");
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

void exitChat(int signal, char resBuffer[MAX_SIZE]){
    char msgbuff[200];

    sprintf(msgbuff, "[CLIENT]: Signal received: %d\n", signal);
    funcionLog(msgbuff);

    sprintf(msgbuff, "%s\n", STOP_MSG);

    printf("MESSAGE: %s", msgbuff);

    if(mq_send(mq_req, msgbuff, MAX_SIZE, 0) != 0){
        perror("Can't send exit message");
        funcionLog("Can't send exit message");
        exit(-1);
    }

    funcionLog("[CLIENT]: Stop message sent to server\n");

    if(mq_close(mq_res) == (mqd_t)-1){
        perror("Can't close request queue");
        funcionLog("Can't close request queue");
        exit(-1);
    }

    if(mq_close(mq_req) == (mqd_t)-1){
        perror("Can't close server queue");
        funcionLog("Can't close server queue");
        exit(-1);
    }

    if(fLog != NULL)
        fclose(fLog);
}