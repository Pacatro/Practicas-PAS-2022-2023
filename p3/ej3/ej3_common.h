#ifndef EJ3_COMMON_H
#define EJ3_COMMON_H

#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>

#define REQ_QUEUE "/req_queue"
#define RES_QUEUE "/res_queue"
#define STOP_MSG "exit"
#define MAX_SIZE 1024

#endif