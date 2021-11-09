#define TDA_PILA_IMPL_DINAMICA

#include <stdlib.h>
#include <string.h>

#include "../TDAPila/TDAPila.h"


void crearPila(Pila* pp)
{
    *pp = NULL;
}


booleano apilar(Pila* pp, const void* elem, size_t tamElem) ///void* permite enviar un puntero de cualquier tipo
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo)); ///malloc reserva un bloque contiguo de memoria del parametro que le pase y devuelve la direccion del primer bit que encuentre. Siempre hay que liberar la memoria de mallloc, con la funcion free, sino se produce un error de fuga de memoria
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return FALSO;
    }

    memcpy(elemNodo, elem, tamElem); ///origen, destino, tamaño

    nue->elem = elemNodo;
    nue->tamElem = tamElem;

    nue->sig = *pp;
    *pp = nue;

    return VERDADERO;    
}


booleano desapilar(Pila* pp, void* elem, size_t tamElem)
{
    if(!*pp) /// pregunto si la pila no esta vacia 
        return FALSO;
    
    Nodo* nae = *pp;
    *pp = nae->sig;

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);

    return VERDADERO;
}


booleano verTopeDePila(const Pila* pp, void* elem, size_t tamElem)
{
    if(!*pp) /// pregunto si la pila no esta vacia 
        return FALSO;
    
    Nodo* tope = *pp;

    memcpy(elem, tope->elem, min(tamElem, tope->tamElem));

    return VERDADERO;   
}


booleano pilaVacia(const Pila* pp)
{
    return !*pp; /// *pp ==  NULL    
}


booleano pilaLlena(const Pila* pp, size_t tamElem)
{
    void* nue = (Nodo*)malloc(sizeof(Nodo)); 
    void* elemNodo = malloc(tamElem);

    free(nue);
    free(elemNodo);

    return !nue || !elemNodo; /// retorna pila llena 
}


void vaciarPila(Pila* pp)
{
    Nodo* nae;

    while(!*pp) /// pregunto si la pila no esta vacia     
    {
        nae = *pp;
        *pp = nae->sig;
        free(nae->elem);
        free(nae);
    }
}


