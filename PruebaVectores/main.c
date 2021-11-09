#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

#include "../Vectores/Vectores.h"


typedef struct
{
    int dni;
    char apellido[51];
    char nombre[51];
    float sueldo;
}
Empleado;


int cmpEmpl(const void* pv1, const void* pv2);
int cmpApeYNom(const void* pv1, const void* pv2);
void mostrarEmpl(const void* pve);


int main()
{
    setlocale(LC_CTYPE, "spanish");

    Vector vec;

    crearVector(&vec, sizeof(Empleado));

    Empleado empleados[6]=
    {
        {
            22333444,
            "Perez",
            "Juan",
            56000
        },
        {
            33344455,
            "Rodriguez",
            "Pedro",
            56000
        },
        {
            44455566,
            "Alvarez",
            "Alberto",
            459000
        },
        {
            55566777,
            "Alvarez",
            "Nicolas",
            455000
        },
        {
            55566777,
            "Benitez",
            "Bernardo",
            459000
        },
        {
            41757402,
            "Aaaa",
            "Fgggg",
            206000
        }
    };



    for(int i = 0; i < 6; i++)
        insertarEnVectorAlFinal(&vec, &empleados[i]);


   /* if(buscarEnVectorOrd(&vec, 5) >= 0)
        printf("\nElemento %d encontrado",5);
    else
        printf("\nElemento %d no encontrado", 5);

    if(buscarEnVectorOrd(&vec, 20) >= 0)
        printf("\nElemento %d encontrado",20);
    else
        printf("\nElemento %d no encontrado", 20);
    */

   /// mostrarVector(&vec);

    time_t tIni = time(NULL);

    ordenarVectorAscSeleccion(&vec, cmpApeYNom);

    time_t  tFin = time(NULL);

    mostrarVector(&vec, mostrarEmpl);

    printf("\nEl ordenamiento demoro %ld segundos. ",(long)(tFin - tIni));

    return 0;
}


int cmpEmpl(const void* pv1, const void* pv2)
{
    Empleado* emp1 = (Empleado*)pv1;
    Empleado* emp2 = (Empleado*)pv2;

    return emp1->dni - emp2->dni;
}


int cmpApeYNom(const void* pv1, const void* pv2)
{
    Empleado* emp1 = (Empleado*)pv1;
    Empleado* emp2 = (Empleado*)pv2;

    int comp = strcmp(emp1->apellido, emp2->nombre);

    if( comp ==0)
        comp = strcmp(emp1->nombre, emp2->nombre);

    return comp;
}


void mostrarEmpl(const void* pve)
{
    Empleado* empl =(Empleado*)pve;

    printf("[DNI: %d, Apellido: %s, Nombre %s, Sueldo: %.2f]\n", empl->dni, empl->apellido, empl->nombre, empl->sueldo);
}
