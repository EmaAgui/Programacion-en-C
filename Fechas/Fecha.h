#ifndef FECHA_H
#define FECHA_H

#include "../Comun/Defs.h"


typedef struct ///Definicion de estructura
{
    int dia;
    int mes;
    int anio;
}
Fecha;


booleano esFechaValida(const Fecha* f);
Fecha ingresarFecha();
Fecha sumarDiasAFecha(const Fecha* f, int dias);
int diferenciaDeDiasEntreFechas(const Fecha* f1, const Fecha* f2);
int diaDelAnio(const Fecha* f);
/*
void sumarDiasAFecha(Fecha f, int dias);
void restarDiasAFecha(Fecha f, int dias);
int diaDeLaSemana(const Fecha* f);
*/



#endif // FECHA_H
