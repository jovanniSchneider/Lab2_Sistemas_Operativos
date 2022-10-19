//
// Created by jovan on 9/13/2022.
//
#include <stdio.h>
#include <string.h>//para armar la entrega
#include "gameList.h"



//Entradas: puntero del archivo intermedio creado por el padre y el puntero (long) para saber donde comenzar a leer
//Salidas: void
//Descripcion: lee los juegos correspondientes y los almacena
void leerArchivo(FILE * fp,long puntero,gamelist * lista){
    fseek(fp,puntero,SEEK_SET);//posicionamiento del puntero en la posicion correspondiente
    char string[150];
    game juego;
    fgets(string,150,fp);
    int year = getYear(string);
    do {
        //38400,Fallout: A Post Nuclear Role Playing Game,16,6.88,False,2015,False,Yes,No,No
        juego.ID = atoi(getGenerico(string,0));
        strcpy(juego.name,getGenerico(string,1));
        juego.ageRest = atoi(getGenerico(string,2));
        juego.price = getPrice(string);
        juego.comSoon = convertirBool(getGenerico(string,4));
        juego.year = getYear(string);
        juego.free = convertirBool(getGenerico(string,6));
        juego.win = convertirBool(getGenerico(string,7));
        juego.mac = convertirBool(getGenerico(string,8));
        juego.lix = convertirBool(getGenerico(string,9));
        //printf("%d,%s,%d,%f,%d,%d,%d,%d,%d,%d\n",juego.ID,juego.name,juego.ageRest,juego.price,juego.comSoon,juego.year,juego.free,juego.win,juego.mac,juego.lix);
        insertarIniciogame(lista,juego);
    }while(fgets(string,150,fp)!=NULL && getYear(string) ==year);
    
}

//Entradas: array
//Salidas: char*
//Descripcion: busca los juegos con mayor y menor precio dentro de un array
char * buscarTopAndBottom(char * string, gamelist * lista){
    float maxPrice;
    float minPrice;
    char minGame[50];
    char maxGame[50];
    strcpy(string,"Año: ");
    char stringAux[200] = "\nJuego mas caro: ";
    char year[10];
    sprintf(year,"%d",lista->inicio->dato.year);
    strcat(string, year);
    strcat(string,stringAux);
    maxPrice = lista->inicio->dato.price;
    minPrice = lista->inicio->dato.price;
    strcpy(minGame,lista->inicio->dato.name);
    strcpy(maxGame,lista->inicio->dato.name);
    if (!esListaVaciaGame(lista))
    {
        nodogame * auxiliar=lista->inicio;
        while (auxiliar!=NULL)
        {
            if(auxiliar->dato.price > maxPrice){
                maxPrice = auxiliar->dato.price;
                strcpy(maxGame,auxiliar->dato.name);
            }
            if(auxiliar->dato.price < minPrice){
                minPrice = auxiliar->dato.price;
                strcpy(minGame,auxiliar->dato.name);
            }
            auxiliar=auxiliar->siguiente;
        }
    }
    strcat(string,maxGame);
    strcpy(stringAux,"\nJuego mas barato: ");
    strcat(string,stringAux);
    strcat(string,minGame);
    strcpy(stringAux,"\n");
    strcat(string,stringAux);
    return string;
}

//Entradas: string x array
//Salidas: void
//Descripcion: calcula el primedio de precios y compatibilidad de los SO de un array de juegos
void calcularPromedios(char * string, gamelist * lista){
    float cont = 0;
    float suma = 0;
    float win;
    float mac;
    float lix;
    char sumaString[10];
    char stringAux[50];
    if (!esListaVaciaGame(lista))
    {
        nodogame * auxiliar=lista->inicio;
        while (auxiliar!=NULL)
        {
            if(auxiliar->dato.win == 1){
                win++;
            }
            if(auxiliar->dato.mac == 1){
                mac++;
            }
            if(auxiliar->dato.lix == 1){
                lix++;
            }
            cont++;
            suma+= auxiliar->dato.price;
            auxiliar=auxiliar->siguiente;
        }
    }
    win/=cont;
    mac/=cont;
    lix/=cont;
    suma = suma/cont;
    gcvt(suma,4,sumaString);
    strcpy(stringAux,"Promedio de precios: ");
    strcat(string,stringAux);
    strcat(string,sumaString);

    strcpy(stringAux,"\nWindows: ");
    strcat(string,stringAux);
    sprintf(stringAux,"%d",(int)(win*100));
    strcat(string,stringAux);
    //concatenar % de windows
    strcpy(stringAux,"% ");
    strcat(string,stringAux);

    //% de mac
    strcpy(stringAux,"Mac: ");
    strcat(string,stringAux);
    sprintf(stringAux,"%d",(int)(mac*100));
    strcat(string,stringAux);
    strcpy(stringAux,"% ");
    strcat(string,stringAux);

    //% de linux
    strcpy(stringAux,"Linux: ");
    strcat(string,stringAux);
    sprintf(stringAux,"%d",(int)(lix*100));
    strcat(string,stringAux);
    strcpy(stringAux,"%\n");
    strcat(string,stringAux);
}

//Entradas: string x array
//Salidas: void
//Descripcion: escribe el total de juegos gratis en un string
void juegosFree(char * string, gamelist * lista) {
    char stringAux[20];
    char aux[5]="\n";
    int contador=0;
    if (!esListaVaciaGame(lista))
    {
        nodogame * auxiliar=lista->inicio;
        while (auxiliar!=NULL)
        {

            if(auxiliar->dato.free==1){//si es gratis
                if(contador==0){
                    strcpy(stringAux,"Juegos gratis:\n");
                    strcat(string,stringAux);
                    contador++;
                }
                strcat(string,auxiliar->dato.name);//se agrega el nombre
                strcat(string,aux);
            }
            auxiliar=auxiliar->siguiente;
        }
    }
}