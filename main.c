#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <guesser.h>

int main(int argc, char *argv[]){
    size_t bufsize = 65;
    char *buff = (char*)malloc(bufsize*sizeof(char));
    memset(buff,'\0',bufsize);
    printf("Give me the password(no longer than 64 characters):\n");
    getline(&buff,&bufsize,stdin);
    run(buff);
    return 0;
}