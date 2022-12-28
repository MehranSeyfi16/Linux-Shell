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
	/* Reset handler to catch SIGINT next time.
	Refer http://en.cppreference.com/w/c/program/signal */
	signal(SIGINT, sigintHandler);
	fprintf(stderr,"\n Cannot be terminated using Ctrl+C \n");
	// printf("\n Cannot be terminated using Ctrl+C \n");

	fflush(stdout);
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


