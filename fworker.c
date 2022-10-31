//
// Created by jovan on 9/13/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>//para armar la entrega
#include "hash.h"

// Entradas: char* (que representa un juego) x int
// Salidas: char*
// Descripción: realiza strtok una cantida N de veces para obtener un dato del juego
char * getGenerico(char string[250], int posicion){
    char string2[250];
    strcpy(string2,string);
    char separacion[2] = ",";
    char * pedacito;
    pedacito = strtok(string2,separacion);//980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    for (int i = 0; i<posicion;i++){
        pedacito = strtok(NULL,separacion);
    }
    return pedacito;
}

// Entradas: char*
// Salidas: int
// Descripción: transforma un char* a bool(int 0 o 1)
int convertirBool(char string[10]) {
    //True,False,Yes,No
    if((strcmp(string,"True")==0)||(strcmp(string,"Yes")==0)||(strcmp(string,"Yes\n")==0)){
        return 1;
    }if((strcmp(string,"False")==0)||(strcmp(string,"No")==0)||(strcmp(string,"No\n")==0)){
        return 0;
    }
    return -1;
}

// Entradas: char*
// Salidas: void
// Descripción: trabaja un char* del tipo juego, para agregarlo a la tabla hash en la posicion correspondiente
void trabajarLinea(year ** tabla, char linea[250], int min_year){
    //980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    //ID=0, Nombre=1, Rest=2, Price=3, year=5, Free=6, Win=7, Mac=8, Linux = 9
    int year = atoi(getGenerico(linea,5));
    //printf("%s\nproceso %d year %d\n",linea,getpid(),year);
    int position = hashFunction(year,min_year);
    char string[250];
    if(tabla[position]->access != 1) {
        tabla[position]->access = 1;
        tabla[position]->year = year;
        strcpy(string, getGenerico(linea, 1));
        strcat(string, "*");
        strcat(string, getGenerico(linea, 3));
        strcpy(tabla[position]->moreExpensive, string);
        strcpy(tabla[position]->cheaper, string);
        tabla[position]->priceEx = atof(getGenerico(linea, 3));
        tabla[position]->priceCh = tabla[position]->priceEx;
    }else{
        //printf("voy\n");
        //Se guarda nombre y precio en un string
        strcpy(string, getGenerico(linea,1));
        strcat(string,"*");
        strcat(string, getGenerico(linea,3));
        //Ve si el juego es mas caro
        if(tabla[position]->priceEx < atof(getGenerico(linea,3))){
            strcpy(tabla[position]->moreExpensive,string);
            tabla[position]->priceEx = atof(getGenerico(linea,3));

        }//Ve si es el juego es mas barato
        else if(tabla[position]->priceCh > atof(getGenerico(linea,3))){
            strcpy(tabla[position]->cheaper,string);
            tabla[position]->priceCh = atof(getGenerico(linea,3));
        }
        //aumenta la cantidad de juegos procesados
        tabla[position]->totalGamesYear++;
        //year nombrecaro preciocaro nombrebarato preciobarato gratis1,gratis2....,gratisN windows mac linux gamesYear
        // 1      2           3          4              5              6                    7       8    9       10
    }
    //Verifica si esta para windows
    if(convertirBool(getGenerico(linea,7))){
        tabla[position]->win ++;
    }
    //Verifica si esta para mac
    if(convertirBool(getGenerico(linea,8))){
        tabla[position]->mac ++;
    }
    //Verifica si esta para linux
    if(convertirBool(getGenerico(linea,9))){
        tabla[position]->lix ++;
    }
    //Verifica si esta gratis
    if(convertirBool(getGenerico(linea,6))){
        if(strcmp(tabla[position]->free,"")!=0){
            strcat(tabla[position]->free, ",");
        }
        strcat(tabla[position]->free, getGenerico(linea,1));
    }
//    //printf("%d %d %s\n",getpid(), year,tabla[position]->moreExpensive);
}

void toString(year * anio,char string[1000]){
    char string2[13];
    strcpy(string,"");
    if(anio->access!=0){
        sprintf(string,"%d", anio->year);
        strcat(string,"*");
        strcat(string,anio->moreExpensive);
        strcat(string,"*");
        strcat(string, anio->cheaper);
        strcat(string, "*");
        if(strcmp(anio->free,"")==0)
            strcat(string,"@");
        strcat(string, anio->free);
        strcat(string, "*");
        gcvt(anio->win,5,string2);
        strcat(string,string2);
        strcat(string, "*");
        gcvt(anio->mac,5,string2);
        strcat(string,string2);
        strcat(string, "*");
        gcvt(anio->lix,5,string2);
        strcat(string,string2);
        strcat(string, "*");
        sprintf(string2,"%d", anio->totalGamesYear);
        strcat(string, string2);
    }else
        strcat(string,"ND");
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