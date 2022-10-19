#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "functions.c"


int main(int argc, char * argv[]) {
    char input[30] = "datos_juegos_1000.csv";
    char output[30] = "output.txt";
    char min_year[5] = "0";
    char flag[2] = "0";
    char workers[3];
    char min_price[8] = "0";
    if(validate(argc,argv,input,output,min_year,flag,workers,min_price)){
        execlp("./broker","./broker", input,output,min_price,min_year,flag,workers,NULL);
        return 0;
    }
    return -1;
}