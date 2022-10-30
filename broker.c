//
// Created by bull on 19-10-22.
//
//main que usa fbroker
#include "fbroker.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 * i input
 * o output
 * d year start
 * p minprice
 * n cant workers
 * b prints console
 */
int main(int argc, char * argv[]){
    char input[30];
    char output[30];
    strcpy(input,argv[1]);
    strcpy(output,argv[2]);
    float min_price = atof(argv[3]);
    int min_year = atoi(argv[4]);
    int flag = atoi(argv[5]);
    int workers = atoi(argv[6]);
    int pid;

//    int size = snprintf(NULL,0,"%p",tablaHash);
//    char * buffer = calloc(size+1,1);
//    sprintf(buffer,"%p",tablaHash);
    if(flag){
        printf("input %s\n",input);
        printf("output %s\n",output);
        printf("min_price %f\n",min_price);
        printf("min_year %d\n",min_year);
        printf("workers %d\n",workers);
    }
    //genera n pipes para enviar la info con dupe
    int pipesEscritura[workers][2];
    int pipesLectura[workers][2];
    int ja;
    int i;
    for( i = 0; i<workers;i++){
        pipe(pipesEscritura[i]);
        pipe(pipesLectura[i]);
        //genera los n workers
        pid = fork();
        if(pid == 0) {
            close(pipesEscritura[i][1]);
            dup2(pipesEscritura[i][0], STDIN_FILENO);
            dup2(pipesLectura[i][1], 121);
            fflush(stdout);
            ja = execlp("./worker", "./worker", argv[4], NULL);
            if(ja==-1)
                printf("error de execlp\n");
            exit(0);
        }else
            close(pipesEscritura[i][0]);
    }
    //lee el csv (linea x linea)
    leerCSV(input,min_year,min_price,pipesEscritura,workers);
    for( i=0;i<workers;i++){
        wait(NULL);
    }
    //ahora con todos los juegos entregados,se recolectan los resultados de cada worker
    year ** tablaHash = crearHash(min_year);
    //llamar a recolectar datos
    recolectarDatos(tablaHash,pipesLectura,workers,min_year);
    //pasar de la tabla al txt de salida


    return 0;
}