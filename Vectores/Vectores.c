#include "Vectores.h"

#include <stdio.h>
#include <string.h>


#define espacioLibre(vec) (CAP - (vec)->ce * (vec)->tamElem)

int buscarPosicionInsercionMayorEnVectorOrd(const Vector* vec, int elem);
void* buscarMenor(void* inicio, void* fin, int tamElem, Cmp cmp);

void crearVector(Vector* vec, int tamElem)
{
    vec->ce = 0;
    vec->tamElem = tamElem;
}

int insertarEnVectorOrdAscConDup(Vector* vec, int elem)
{
    if(vec->ce == CAP)
        return VEC_LLENO;

    int posAct;

    for(posAct = vec->ce-1; posAct >= 0 && elem < vec->v[posAct]; posAct--)
        vec->v[posAct + 1] = vec->v[posAct];

    vec->v[posAct+1] = elem;

    vec->ce++;

    return TODO_OK;
}


int insertarEnVectorOrdAscSinDup(Vector* vec, int elem)
{
    if(vec->ce == CAP)
        return VEC_LLENO;

    int posIns = buscarPosicionInsercionMayorEnVectorOrd(vec, elem);

    if(vec->ce > 0 && vec->v[posIns] == elem)
        return DUPLICADO;

    for(int posAct = vec->ce-1; posAct >= posIns && elem < vec->v[posAct]; posAct--)
        vec->v[posAct + 1] = vec->v[posAct];

    vec->v[posIns] = elem;

    vec->ce++;

    return TODO_OK;
}


int insertarEnVectorAlFinal(Vector* vec, const void* elem)
{
    if(espacioLibre(vec) < vec->tamElem)
        return VEC_LLENO;

    memcpy(vec->v + vec->ce * vec->tamElem, elem, vec->tamElem);

    vec->ce++;

    return TODO_OK;
}


int buscarEnVectorOrd(const Vector* vec, int elem)
{
    int posAct=0;

    while(posAct < vec->ce && elem > vec->v[posAct])
        posAct++;

    if( posAct < vec->ce && elem == vec->v[posAct])
        return posAct;

    return -1;
}


boolean eliminarDeVectorOrdAsc(Vector* vec, int elem)
{
    int posElem = buscarEnVectorOrd(vec, elem);

    if (posElem == -1)
        return FALSO;

    for(int posAct = posElem; posAct < vec->ce - 1; posAct++)
        vec->v[posAct] = vec->v[posAct + 1];

    vec->ce --;

    return VERDADERO;
}


void ordenarVectorAscBurbujeo(Vector* vec)
{
    boolean huboIntercambio = VERDADERO;
    int i = 1;

    while(i < vec->ce && huboIntercambio)
    {
        huboIntercambio = FALSO;

        for(int j = 0; j < vec->ce - i; j++)
        {
            if(vec->v[j] > vec->v[j+1])
            {
                intercambiar(&vec->v[j],&vec->v[j+1], vec->tamElem);
                huboIntercambio = VERDADERO;
            }
        }

        i++;
    }

}


void ordenarVectorAscSeleccion(Vector* vec, Cmp cmp)
{
    void* m;
    void* ult = vec->v + (vec->ce - 1) * vec->tamElem;

    for( void* i = vec->v; i <= ult; i += vec->tamElem)
    {
        m = buscarMenor(i, ult, vec->tamElem, cmp);

        if(m != i)
            intercambiar(m, i, vec->tamElem);
    }
}


void* buscarMenor(void* inicio, void* fin, int tamElem, Cmp cmp)
{
    void* m = inicio;
    for(void* j = inicio + tamElem; j <= fin; j += tamElem)
    {
        if( cmp(j, m) < 0)
            m = j;
    }

    return m;
}


void ordenarVectorAscInsercion(Vector* vec)
{
    int elem;

    for(int i = 1; i < vec->ce; i++)
    {
        elem = vec->v[i];

        int j;
        for(j = i; j >= 0 && elem < vec->v[j]; j--)
            vec->v[j+1] = vec->v[j];

        if(i != j+1)
            vec->v[j+1] = elem;
    }
}


void mostrarVector(const Vector* vec, Mostrar mostrar)
{
    if(vec->ce == 0 )
        {
            puts("\nEl Vector esta vacio");
            return;
        }
    putchar('\n');

    const void* ult = vec->v + (vec->ce - 1) * vec->tamElem;
    for(const void* i = vec->v; i <= ult; i += vec->tamElem)
        mostrar(i);

    putchar('\n');
}



int buscarPosicionInsercionMayorEnVectorOrd(const Vector* vec, int elem)
{
    if(vec->ce == 0)
        return -1;

    int posAct=0;

    while(posAct < vec->ce && elem > vec->v[posAct])
        posAct++;

    return posAct;
}


void intercambiar(void* v1, void* v2, int tamElem)
{
    char aux[tamElem];
    memcpy(aux, v1, tamElem);
    memcpy(v1,v2,  tamElem);
    memcpy(v2, aux, tamElem);
}




