#ifndef LAB_1_HASH_H
#define LAB_1_HASH_H

#endif //LAB_1_HASH_H
#include "TDAlista.h"
#include <time.h>

//Entradas: Un entero que representa el año del game
//Salidas: Un entero correspondiente a la casilla de la tabla hash
//Descripcion: Calcula la casilla de la tabla
int hashFunction(int number, int min_year){
    return number - min_year;
}
//Entradas: void
//Salidas: Un arreglo de listas enlazadas que corresponde a la tabla hash
//Descripcion: genera una tabla hash
TDAlista ** crearHash(int min_year){
    int year = getActualYear();
    TDAlista** M=(TDAlista**)malloc(sizeof(TDAlista*)*(year-min_year+5));
    for (int i = 0; i < year-min_year+5; ++i) {
        M[i] = crearListaVacia();
    }
    return M;
}

//Entradas: string,tabla hash, int, int
//Salidas: void
//Descripcion: inserta un dato en la tabla hash.
void agregarDatoHash(char * datos, TDAlista ** hash,int min_year,int min_price){
    int year = getYear(datos);
    int price = getPrice(datos);
    if(year>=min_year && price >=min_price) {
        insertarInicio(hash[hashFunction(year, min_year)], datos);
    }
}