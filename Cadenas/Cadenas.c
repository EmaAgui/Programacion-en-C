#include <stddef.h>
#include <ctype.h>

#include "Cadenas.h"
#define esLetra(c) ((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z')

char* miStrStr(const char* cad, const char* subCad)
{
    char* i = (char*)cad;
    char* j;
    char* encontrada;

    while(*i) ///Mientras *i no sea fin de cadena
    {
        while(*i && *i != *subCad)
        i++;

        if(*i)
        {
            encontrada = i;
            i++;
            j = (char*)subCad + 1;
            while(*i && *j && *i == *j)
            {
                i++;
                j++;
            }

            if(!*j)
                return encontrada;
            else
                i = encontrada + 1;
        }
    }

    return NULL;
}


void normalizarCadena(const char* origen, char* destino)
{
    SecuenciaPalabras secLec;
    crearSecuenciaPalabras(&secLec, (char*)origen);

    SecuenciaPalabras secEscr;
    crearSecuenciaPalabras(&secEscr, destino);

    Palabra pal, palDest;
    leerPalabra(&secLec, &pal);
    while(!finSecuenciaPalabras(&secLec))
    {
        escribirPalabra(&secEscr, &pal, &palDest);
        formatearPalabra(&palDest); ///pasa mayuscula la primer letra y las otras a minuscula
        escribirCaracter(&secEscr, ' ');
        leerPalabra(&secLec, &pal);
    }

    reposicionarSecuenciaPalabras(&secEscr, -1);
    cerrarSecuencia(&secEscr);
}


void crearSecuenciaPalabras(SecuenciaPalabras* sec, char* cad)
{
    sec->cursor = cad;
    sec->finSec = FALSO;
}


boolean leerPalabra(SecuenciaPalabras* sec, Palabra* pal)
{
    char* act = sec->cursor;
    while((*act) && (!esLetra(*act)))
        act++;

    if(!*act) ///*act == '\0'
    {
        sec->finSec = VERDADERO;
        return FALSO;
    }

    pal->ini = act;

    while((*act) && (esLetra(*act)))
        act++;

    pal->fin = act - 1;

    sec->cursor = act;

    return VERDADERO;
}


boolean finSecuenciaPalabras(SecuenciaPalabras* sec)
{
    return sec->finSec;
}


void formatearPalabra(Palabra* pal)
{
    *pal->ini = toupper(*(pal->ini));

    for(char* act= pal->ini + 1; act <= pal->fin; act++)
        *act = tolower(*act);
}


void escribirCaracter(SecuenciaPalabras* sec, char c)
{
    *sec->cursor = c;
    sec->cursor++;
}


void escribirPalabra(SecuenciaPalabras* sec, Palabra* pal, Palabra* palDest)
{
    char* dest = sec->cursor;

    palDest->ini = dest;

    for(char* orig = pal->ini, *dest; orig <= pal->fin; orig++, dest++)
        *dest= *orig;

    palDest->fin = dest - 1;

    sec->cursor = dest;
}


void reposicionarSecuenciaPalabras(SecuenciaPalabras* sec, int desp)
{
    sec->cursor += desp;
}


void cerrarSecuencia(SecuenciaPalabras* sec)
{
    *sec->cursor = '\0';
}
