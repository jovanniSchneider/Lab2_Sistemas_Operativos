#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

//LEER CSV LINEA X LINEA
//GENERAR WORKERS

//Entradas: entero que representa el numero maximo a generar
//Salida: Un entero
//Descripcion: Entrega un numero aleatorio entre 0 y el numero ingresado

int myRandom(int n){
    return rand() % n;
}

// Entradas: char*
// Salidas: int
// Descripción: separa un string hasta obtener el dato que representa el year
int getYear(char * string) {
    char string2[150];
    strcpy(string2,string);
    char separacion[2] = ",";
    char * pedacito;
    int year;
    pedacito = strtok(string2,separacion);//980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    for (int i = 0; i<5;i++){
        pedacito = strtok(NULL,separacion);
    }
    year = atoi(pedacito);
    return year;
}

//Entradas: string
//Salidas: float
//Descripcion: separa un string hasta obtener el dato que representa el precio
float getPrice(char * string){
    char string2[150];
    strcpy(string2,string);
    char separacion[2] = ",";
    char * pedacito;
    float price;
    pedacito = strtok(string2,separacion);//980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    for (int i = 0; i<3;i++){
        pedacito = strtok(NULL,separacion);
    }
    price = atof(pedacito);
    return price;
}


//Entradas Char* del nombre del archivo
//Salidas TdaLista ** que trabaja como una tabla hash
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este csv se almacena en una tabla hash segun
//            el year del juego en cuestion
void leerCSV(char nombreArchivo[30],int min_year,int min_price, int fd[][2],int workers){
    FILE* fp;
    fp= fopen(nombreArchivo,"r");
    char string[150];
    int lineas = 0;
    while(fgets(string,150,fp)!=NULL){
        if(getYear(string)>= min_year && getPrice(string) >= min_price){
            lineas++;
            write(fd[myRandom(workers)][1],string,sizeof(string));
        }
    }
    printf("Lineas leidas = %d\n",lineas);
    strcpy(string,"FIN");
    for(int i=0;i<=workers;i++){
        write(fd[i][1],string,sizeof(string));
    }
    fclose(fp);
}


//Entradas TDALista** que simula una tabla hash,char* para el nombre del archivo
//Salidas int que representa la cantidad de years que si tienen juegos
//Descripcion crea un archivo que contiene la info de la tabla hash con el nombre ingresado, ademas de calcular
//             los years con juegos, tambien dejando constancia de donde comienza cada year mediante ftell
//int crearArchivo(TDAlista** hash, char * nombreSalida, int fd[2],int flag,int min_year){
//    int largoHash = getActualYear()-min_year+5;
//    FILE * fp;
//    fp = fopen(nombreSalida, "w");
//    int cont = 0;
//    long puntero;
//    for(int i=0;i<largoHash;i++){
//        if(!esListaVacia(hash[i])) {
//            puntero = ftell(fp);
//            recorrerLista(hash[i],fp,flag);
//            cont++;
//            write(fd[1],&puntero,sizeof(puntero));
//        }
//        liberarLista(hash[i]);
//    }
//    free(hash);
//    fclose(fp);
//    return cont;
//}

