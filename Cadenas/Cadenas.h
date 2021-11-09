#ifndef CADENAS_H
#define CADENAS_H

#include <stdio.h>
#include "../Comun/Defs.h"

typedef struct
{
    char* cursor;
    boolean finSec;
}
SecuenciaPalabras;


typedef struct
{
    char* ini;
    char* fin;
}
Palabra;


char* miStrStr(const char* cad, const char* subCad);
void normalizarCadena(const char* origen, char* destino);
void crearSecuenciaPalabras(SecuenciaPalabras* sec, char* cad);
boolean leerPalabra(SecuenciaPalabras* sec, Palabra* pal);
boolean finSecuenciaPalabras(SecuenciaPalabras* sec);
void formatearPalabra(Palabra* pal);
void escribirPalabra(SecuenciaPalabras* sec, Palabra* pal, Palabra* palDest);
void reposicionarSecuenciaPalabras(SecuenciaPalabras* sec, int desp);
void escribirCaracter(SecuenciaPalabras* sec, char c);
void cerrarSecuencia(SecuenciaPalabras* sec);


#endif // CADENAS_H
