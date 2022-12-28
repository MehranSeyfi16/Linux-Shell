#include <stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#define MAXLIST 100 // max number of commands to be suppo
void firstWord(char *string){
    char *found;

    found= strsep(&string," ");
    printf("%s\n",found);
}

// Function to take input
int takeInput(char* str) {
    scanf("%s", str);
    return 0;
}

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num){
    signal(SIGINT, sigintHandler);
    fprintf(stderr,"\n Cannot be terminated using Ctrl+C \n");
    fflush(stdout);
}
int ownCmdHandler(char** parsed){
    printf("first");

    int NoOfOwnCmds = 8, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;
    printf("vfdgkjfhewl");
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "tl";
    ListOfOwnCmds[3] = "mf";
    ListOfOwnCmds[4] = "rs";
    ListOfOwnCmds[5] = "uc";
    ListOfOwnCmds[6] = "nl";
    ListOfOwnCmds[7] = "fw";


    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            printf("compare");

            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
        case 1:
            printf("\nGoodbye\n");
            exit(0);
        case 2:
            chdir(parsed[1]);
            return 1;
        case 3:
            parsed[0] = "head";
            parsed[2] = NULL;
            return 0;
        case 4:
            parsed[2] = parsed[1];
            parsed[0] = "awk";
            parsed[1] = "max < ++c[$0] {max = c[$0]; line = $0} END {print line}";
            return 0;
        case 5:
            parsed[2] = parsed[1];
            parsed[0] = "sed";
            parsed[1] = "s/[[:blank:]$SPACES]//g";
            parsed[3] = NULL;
            return 0;
        case 6:
            parsed[3] = parsed[1];
            parsed[0] = "grep";
            parsed[1] = "-v";
            parsed[2] = "^#";
            parsed[4] = NULL;
            return 0;
        case 7:
            printf("nl");

            parsed[2] = parsed[1];
            parsed[0] = "wc";
            parsed[1] = "-l";
            // parsed[2] = "<";
            parsed[3] = NULL;
            return 0;
        case 8:
            parsed[2] = parsed[1];
            parsed[0] = "awk";
            parsed[1] = "{print $1}";
            parsed[3] = NULL;
            return 0;
        default:
            break;
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

