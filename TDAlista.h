#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

/*------------- estructura de datos -------------*/
//documentada con formato input,output,desc
typedef struct nodoGenerico
{
  char * dato;
  struct nodoGenerico* siguiente;
}nodo;

typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;


/*------------- operaciones -------------*/

// Entradas: void
// Salidas: una struct del tipo lista
// Descripción: retorna una lista vacia
TDAlista* crearListaVacia()
{
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->inicio=NULL;
  return lista;
}

// Entradas: una struct del tipo lista
// Salidas: int
// Descripción: retorna segun si la lista esta vacia o no
int esListaVacia(TDAlista* lista)
{
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

//Entrada: Una lista de horarios y una funcion que debe recibir un nodo y un string
//Salida: No entrega
//Funcion: Recorre la lista enlazada y aplica la funcion pasada por parametro a cada nodo
void recorrerLista(TDAlista* lista, FILE * fp, int flag)
{
    int cont = 0;
    if (!esListaVacia(lista))
    {
        nodo* auxiliar=lista->inicio;
        if (flag){
            printf("Juegos encontrados el año %d: ", getYear(auxiliar->dato));
        }
        while (auxiliar!=NULL)
        {
            fprintf(fp,"%s",auxiliar->dato);
            cont++;
            auxiliar=auxiliar->siguiente;
        }
        if(flag){
            printf("%d\n",cont);
        }
    }
}

//Entrada: tda lista, un dato
//Salida: No entrega
//Funcion: modifica la lista entregada, agregando en un inicio el dato
void insertarInicio(TDAlista* lista, char * dato)
{
    nodo* nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=(char *)malloc(sizeof(char)*150);
    strcpy(nuevo->dato,dato);
    nuevo->siguiente = lista->inicio;
    lista->inicio=nuevo;
}

//Entrada: tda lista
//Salida: No entrega
//Funcion: elimina el primer nodo de la lista
void eliminarInicio(TDAlista* lista)
{
  nodo* auxiliar;
  if(!esListaVacia(lista))
  {
    auxiliar=lista->inicio;
    lista->inicio=lista->inicio->siguiente;
    free(auxiliar->dato);
    free(auxiliar);
  }
}

//Entrada: tda lista
//Salida: No entrega
//Funcion: elimina los nodos de las listas utilizando funciones anteriores
void liberarLista(TDAlista * lista){
	while (!esListaVacia(lista))
	{
		eliminarInicio(lista);
	}
}