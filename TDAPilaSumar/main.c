#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDA_PILA_IMPL_DINAMICA

#include "../TDAPila/TDAPila.h"

#define aBin(c) ((c) - '0')
#define aChar(d) ((d) + '0')


booleano sumar(const char* num1S, const char* num2S);
booleano cargarPila(const char* vec, Pila* pp, int cantCeros);
void cargarVector(Pila* pp, char* vec);


int main(int argc, char* argv[])
{

    int sumo = sumar(argv[1], argv[2]);/// Le paso los numeros por argumentos

    return sumo? 0 : 1;
}


booleano sumar(const char* num1S, const char* num2S)
{
    Pila pNum1, pNum2, pSuma;

    crearPila(&pNum1);
    crearPila(&pNum2);
    crearPila(&pSuma);

    booleano pudoCargar;

    int cantCeros = strlen(num1S) - strlen(num2S); /// Sirve para saber si tengo que agregar ceros para poder sumar

    pudoCargar = cargarPila(num1S, &pNum1, (cantCeros < 0 )? -cantCeros : 0); ///Cargo las pilas con los numeros

    if(!pudoCargar)
        return FALSO;

    pudoCargar = cargarPila(num2S, &pNum2, (cantCeros > 0 )? cantCeros : 0);

    if (!pudoCargar)
        return FALSO;

    int acarreo = 0, digS, cantDigS = 0;
    char digNum1C, digNum2C, digSC; ///c es de char

    while (!pilaVacia(&pNum1) && pudoCargar)
    {
        desapilar(&pNum1, &digNum1C, sizeof(char));
        desapilar(&pNum2, &digNum2C, sizeof(char));

        digS = aBin(digNum1C) + aBin(digNum2C) + acarreo;

        acarreo = digS / 10;

        digSC = aChar(digS % 10);

        pudoCargar = apilar(&pSuma, &digSC, sizeof(char));
        cantDigS++;
    }

    if (pudoCargar && acarreo == 1)
    {
        char acarreoC = '1';
        pudoCargar = apilar(&pSuma, &acarreoC, sizeof(char));
        cantDigS++;
    }

    if (pudoCargar)
    {
        char* sumaS = (char*)malloc(cantDigS); /// malloc obtengo bloques de memoria dinamica, devuelve void*

        if(!sumaS)
            return FALSO;

        cargarVector(&pSuma, sumaS);

        puts(sumaS);

        free(sumaS); /// free devuelve el puntero de malloc y libera la memoria
    }

    return pudoCargar;
}


booleano cargarPila(const char* vec, Pila* pp, int cantCeros)
{
    char cero = '0';
    booleano pudoApilar = VERDADERO;

    for(int i = 1; i <= cantCeros && pudoApilar; i++ )
        pudoApilar = apilar(pp, &cero, sizeof(char));

    const char * act = vec;

    while(*act && pudoApilar)
    {
        pudoApilar = apilar(pp, act, sizeof(char));
        act++;
    }

    return pudoApilar;
}


void cargarVector(Pila* pp, char* vec)
{
    char* act = vec;

    while(!pilaVacia(pp))
    {
        desapilar(pp, act, sizeof(char));
        act++;
    }

    *act = '\0';
}
