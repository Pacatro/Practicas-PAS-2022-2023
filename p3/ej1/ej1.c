#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

void printUserInfo(char *lgn);
void printGroupInfo(char *lgn);

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

    command = getopt_long(argc, argv, "u:g:amsh", long_options, NULL);

    if(command != -1){
        //printf("optind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);

        switch(command){
            case 'u':
                uvalue = optarg;
                printUserInfo(uvalue);
            break;

            case 'g':
                gvalue = optarg;
                printGroupInfo(gvalue);
            break;

            case 'a':
                aflag = true;
                
                if(aflag){
                    char *lgn = getenv("USER");
                    
                    if(lgn == NULL || lgn == ""){
                        fprintf(stderr, "Failed to get user information.\n");
                        exit(1);
                    }

                    printUserInfo(lgn);
                }
            break;

            case 'm':
                mflag = true;

                if(mflag){
                    char *lgn = getenv("USER");
                    
                    if(lgn == NULL){
                        fprintf(stderr, "Failed to get group information.\n");
                        exit(1);
                    }

                    printGroupInfo(lgn);
                }
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

void printUserInfo(char *lgn){
    struct passwd *pw;

    for(int i = 0; lgn[i]; i++){
        if(!isalpha(lgn[i])){
            int uid = atoi(lgn);
            pw = getpwuid(uid);
        } else { 
            pw = getpwnam(lgn);
        }
    }

    /* Tambien funciona así
    
    if(!isalpha(lgn[1])){
        int uid = atoi(lgn);
        pw = getpwuid(uid);
    } else { 
        pw = getpwnam(lgn);
    }
    */

    if(pw == NULL){
        fprintf(stderr, "Failed to get user information.\n");
        exit(1);
    }

    printf("Name: %s\n", pw->pw_gecos);
    printf("Login: %s\n", pw->pw_name);
    printf("Password: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Home: %s\n", pw->pw_dir);
    printf("Shell: %s\n", pw->pw_shell);
    printf("Principal group number %d\n", pw->pw_gid);
}

void printGroupInfo(char *lgn){
    struct group *gr;
    
    for(int i = 0; lgn[i]; i++){
        if(!isalpha(lgn[i])){
            int gid = atoi(lgn);
            gr = getgrgid(gid);
        } else { 
            gr = getgrnam(lgn);
        }
    }

    /* Tambien funciona así
    
    if(!isalpha(lgn[1])){
        int gid = atoi(lgn);
        gr = getgrgid(gid);
    } else { 
        gr = getgrnam(lgn);
    }
    */

    if(gr == NULL){
        fprintf(stderr, "Failed to get group information.\n");
        exit(1);
    }

    printf("Name: %s\n", gr->gr_name);
    printf("Password: %s\n", gr->gr_passwd);
    printf("GID: %d\n", gr->gr_gid);
    //printf("Member list: %s\n", gr->gr_mem[1]); --> necesario?
}