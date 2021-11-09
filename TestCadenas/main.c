#include <stdio.h>
#include <stdlib.h>

#include "../Cadenas/Cadenas.h"

int main()
{
    char cadena[] = "Hola sxflalalo!";
    char subCad[] = "lalo";

    char* encontrada = miStrStr(cadena, subCad);

    if(encontrada) ///si no es fin de cadena
        printf("\nLa subcadena es: %s", encontrada);
    else
        printf("\nLa subcadena %s no fue encontrada", subCad);

    char cadANorm[] = ".-´esTO$%\e(&%&$%uN#tiTULOS#$$";
    char cadNorm[17];

    normalizarCadena(cadANorm, cadNorm);
    printf("\nCadena a normalizar : %s\n",cadANorm);
    printf("\nCadena normalizada : %s\n",cadANorm);
    return 0;
}
