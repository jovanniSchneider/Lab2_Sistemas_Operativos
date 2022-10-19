#ifndef LAB_1_PADRE_H
#define LAB_1_PADRE_H

#endif //LAB_1_PADRE_H

//#include "hash.h"

//Entradas Char* del nombre del archivo
//Salidas TdaLista ** que trabaja como una tabla hash
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este csv se almacena en una tabla hash segun
//            el year del juego en cuestion
TDAlista ** leerCSV(char* nombreArchivo, int min_year,int min_price);

//Entradas TDALista** que simula una tabla hash,char* para el nombre del archivo
//Salidas int que representa la cantidad de years que si tienen juegos
//Descripcion crea un archivo que contiene la info de la tabla hash con el nombre ingresado, ademas de calcular
//             los years con juegos, tambien dejando constancia de donde comienza cada year mediante ftell
int crearArchivo(TDAlista** hash, char * nombreSalida, int fd[0],int flag, int min_year);

