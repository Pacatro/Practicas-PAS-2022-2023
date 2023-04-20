#include "functions.h"

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

    if(pw == NULL){
        fprintf(stderr, "Failed to get user information.\n");
        exit(-1);
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

    if(gr == NULL){
        fprintf(stderr, "Failed to get group information.\n");
        exit(-1);
    }

    printf("Name: %s\n", gr->gr_name);
    printf("Password: %s\n", gr->gr_passwd);
    printf("GID: %d\n", gr->gr_gid);
    
    printf("Member list:\n");
    for(int i = 0; gr->gr_mem[i] != NULL; i++)
        printf(" - %s\n", gr->gr_mem[i]);
    
}

void printAllGroupsInfo(){
    FILE *file;
    char line[200];

    file = fopen("/etc/group", "r");

    if(file == NULL){
        fprintf(stderr, "Failed to open file.\n");
        exit(-1);
    }

    while(fgets(line, 200, file)){
        char gname[200];
        int posInit = strchr(line, ':') - line;

        strncpy(gname, line, posInit);
        gname[posInit] = '\0';

        printGroupInfo(gname);
        printf("\n");
    }

    fclose(file);
}

void printHelp(){
    printf("Options:\n");
    printf("-h, --help\t\t\tShow this help\n");
    printf("-u, --user (<name>|<uid>)\tGet user information\n");
    printf("-a, --active\t\t\tGet information about actual user\n");
    printf("-m, --maingroup\t\t\tIn addition to user information, print the information of their primary group\n");
    printf("-g, --group (<name>|<gid>)\tGet group information\n");
    printf("-s, --allgroup\t\t\tGet information about all the groups in the system\n");
}