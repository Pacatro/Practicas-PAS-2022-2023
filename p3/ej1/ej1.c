#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

int main(int argc, char **argv){
    int command;

    static struct option long_options[] = {
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0}
    };

    bool aflag = false;
    bool mflag = false;
    bool sflag = false;
    bool hflag = false;

    char *uvalue = NULL;
    char *gvalue = NULL;

    while((command = getopt_long(argc, argv, "u:g:amsh", long_options, NULL)) != -1){
        printf("optind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);

        switch(command){
            case 'u':
                uvalue = optarg;
            break;

            case 'g':
                gvalue = optarg;
            break;

            case 'a':
                aflag = true;
            break;

            case 'm':
                mflag = true;
            break;

            case 's':
                sflag = true;
            break;

            case 'h':
                hflag = true;
            break;

            case '?':
                if (optopt == 'u' || optopt == 'g')
                    fprintf (stderr, "La opción %c requiere un argumento.\n", optopt);
            break;

            default: abort();
        }
    }
    
    return 0;
    
}