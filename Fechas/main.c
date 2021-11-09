#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Fecha.h"

int ingresarEnteroPositivo(const char* mensaje);
boolean continuar(const char* mensaje);

int main()
{
    do
    {
        Fecha fecha = ingresarFecha();

        int cantDias = ingresarEnteroPositivo("\nIngresa dias a Sumar");

        Fecha suma = sumarDiasAFecha(&fecha, cantDias);

        printf("\nLa suma es %d/%d/%d", suma.dia, suma.mes, suma.anio);

        Fecha f2= ingresarFecha();

        int dif = diferenciaDeDiasEntreFechas(&fecha, &f2);
        printf("\nLa diferencia entre fechas es: %d", dif);
    }
    while(continuar("\n queres realizarotrasuma?"));

    return 0;
    /*
    printf("\nIngrese cantidad de dias a sumar: ");
    scanf("%d", &diassum);

    sumarDiasAFecha(fhoy,diassum);

    printf("\nIngrese cantidad de dias a restar: ");
    scanf("%d", &diasres);
    restarDiasAFecha(fhoy, diasres);
    */
}

int ingresarEnteroPositivo(const char* mensaje)
{
    int valor;
    printf("%s: ",mensaje);
    printf(": ");
    scanf("%d", &valor);
    fflush(stdin);

    while(valor < 1)
    {
        printf("\nEl valor ingresado es invalido, ingrese nuevamente: ");
        fflush(stdin);
        scanf("%d", &valor);
    }

    return valor;
}


boolean continuar(const char* mensaje)
{
    char cont;
    printf("%s(s/n)",mensaje);
    scanf("%c",&cont);
    cont = tolower(cont);
    while(cont!='s' && cont != 'n')
    {
        printf("\nOpcion incorrecta, ingresa nuevamente(s/n): ");
        scanf("%c", &cont);
        cont = tolower(cont);
    }
    return cont == 's';
}


