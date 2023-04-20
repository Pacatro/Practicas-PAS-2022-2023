#ifndef FUNCTIONS_H
#define FUNCTIONS_H
    #include <pwd.h>
    #include <grp.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <getopt.h>
    #include <stdbool.h>
    #include <ctype.h>
    #include <string.h>

    void printUserInfo(char *lgn);
    void printGroupInfo(char *lgn);
    void printAllGroupsInfo();
    void printHelp();

#endif