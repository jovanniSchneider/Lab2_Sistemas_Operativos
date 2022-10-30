//
// Created by jovan on 9/13/2022.
//
#include <stdio.h>
#include <string.h>//para armar la entrega
#include "hash.h"

char * getGenerico(char * string, int posicion){
    char string2[150];
    strcpy(string2,string);
    char separacion[2] = ",";
    char * pedacito;
    pedacito = strtok(string2,separacion);//980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    for (int i = 0; i<posicion;i++){
        pedacito = strtok(NULL,separacion);
    }
    return pedacito;
}

void trabajarLinea(year ** tabla, char * linea, int min_year){
    //980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    //ID=1, Nombre=2, Rest=3, Price=4, year=6, Free=7, Win=8, Mac=9, Linux = 10
    int year = atoi(getGenerico(linea,6));
    int position = hashFunction(year,min_year);
    if(tabla[hashFunction(year,min_year)]->access != 1){
        tabla[position]->access = 1;
        tabla[position]->year = year;
        tabla[position]->
    }
    if()

}


//Entradas: array
//Salidas: char*
//Descripcion: busca los juegos con mayor y menor precio dentro de un array
//char * buscarTopAndBottom(char * string, gamelist * lista){
//    float maxPrice;
//    float minPrice;
//    char minGame[50];
//    char maxGame[50];
//    strcpy(string,"Año: ");
//    char stringAux[200] = "\nJuego mas caro: ";
//    char year[10];
//    sprintf(year,"%d",lista->inicio->dato.year);
//    strcat(string, year);
//    strcat(string,stringAux);
//    maxPrice = lista->inicio->dato.price;
//    minPrice = lista->inicio->dato.price;
//    strcpy(minGame,lista->inicio->dato.name);
//    strcpy(maxGame,lista->inicio->dato.name);
//    if (!esListaVaciaGame(lista))
//    {
//        nodogame * auxiliar=lista->inicio;
//        while (auxiliar!=NULL)
//        {
//            if(auxiliar->dato.price > maxPrice){
//                maxPrice = auxiliar->dato.price;
//                strcpy(maxGame,auxiliar->dato.name);
//            }
//            if(auxiliar->dato.price < minPrice){
//                minPrice = auxiliar->dato.price;
//                strcpy(minGame,auxiliar->dato.name);
//            }
//            auxiliar=auxiliar->siguiente;
//        }
//    }
//    strcat(string,maxGame);
//    strcpy(stringAux,"\nJuego mas barato: ");
//    strcat(string,stringAux);
//    strcat(string,minGame);
//    strcpy(stringAux,"\n");
//    strcat(string,stringAux);
//    return string;
//}

//Entradas: string x array
//Salidas: void
//Descripcion: calcula el primedio de precios y compatibilidad de los SO de un array de juegos
//void calcularPromedios(char * string, gamelist * lista){
//    float cont = 0;
//    float suma = 0;
//    float win;
//    float mac;
//    float lix;
//    char sumaString[10];
//    char stringAux[50];
//    if (!esListaVaciaGame(lista))
//    {
//        nodogame * auxiliar=lista->inicio;
//        while (auxiliar!=NULL)
//        {
//            if(auxiliar->dato.win == 1){
//                win++;
//            }
//            if(auxiliar->dato.mac == 1){
//                mac++;
//            }
//            if(auxiliar->dato.lix == 1){
//                lix++;
//            }
//            cont++;
//            suma+= auxiliar->dato.price;
//            auxiliar=auxiliar->siguiente;
//        }
//    }
//    win/=cont;
//    mac/=cont;
//    lix/=cont;
//    suma = suma/cont;
//    gcvt(suma,4,sumaString);
//    strcpy(stringAux,"Promedio de precios: ");
//    strcat(string,stringAux);
//    strcat(string,sumaString);
//
//    strcpy(stringAux,"\nWindows: ");
//    strcat(string,stringAux);
//    sprintf(stringAux,"%d",(int)(win*100));
//    strcat(string,stringAux);
//    //concatenar % de windows
//    strcpy(stringAux,"% ");
//    strcat(string,stringAux);
//
//    //% de mac
//    strcpy(stringAux,"Mac: ");
//    strcat(string,stringAux);
//    sprintf(stringAux,"%d",(int)(mac*100));
//    strcat(string,stringAux);
//    strcpy(stringAux,"% ");
//    strcat(string,stringAux);
//
//    //% de linux
//    strcpy(stringAux,"Linux: ");
//    strcat(string,stringAux);
//    sprintf(stringAux,"%d",(int)(lix*100));
//    strcat(string,stringAux);
//    strcpy(stringAux,"%\n");
//    strcat(string,stringAux);
//}

//Entradas: string x array
//Salidas: void
//Descripcion: escribe el total de juegos gratis en un string
//void juegosFree(char * string, gamelist * lista) {
//    char stringAux[20];
//    char aux[5]="\n";
//    int contador=0;
//    if (!esListaVaciaGame(lista))
//    {
//        nodogame * auxiliar=lista->inicio;
//        while (auxiliar!=NULL)
//        {
//
//            if(auxiliar->dato.free==1){//si es gratis
//                if(contador==0){
//                    strcpy(stringAux,"Juegos gratis:\n");
//                    strcat(string,stringAux);
//                    contador++;
//                }
//                strcat(string,auxiliar->dato.name);//se agrega el nombre
//                strcat(string,aux);
//            }
//            auxiliar=auxiliar->siguiente;
//        }
//    }
//}