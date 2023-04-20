#include "functions.h"

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
                hflag = true;
            break;

            default: abort();
        }
    }

    if(((uvalue != NULL || gvalue != NULL) && aflag) || (uvalue != NULL && sflag) || (uvalue != NULL && gvalue != NULL)){
        fprintf(stderr, "Incompatible options.\n");
        hflag = true;
    }
    
    if(sflag && mflag){
        fprintf(stderr, "The --maingroup option only can be use with --user or --active.\n");
        hflag = true;
    }

    if(uvalue == NULL && gvalue == NULL && !aflag && !mflag && !sflag && !hflag){
        char *lgn = getenv("USER");
        
        if(lgn == NULL || lgn == ""){
            fprintf(stderr, "Failed to get user information.\n");
            hflag = true;
        }

        printf("User info:\n");
        printUserInfo(lgn);
        printf("\nGroup info:\n");
        printGroupInfo(lgn);
    }

    if(uvalue != NULL && !mflag){
        printUserInfo(uvalue);
    } 
    
    if (gvalue != NULL){
        printGroupInfo(gvalue);
    }
    
    if(aflag && !mflag){
        char *lgn = getenv("USER");
        
        if(lgn == NULL || lgn == ""){
            fprintf(stderr, "Failed to get user information.\n");
            exit(-1);
        }

        printUserInfo(lgn);
    } 
    
    if(mflag && uvalue != NULL){
        printGroupInfo(uvalue);
    }
    
    if(mflag && aflag){
        char *lgn = getenv("USER");
        
        if(lgn == NULL){
            fprintf(stderr, "Failed to get group information.\n");
            exit(-1);
        }

        printGroupInfo(lgn);
    }

    if(sflag){
        printAllGroupsInfo();
    }

    if(hflag){
        printHelp();
        return 0;
    }
    
    return 0;
}