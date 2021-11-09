#define TDA_PILA_IMPL_ESTATICA

#include <string.h>

#include "../TDAPila/TDAPila.h"

#define espacioLibre(pp) (TAM_PILA - (pp)->tope)


void crearPila(Pila* pp)
{
    pp->tope = 0; ///tope indica la cantidad de bits que tiene, por eso apunta a 0
}


booleano apilar(Pila* pp, const void* elem, size_t tamElem) ///void* permite enviar un puntero de cualquier tipo
{
    if(tamElem + sizeof(size_t) > espacioLibre(pp))
        return FALSO;        

    memcpy(pp->vPila + pp->tope, elem, tamElem);
    pp->tope += tamElem;

    *(size_t*)(pp->vPila + pp->tope) = tamElem; ///mencpy(pp->vPila + pp->tope, &tamelem, sizeof(size_t))
    pp->tope += sizeof(size_t);

    return VERDADERO;
}


booleano desapilar(Pila* pp, void* elem, size_t tamElem)
{
    if(pp->tope == 0) ///Pregunto si la pila esta vacia
        return FALSO;
    
    pp->tope -= sizeof(size_t);
    size_t tamElemApilado = *(size_t*)(pp->vPila + pp->tope);
    
    pp->tope -= tamElemApilado;
    memcpy(elem, pp->vPila + pp->tope, min(tamElem, tamElemApilado)); 

    return VERDADERO;
}


booleano verTopeDePila(const Pila* pp, void* elem, size_t tamElem)
{
    if(pp->tope == 0) ///Pregunto si la pila esta vacia
        return FALSO;

    unsigned tope = pp->tope;
    
    tope -= sizeof(size_t);
    size_t tamElemApilado = *(size_t*)(pp->vPila + tope);
    
    tope -= tamElemApilado;
    memcpy(elem, pp->vPila + tope, min(tamElem, tamElemApilado)); 

    return VERDADERO;
}


booleano pilaVacia(const Pila* pp)
{
    return pp->tope == 0;
}


booleano pilaLlena(const Pila* pp, size_t tamElem)
{
    return tamElem + sizeof(size_t) > espacioLibre(pp); //retorna verdadero 
      
}


void vaciarPila(Pila* pp)
{
    pp->tope = 0;
}