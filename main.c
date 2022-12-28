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


int main() {
    char inputString[100];
    char string[100];
    takeInput(string);
    firstWord(string);

    return 0;

}


