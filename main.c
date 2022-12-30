#include <stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

void directory()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
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
        printf("\nExnlited Successfully\n");
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

int handlePipe(char* str, char** pipedString)
{
    for (int i = 0; i < 2; i++) {
        pipedString[i] = strsep(&str, "|");
        if (pipedString[i] == NULL)
            break;
    }
    if (pipedString[1] != NULL)
        return 1;
    else {
        return 0;
    }
}

int processString(char* str, char** parsed, char** parsedpipe){

    char* pipedString[2];
    int pipedreturend = 0;
    pipedreturend = handlePipe(str, pipedString);

    if (pipedreturend) {
        parseSpace(pipedString[0], parsed);
        parseSpace(pipedString[1], parsedpipe);

    }
    else {
        parseSpace(str, parsed);
    }

    if (commandHandler(parsed)){
        return 0;
    }
    else{
        return 1 + pipedreturend;
    }
}

int main(){
    char input[1000];
    char *parsedArguments[100];
    char* parsedArgumentsPiped[100];
    int returend = 0;

    signal(SIGINT, sigintHandler);
    FILE *filePointer ;

    while (1) {
        directory();
        if (receiveCommand(input)) {
            continue;
        }

	filePointer = fopen("pooooof.txt", "a");
	fputs(input,filePointer);
	fputs("\n",filePointer);
	fclose(filePointer);

	returend = processString(input, parsedArguments, parsedArgumentsPiped);
	
	if (returend == 1){
            pid_t pid = fork();

            if (pid == -1) {
                fprintf(stderr,"\nForking child failed..");
            }

            else if (pid == 0) {
                if (execvp(parsedArguments[0], parsedArguments) < 0) {
                    fprintf(stderr,"\nWrong command..");
                }

            }
            else {
                wait(NULL);
            }
        }

        if (returend == 2){

            int pipedFD[2];
            pid_t p1, p2;

            if (pipe(pipedFD) < 0){
                fprintf(stderr ,"\ninitialized failed");
            }

            p1 = fork();

            if (p1 < 0) {
                fprintf(stderr ,"\nfork error");
            }

            if (p1 == 0) {
                close(pipedFD[0]);
                dup2(pipedFD[1], STDOUT_FILENO);
                close(pipedFD[1]);

                if (execvp(parsedArguments[0], parsedArguments) < 0) {
                    fprintf(stderr ,"\nexecute command 1 failed");
                    exit(0);
                }
            }
            else {
                p2 = fork();

                if (p2 < 0) {
                    fprintf(stderr ,"\nfork failed");
                }

                if (p2 == 0) {
                    close(pipedFD[1]);
                    dup2(pipedFD[0], STDIN_FILENO);
                    close(pipedFD[0]);

                    if (execvp(parsedArgumentsPiped[0], parsedArgumentsPiped) < 0) {
                        fprintf(stderr ,"\execute command 2 failed");
                        exit(0);
                    }
                }
                else {
                    wait(NULL);
                    wait(NULL);
                }
            }
        }
    }
    return 0;
}
