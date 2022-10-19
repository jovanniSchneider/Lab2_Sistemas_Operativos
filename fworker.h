//
// Created by jovan on 9/13/2022.
//

#ifndef LAB_1_HIJO_H
#define LAB_1_HIJO_H

#endif //LAB_1_HIJO_H
//Entradas: puntero del archivo intermedio creado por el padre y el puntero (long) para saber donde comenzar a leer
//Salidas: void
//Descripcion: lee los juegos correspondientes y los almacena
void leerArchivo(FILE * fp,long puntero,gamelist * lista);

void juegosFree(char * string, gamelist * lista);

void calcularPromedios(char * string, gamelist * lista);

char * buscarTopAndBottom(char* string, gamelist * lista);