//
// Created by bull on 19-10-22.
//
//main que usa al fworker
// https://github.com/shaaadoow/Sistemas-Operativos/blob/main/Lab2/lab2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
    char buffer[150];
    char lineas[10000] = "";
    do {
        read(STDIN_FILENO,buffer, sizeof(char)*150);
        strcat(lineas,buffer);
        strcat(lineas,"\n");
    } while (strcmp(buffer,"Fin")!=0);
    printf("\nSoy el proceso %d y me tocaron las lineas\n%s",getpid(),lineas);
    return 0;
}