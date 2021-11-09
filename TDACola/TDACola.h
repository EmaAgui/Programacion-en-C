#ifndef TDACOLA_H
#define TDACOLA_H

#ifdef TDA_COLA_IMPL_ESTATICA
    #include "../TDAColaImpEstatica/TDAColaImpEstatica.h"
#else
    #include "../TDAColaImplDinamica/TDAColaImplDinamica.h"
#endif

#include "../Comun/Defs.h"


void crearCola(Cola* pc);
booleano encolar(Cola* pc, const void* elem, size_t tamElem);
booleano desencolar(Cola* pc, void* elem, size_t tamElem);
booleano verFrenteDeCola(const Cola* pc, void* elem, size_t tamElem);
booleano colaVacia(const Cola* pc);
booleano colaLlena(const Cola* pc, size_t tamElem);
void vaciarCola(Cola* pc);


#endif // TDACOLA_H
