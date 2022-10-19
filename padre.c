#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"


//Entradas Char* del nombre del archivo
//Salidas TdaLista ** que trabaja como una tabla hash
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este csv se almacena en una tabla hash segun
//            el year del juego en cuestion
TDAlista ** leerCSV(char nombreArchivo[30],int min_year,int min_price){
    FILE* fp;
    fp= fopen(nombreArchivo,"r");
    TDAlista** hash=crearHash(min_year);
    char string[150];
    while(fgets(string,150,fp)!=NULL){
        agregarDatoHash(string,hash,min_year,min_price);
    }
    fclose(fp);
    return hash;
}
//Entradas TDALista** que simula una tabla hash,char* para el nombre del archivo
//Salidas int que representa la cantidad de years que si tienen juegos
//Descripcion crea un archivo que contiene la info de la tabla hash con el nombre ingresado, ademas de calcular
//             los years con juegos, tambien dejando constancia de donde comienza cada year mediante ftell
int crearArchivo(TDAlista** hash, char * nombreSalida, int fd[2],int flag,int min_year){
    int largoHash = getActualYear()-min_year+5;
    FILE * fp;
    fp = fopen(nombreSalida, "w");
    int cont = 0;
    long puntero;
    for(int i=0;i<largoHash;i++){
        if(!esListaVacia(hash[i])) {
            puntero = ftell(fp);
            recorrerLista(hash[i],fp,flag);
            cont++;
            write(fd[1],&puntero,sizeof(puntero));
        }
        liberarLista(hash[i]);
    }
    free(hash);
    fclose(fp);
    return cont;
}