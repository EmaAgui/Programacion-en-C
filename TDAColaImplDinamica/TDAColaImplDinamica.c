#include <stdlib.h>
#include <string.h>

#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"


void crearCola(Cola* pc)
{
    pc->frente = pc->fondo = NULL;
}


booleano encolar(Cola* pc, const void* elem, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));    ///tomo memoria para un nodo y un elemento
    void* elemNodo = malloc(tamElem);

    if (!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return FALSO;
    }

    memcpy(elemNodo, elem, tamElem);
    nue->elem = elemNodo;
    nue->tamElem = tamElem;
    nue->sig = NULL;

    if(pc->fondo) ///Si la Cola No esta Vacia
        pc->fondo->sig = nue;
    else
        pc->frente = nue;

    pc->fondo = nue;

    return VERDADERO;
}


booleano desencolar(Cola* pc, void* elem, size_t tamElem)
{
    if(!pc->frente) /// veo que la cola no este vacia
        return FALSO;

    Nodo* nae = pc->frente;
    pc->frente = nae->sig;

    if(!pc->frente)
        pc->fondo = NULL;

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);

    return VERDADERO;
}


booleano verFrenteDeCola(const Cola* pc, void* elem, size_t tamElem)
{
    Nodo* frente = pc->frente;

    if(!pc->frente) /// veo que la cola no este vacia
        return FALSO;

    memcpy(elem, frente->elem, min(tamElem, frente->tamElem));

    return VERDADERO;
}


booleano colaVacia(const Cola* pc)
{
    return !pc->frente;
}


booleano colaLlena(const Cola* pc, size_t tamElem)
{
    void* nue = malloc(sizeof(Nodo));    ///tomo memoria para un nodo y un elemento
    void* elemNodo = malloc(tamElem);

    free(nue);
    free(elemNodo);

    return !nue || !elemNodo;
}


void vaciarCola(Cola* pc)
{
    Nodo* nae;

    while(!pc->frente) /// veo que la cola no este vacia
    {
        nae = pc->frente;
        pc->frente = nae->sig;
        free(nae->elem);
        free(nae);
    }

    pc->fondo = NULL;
}
