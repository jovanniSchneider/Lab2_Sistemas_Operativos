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
    if(flag){
        printf("input %s\n",input);
        printf("output %s\n",output);
        printf("min_price %f\n",min_price);
        printf("min_year %d\n",min_year);
        printf("workers %d\n",workers);
    }
    //genera n pipes con dupe
    int pipes[workers][2];
    for(int i = 0; i<=workers;i++){
        pipe(pipes[i]);
        //genera los n workers
        pid = fork();
        if(pid == 0){
            close(pipes[i][1]);
            dup2(pipes[i][0],STDIN_FILENO);
            //close(pipes[i][0]);
            execl("./worker", "./worker", NULL);
        }else {
            close(pipes[i][0]);
        }
    }
    leerCSV(input,min_year,min_price,pipes,workers);
    //lee el csv (linea x linea)
    return 0;
}