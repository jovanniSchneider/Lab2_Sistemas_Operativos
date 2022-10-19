//
// Created by jovanni on 02-10-22.
//

#ifndef LAB_1_GAMELIST_H
#define LAB_1_GAMELIST_H

#endif //LAB_1_GAMELIST_H

#include "game.h"
#include "functions.h"

typedef struct nodojueg
{
    game dato;
    struct nodojueg* siguiente;
}nodogame;

typedef struct listajueg
{
    nodogame* inicio;
}gamelist;

// Entradas: void
// Salidas: una struct del tipo lista
// Descripción: retorna una lista vacia
gamelist * crearListaVaciaGame()
{
    gamelist * lista=(gamelist *)malloc(sizeof(gamelist));
    lista->inicio=NULL;
    return lista;
}


void insertarIniciogame(gamelist* lista, game dato)
{
    nodogame* nuevo=(nodogame*)malloc(sizeof(nodogame));
    nuevo->dato=dato;
    nuevo->siguiente = lista->inicio;
    lista->inicio=nuevo;
}
int esListaVaciaGame(gamelist * lista)
{
    if (lista->inicio == NULL)
        return 1;
    else
        return 0;
}

void recorrerListaGame(gamelist * lista)
{
    int cont = 0;
    if (!esListaVaciaGame(lista))
    {
        nodogame * auxiliar=lista->inicio;
        while (auxiliar!=NULL)
        {
            printf("%d,%s,%d,%f,%d,%d,%d,%d,%d,%d\n",auxiliar->dato.ID,auxiliar->dato.name,auxiliar->dato.ageRest,auxiliar->dato.price,auxiliar->dato.comSoon,auxiliar->dato.year,auxiliar->dato.free,auxiliar->dato.win,auxiliar->dato.mac,auxiliar->dato.lix);
            cont++;
            auxiliar=auxiliar->siguiente;
        }
        printf("\n\n");
    }
}
