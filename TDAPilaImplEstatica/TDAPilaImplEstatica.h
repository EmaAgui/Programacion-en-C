#ifndef TDAPILAIMPLESTATICA_H_INCLUDED
#define TDAPILAIMPLESTATICA_H_INCLUDED

#define TAM_PILA 5000


typedef struct
{
    char vPila[TAM_PILA]; /// Vector de caracteres, porque el char ocupa un bit y es mas facil saber cuanto tamaño ocupa
    unsigned tope;
}
Pila;

#endif // TDAPILAIMPLESTATICA_H_INCLUDED
