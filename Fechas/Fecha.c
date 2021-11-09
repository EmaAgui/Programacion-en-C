#include <stdio.h>
#include <stdlib.h>

#include "../Comun/Defs.h"
#include "Fecha.h"


int cantDiasMes(int mes, int anio);
boolean esBisiesto(int anio);



boolean esFechaValida(const Fecha* f)
{
    return
        f->anio>1600 &&
        f->mes >= 1 && f->mes <= 12 &&
        f->dia >= 1 && f->dia <= cantDiasMes(f->mes, f->anio);

}
Fecha sumarDiasAFecha(const Fecha* f, int dias)
{
    int cdm;
    Fecha fecha = *f;

    fecha.dia += dias;

    while(fecha.dia > (cdm = cantDiasMes(fecha.mes, fecha.anio)))
    {
        fecha.dia -= cdm;

        fecha.mes++;

        if(fecha.mes > 12)
        {
            fecha.mes = 1;
            fecha.anio++;
        }
    }
    return fecha;
}

int cantDiasMes(int mes, int anio)
{
    static const int cdm[] ={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; ///static declaro una sola vez el vector, se inicializa solo una vez el vector,CONST variable constante si selamodifica el compilador tira error

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];
}


boolean esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

Fecha ingresarFecha()
{
    Fecha fecha;
    printf("\nIngrese Fecha(dd/mm/aaaa): ");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    while(!esFechaValida(&fecha))
    {
        printf("\nLa fecha es invalida, ingrese nuevamente(dd/mm/aaaa): ");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }
    return fecha;
}


int diferenciaDeDiasEntreFechas(const Fecha* f1, const Fecha* f2)
{
    int dif = (diaDelAnio(f2) - diaDelAnio(f1));
    int anioAct = f1->anio;

    while(anioAct < f2->anio)
    {
        dif += cantDiasAnio(anioAct);
        anioAct++;
    }

    return dif;
}


int diaDelAnio(const Fecha* f)
{
    int diaA = f->dia;
    int mesAct = 1;

    while(mesAct < f->mes)
    {
        diaA += cantDiasMes(mesAct, f->anio);
        mesAct++;
    }

    return diaA;
}


int cantDiasAnio(int anio)
{
    return esBisiesto(anio)? 366 : 365;
}

/*
void sumarDiasAFecha(Fecha f, int dias)
{
    int sum, res, d, m, a,cdm;

    m = f.mes;
    a = f.anio;

    cdm = cantDiasMes(m, a);

    sum = dias+f.dia;

    while(sum > cdm)
    {
        res = sum-cdm;
        sum = res;

        if(m == 12)
            {
                a++;
                m = 0;
            }
        m++;
        cdm = cantDiasMes (m, a);
    }
    d = sum;

    printf("La fecha es: %d/%d/%d", d, m, a );


}

void restarDiasAFecha(Fecha f, int dias)
{
    int sum, res, d, m, a, cdm;

    m = f.mes;
    a = f.anio;

    cdm = cantDiasMes(m, a);

    sum = f.dia - dias;

    while(sum < cdm)
    {
        res = sum+cdm;
        sum = res;

        if(m == 1)
            {
                a--;
                m = 1;
            }

        cdm = cantDiasMes (m, a);
        m--;
    }
    d = sum-cdm;


    printf("La fecha es: %d/%d/%d", d, m, a );

}
*/
