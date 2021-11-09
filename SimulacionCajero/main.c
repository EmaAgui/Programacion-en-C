#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"


typedef struct
{
    char nombre[31];
    unsigned tiempoEnCajero;
}
Cliente;


unsigned calcularTiempoDeArribo();
void generarCliente(Cliente* cliente);
unsigned calcularTiempoEnCAjero();


int main()
{
    srand(time(NULL));

    unsigned tiempoArribo = calcularTiempoDeArribo();
    Cliente clienteEnCajero, cliente;
    booleano cajeroOcupado = FALSO; /// Cajero no ocupado
    unsigned cantVecesColaVacia = 0;
    unsigned minuto = 0;

    Cola colaCajero;
    crearCola(&colaCajero);

    while (cantVecesColaVacia < 5)
    {
        printf("Minuto %d\n", minuto);

        if(tiempoArribo == 0) /// Llega  una persona
        {
            generarCliente(&cliente);

            if(!cajeroOcupado)
            {
                cajeroOcupado = VERDADERO;
                clienteEnCajero = cliente;
                printf("Llego el cliente %s e ingreso al cajero. Va a usar el cajero %d minutos\n", cliente.nombre, cliente.tiempoEnCajero);
            }
            else
            {
                encolar(&colaCajero, &cliente, sizeof(Cliente));
                printf("Llego el cliente %s e ingreso a la cola. Va a usar el cajero %d minutos", cliente.nombre, cliente.tiempoEnCajero);
            }

            tiempoArribo = calcularTiempoDeArribo();
        }
        if(cajeroOcupado)
        {
            clienteEnCajero.tiempoEnCajero--;

            if(clienteEnCajero.tiempoEnCajero == 0)
            {
                printf("El cliente %s termino de usar el cajero\n", clienteEnCajero.nombre);
                cajeroOcupado = FALSO;

                if(!colaVacia(&colaCajero))
                {
                    desencolar(&colaCajero, &clienteEnCajero, sizeof(Cliente));
                    cajeroOcupado = VERDADERO;
                    printf("El Cliente %s, que estaba en la cola ingreso al cajero\n", clienteEnCajero.nombre);

                    if(colaVacia(&colaCajero))
                        cantVecesColaVacia++;
                }
            }
        }

        minuto++;
        tiempoArribo--;
    }




    return 0;
}


unsigned calcularTiempoDeArribo()
{
    static const unsigned ta[] = {1, 5, 9}; ///vector de tiempo

    return ta[rand() % 3]; ///da uno de los tres valores del vector ta
}


void generarCliente(Cliente* cliente)
{
    static const char nombres[][9] = {"Juan", "Pedro", "Adrian", "Bernardo", "Carlos", "Dario", "Andrea", "Brenda", "Carla", "Daniela", "Esteban", "Fernanda", "Fernando", "Gaston", "Graciela"};
    strcpy(cliente->nombre, nombres[rand() % 15]);

    cliente->tiempoEnCajero = calcularTiempoEnCAjero();
}

unsigned calcularTiempoEnCAjero()
{
    static const unsigned tc[] = {1, 3, 5}; ///vector de tiempo

    return tc[rand() % 3]; ///da uno de los tres valores del vector ta

}
