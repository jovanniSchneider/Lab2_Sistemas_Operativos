//
// Created by bull on 19-10-22.
//
//main que usa fbroker
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
    printf("input %s\n",input);
    printf("output %s\n",output);
    printf("min_price %f\n",min_price);
    printf("min_year %d\n",min_year);
    printf("flag %d\n",flag);
    printf("workers %d\n",workers);

    //genera n pipes con dupe
    //genera los n workers
    //lee el csv (linea x linea)
    return 0;
}