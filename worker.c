//
// Created by bull on 19-10-22.
//
//main que usa al fworker
// https://github.com/shaaadoow/Sistemas-Operativos/blob/main/Lab2/lab2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hash.h"

int main(int argc, char * argv[]){
    char buffer[150];
    int lineas = 0;
    int min_year = atoi(argv[1]);
    year ** tabla = crearHash(min_year);
    read(STDIN_FILENO,buffer, sizeof(char)*150);
    while (strcmp(buffer,"FIN")!=0) {

        lineas++;
        read(STDIN_FILENO,buffer, sizeof(char)*150);
    }
    printf("\nProceso %d = %d lineas\n",getpid(),lineas);
    return 0;
}