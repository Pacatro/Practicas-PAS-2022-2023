#include <errno.h>
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <sys/wait.h>
#include <time.h>  
#include <unistd.h>

float generateRandom();

int main(){
    pid_t chilpid, flag;
    int status;
    int fildes[2];
    const int BSIZE = 100;
    float randSum;

    srand(time(NULL));

    status = pipe(fildes);
    if (status == -1) {
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }

    chilpid = fork();

    switch(chilpid){
        case -1:
            perror("Can't create child process.");
            exit(EXIT_FAILURE);
        case 0:
            //Close unnecessary fildes 
            if(close(fildes[0]) == -1){
                perror("CLose error");
                exit(EXIT_FAILURE);
            }

            printf("[CHILD]: I'm the child, PID: %d, PPID: %d\n", getpid(), getppid());
            float n1 = generateRandom();
            float n2 = generateRandom();
            float sum = n1 + n2;

            printf("[CHILD]: n1 = %f\n", n1);
            printf("[CHILD]: n2 = %f\n", n2);

            //Send sum
            if(write(fildes[1], &sum, sizeof(float)) == -1){
                perror("Write error.");
                exit(EXIT_FAILURE);
            }
            
            printf("[CHILD]: Sending sum...\n");

            //Close fildes[1]
            if(close(fildes[1]) == -1){
                perror("CLose error");
                exit(EXIT_FAILURE);
            }
            
            printf("[CHILD]: Pipe closed.\n");

            exit(EXIT_SUCCESS);
        default:
            printf("[FATHER]: I'm the father, PID: %d\n", getpid());
            //Close unnecessary fildes 
            if(close(fildes[1]) == -1){
                perror("CLose error");
                exit(EXIT_FAILURE);
            }
            
            //Read 
            if(read(fildes[0], &randSum, sizeof(float)) == -1){
                perror("Read error");
                exit(EXIT_FAILURE);
            }

            printf("[FATHER]: Sum = %f\n", randSum);

            if(close(fildes[0]) == -1){
                perror("CLose error");
                exit(EXIT_FAILURE);
            }

            printf("[FATHER]: Pipe closed.\n");
    }

    while ((flag = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("[FATHER]: Child with PID %ld finished, status = %d\n", (long int)flag, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) { // Para seniales como las de finalizar o matar
            printf("[FATHER]: Child with PID %ld finished, signal: %d\n", (long int)flag, WTERMSIG(status));
        }
    }

    if (flag == (pid_t)-1 && errno == ECHILD) {
        printf("Father process %d, no more child to wait. errno = %d, defined as: %s\n", getpid(), errno, strerror(errno));
    } else {
        printf("wait/waitpid error. errno = %d, defined as: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

float generateRandom(){
    float random = (float)rand()/(float)(RAND_MAX) * 5000;
    return random;
}