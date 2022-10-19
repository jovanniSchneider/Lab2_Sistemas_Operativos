//
// Created by bull on 19-10-22.
//
//main que usa al fworker
// https://github.com/shaaadoow/Sistemas-Operativos/blob/main/Lab2/lab2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    char buffer[100];
    read(STDIN_FILENO, buffer, sizeof(char)*100);

    close(STDIN_FILENO);
    printf("%s\n",buffer);
    return 0;
}