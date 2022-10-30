#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "hash.h"
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


//Entradas Char* del nombre del archivo, int del year minimo, int precio minimo, pipes, int de cant de workers
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
// Entradas: char* (que es la salida de un worker) x int
// Salidas: char*
// Descripción: realiza strtok una cantida N de veces para obtener un dato de la salida
char * getGenerico(char * string, int posicion){
    //year nombrecaro preciocaro nombrebarato preciobarato gratis1,gratis2....,gratisN windows mac linux gamesYear
    // 0      1           2          3              4              5                    6      7   8    9
    char string2[150];
    strcpy(string2,string);
    char separacion[2] = "*";
    char * pedacito;
    pedacito = strtok(string2,separacion);
    for (int i = 0; i<posicion;i++){
        pedacito = strtok(NULL,separacion);
    }
    return pedacito;
}
//Entradas hash, pipes, int cantidad de workers, int min year
//Salida void
//Descripcion lee los N pipes, almacenando los resultados en la hash entregada.
void recolectarDatos(year ** tabla, int fd[][2],int workers, int min_year){
    //year nombrecaro preciocaro nombrebarato preciobarato gratis1,gratis2....,gratisN windows mac linux gamesYear
    // 0      1           2          3              4              5                    6      7   8    9
    int cantFin2=0;
    int i;
    char string[1000];
    int yearActual;
    int posicion;
    float priceEX;//precio caro
    float priceCH;//precio barato
    float w,m,l,gy;
    int lectura;
    printf("\nbroker entro en recolectar datos\n");
    while(cantFin2!=workers){
        for(i=0;i<workers;i++){
            lectura = read(fd[i][0],string, sizeof(string));
            //printf("%s\n",string);
            if( (strcmp(string,"FIN2") !=0) && (lectura != 0 ) && (strcmp(string,"ND") !=0)){
                //obtengo el year y la posicion correspondiente
                yearActual=atoi(getGenerico(string,0));
                posicion= hashFunction(yearActual,min_year);

                //obtengo los precios del mas barato y mas caro
                priceEX= atof(getGenerico(string,2));
                priceCH= atof(getGenerico(string,4));

                if(tabla[posicion]->access==0){//si no habia entrado en esta posicion relleno con estos datos
                    tabla[posicion]->year= yearActual;
                    tabla[posicion]->priceEx=0;
                    tabla[posicion]->priceCh=priceEX+1;
                }

                //obtengo la cantidad de juegos por cada SO y la cantidad de juegos procesador en el year
                w= atof(getGenerico(string,6));
                m= atof(getGenerico(string,7));
                l= atof(getGenerico(string,8));
                gy= atoi(getGenerico(string,9));
                //ahora modificamos los datos almacenados en la tabla para este year
                //si tengo un juego mas caro que el anterior
                if(tabla[posicion]->priceEx<priceEX){
                    //reemplazo el nombre
                    strcpy(tabla[posicion]->moreExpensive,getGenerico(string,2));
                    //reemplazo el precio
                    tabla[posicion]->priceEx=priceEX;
                }
                //si tengo un juego mas barato que el anterior
                if(tabla[posicion]->priceCh>priceCH){
                    //reemplazo el nombre
                    strcpy(tabla[posicion]->cheaper,getGenerico(string,4));
                    //reemplazo el precio
                    tabla[posicion]->priceCh=priceCH;
                }
                //agrego la nueva lista de gratis
                if(strcmp(getGenerico(string,5),"@")!=0){//hay juegos que agregar
                    if(strcmp(tabla[posicion]->free,"")!=0){//si ya hay juegos entonces agrego una ,
                        strcat(tabla[posicion]->free,",");
                    }//agrego los juegos nuevos luego de la ,
                    strcat(tabla[posicion]->free, getGenerico(string,5));
                }
                //aumento la cantidad de juegos por cada SO y por el year
                tabla[posicion]->lix = tabla[posicion]->lix + l;
                tabla[posicion]->win = tabla[posicion]->win + w;
                tabla[posicion]->mac = tabla[posicion]->mac + m;
                tabla[posicion]->totalGamesYear = tabla[posicion]->totalGamesYear +gy;
            }
            else{
                if(strcmp(string,"FIN2")==0){
                    printf("Termine el pipe\n");
                    cantFin2++;
                }
            }
        }
    }
    printf("\nbroker salio de recolectar datos\n");
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

