#ifndef TDACOLAIMPESTATICA_H
#define TDACOLAIMPESTATICA_H

#include <stddef.h>

#define TAM_COLA 5000

typedef struct 
{
    char vCola [TAM_COLA];
    void* frente;
    void* fondo;
    size_t tamDisponible;
}
Cola;


#endif // TDACOLAIMPESTATICA_H
