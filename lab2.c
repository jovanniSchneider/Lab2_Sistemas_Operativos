#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "functions.c"

// Entradas: parametros ingresados por consola los cuales podrian variar segun la entrada del usuario
// Salidas: int 0 o 1
// Descripción: verifica los parametros ingresados por consola para corroborar que cumplan ciertos parametros para el
// correcto funcionamiento del codigo.
int validate(int argc, char * argv[], char input[], char output[], char min_price[], char min_year[], char flag[],char workers[]){
    int opt;
    while((opt = getopt(argc,argv,":b i: o: d: p: n: :h"))!= -1){
        switch (opt) {
            case 'i':
                strcpy(input,optarg);
                break;
            case 'o':
                strcpy(output,optarg);
                break;
            case 'd':
                if(digitValidate(optarg)) {
                    printf("min year validate antes del str %s\n", min_year);
                    printf("min year validate %s\n", optarg);
                    strcpy(min_year, optarg);
                    printf("min year validate %s\n", min_year);
                }
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'p':
                if(digitValidate(optarg))
                    strcpy(min_price,optarg);
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'b':
                strcpy(flag,"1");
                break;
            case 'n':
                if(digitValidate(optarg))
                    strcpy(workers,optarg);
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'h':
                printf("-i: input file including extension\n"
                       "-o: output file including extension\n"
                       "-d: game start year, must be a number\n"
                       "-p: minimum game price, must be in dollars\n"
                       "-b: details flag (show additional information on console)\n"
                       "-n: number of workers process\n"
                       "-h: help\n");
                exit(0);
                break;
            case '?':
                printf("Unknown option: %c\n",optopt);
                break;
            case ':':
                printf("Missing arg for %c\n",optopt);
        }
    }
    if(*min_year == -1) {
        return 0;
    }
    return 1;
}

int main(int argc, char * argv[]) {
    char input[30] = "datos_juegos_1000.csv";
    char output[30] = "output.txt";
    char min_price[4] = "0";
    char min_year[5] = "0";
    char flag[2] = "0";
    char workers[3];
    if(validate(argc,argv,input,output,min_price,min_year,flag,workers)){
        printf("min year main lab %s\n", min_year);
        execlp("./broker","./broker", input,output,min_price,min_year,flag,workers,NULL);
        return 0;
    }
    return -1;
}