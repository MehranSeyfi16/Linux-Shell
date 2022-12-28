#include <stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

void firstWord(char *string){
    char *found;
    found= strsep(&string," ");
    printf("%s\n",found);
}

int takeInput(char* str) {
    scanf("%s", str);
    return 0;
}

void sigintHandler(int sig_num){
    signal(SIGINT, sigintHandler);
    fprintf(stderr,"\n Cannot be terminated using Ctrl+C \n");
    fflush(stdout);
}

int commandHandler(char** parsed){

    int ncmds = 8, i, cmdNumber = 0;
    char* cmdlists[ncmds];
    cmdlists[0] = "exit";
    cmdlists[1] = "cd";
    cmdlists[2] = "tl";
    cmdlists[3] = "mf";
    cmdlists[4] = "rs";
    cmdlists[5] = "uc";
    cmdlists[6] = "nl";
    cmdlists[7] = "fw";

    for (i = 0; i < ncmds; i++) {
        if (strcmp(parsed[0], cmdlists[i]) == 0) {
            cmdNumber = i + 1;
            break;
        }
    }
    if(cmdNumber==1){
        printf("\nEXited Successfully\n");
        exit(0);
    }
    if(cmdNumber==2){
        chdir(parsed[1]);
        return 1;
    }
    if(cmdNumber==3){
        parsed[0] = "head";
        parsed[2] = NULL;
        return 0;

    }
    if(cmdNumber==4){
        parsed[2] = parsed[1];
        parsed[0] = "awk";
        parsed[1] = "max < ++c[$0] {max = c[$0]; line = $0} END {print line}";
        parsed[3] = NULL;
        return 0;

    }
    if(cmdNumber==5){
        parsed[2] = parsed[1];
        parsed[0] = "sed";
        parsed[1] = "s/[[:blank:]$SPACES]//g";
        parsed[3] = NULL;
        return 0;

    }
    if(cmdNumber==6){
        parsed[3] = parsed[1];
        parsed[0] = "grep";
        parsed[1] = "-v";
        parsed[2] = "^#";
        parsed[4] = NULL;
        return 0;

    }
    if(cmdNumber==7){
        parsed[2] = parsed[1];
        parsed[0] = "wc";
        parsed[1] = "-l";
        parsed[3] = NULL;
        return 0;

    }
    if(cmdNumber==8){
        parsed[2] = parsed[1];
        parsed[0] = "awk";
        parsed[1] = "{print $1}";
        parsed[3] = NULL;
        return 0;

    }
    return 0;
}

int receiveCommand(char* str)
{
    char* buffer;
    buffer = readline("\n>>>> ");

    if (strlen(buffer) != 0) {
        add_history(buffer);
        strcpy(str, buffer);
        return 0;
    } else {
        return 1;
    }
}

void parseSpace(char* str, char** parsed){
    int i;

    for (i = 0; i < 100; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int main() {
    char inputString[100];
    char string[100];
    takeInput(string);
    firstWord(string);

    return 0;

}
