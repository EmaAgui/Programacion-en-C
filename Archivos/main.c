#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Comun/defs.h"
#include "../Fechas/fecha.h"

#define ERR_ARCHIVO     1
#define ERR_ARG         2
#define ERR_LINEA_LARGA 3
#define ERR_CANT_CAMPOS 4

#define CANT_PROD_INI   9
#define CANT_MOV_INI   12

#define ARG_PROD     1
#define ARG_MOV      2
#define ARG_TXT      3
#define ARG_TIPO_TXT 4
#define ARG_PROD_TXT_A_BIN 5

#define TAM_LINEA   500
typedef struct
{
    char codigo[31];
    char descripcion[101];
    Fecha ultPrecio;
    float precioUnitario;
    int cantidad;
}Producto;



typedef int (*TxtABin) (char* linea, Producto* prod); ///Puntero a Funcion


int generarArchivoProd(const char* nombreProd);
int generarArchivoMov(const char* nombreArchivo);
int mostrarArchivo();
void mostrarProd(const Producto* prod);
int actualizarArchivo();
int merge(const char* nombreProductos, const char* nombreMovimientos);
int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, char tipoTxt);
int archivoTxtABin(const char* nomArchTxt, char tipoTxt, const char* nomArchBin);
int archivoTxtABinCValidacion(const char* nomArchTxt, char tipoTxt, const char* nomArchBin);
int txtVarABin(char* linea, Producto* prod);
int txtFijoABin(char* linea, Producto* prod);



///  argv[0]    argv[1]       argv[2]
/// Archivos Productos.dat Movimientos.dat

int main(int argc, char* argv[])
{
    if(argc != 6)
    {
        printf("Cantidad incorrecta de argumentos: %d. Debio pasar cinco argumentos.", argc);
        return ERR_ARG;
    }

    int ret;
     ret = generarArchivoProd(argv[ARG_PROD]);

    if(ret != TODO_OK)
        return ret;

     ret = generarArchivoMov(argv[ARG_MOV]);

    if(ret != TODO_OK)
        return ret;

    puts("\n Movimientos\n");

    ret = mostrarArchivo(argv[ARG_MOV]);
    if(ret != TODO_OK)
        return ret;

    puts("\nAntes del Merge\n");
    puts("\n Productos\n");

    ret = mostrarArchivo(argv[ARG_PROD]);
    if(ret != TODO_OK)
        return ret;

    ret = merge(argv[ARG_PROD], argv[ARG_MOV]);

    if(ret != TODO_OK)
        return ret;

    puts("\nDespues del Merge\n");
    puts("\n Productos\n");

    ret = mostrarArchivo(argv[ARG_PROD]);
    if(ret != TODO_OK)
        return ret;

    ret = archivoBinATxt(argv[ARG_PROD], argv[ARG_TXT], argv[ARG_TIPO_TXT][0]);
    if(ret != TODO_OK)
        return ret;

    ///ret = archivoTxtABin(argv[ARG_TXT],argv[ARG_TIPO_TXT][0], argv[ARG_PROD_TXT_A_BIN]);

    ret = archivoTxtABinCValidacion(argv[ARG_TXT],argv[ARG_TIPO_TXT][0], argv[ARG_PROD_TXT_A_BIN]);

    puts("\nArchivo Productos convertidos de Txt a Bin: \n");

    ret = mostrarArchivo(argv[ARG_PROD_TXT_A_BIN]);

    return ret;
}


int generarArchivoProd(const char* nombreProd)
{   ///Archivos se usa como Base de datos

    FILE* arch =fopen(nombreProd, "wb"); ///

    if(!arch) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nombreProd);
        return ERR_ARCHIVO;
    }

    Producto producto[CANT_PROD_INI] =
    {
        {"arandano", "Arandano",{12, 4, 2021}, 70, 60},
        {"pera", "Pera", {1, 9, 2021}, 60, 100 },
        {"manz", "Manzana", {2, 2, 2021}, 80, 150 },
        {"naran", "Naranja", {3, 5, 2021}, 50, 90 },
        {"sandia", "Sandia", {4, 3, 2021}, 100, 40 },
        {"uva", "Uva", {5, 1, 2021}, 130, 89 },
        {"banana", "Banana", {6, 8, 2021}, 160, 150 },
        {"kiwi", "Kiwi", {7, 7, 2021}, 200, 30 },
        {"pome", "Pomelo", {8, 9, 2021}, 140, 20 },
    };

    fwrite(producto, sizeof(Producto), CANT_PROD_INI, arch);

    fclose(arch); ///Libera la memoria del buffer

    return TODO_OK;
}


int generarArchivoMov(const char* nombreArchivo)
{
    FILE* arch =fopen(nombreArchivo, "wb");

    if(!arch) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nombreArchivo);
        return ERR_ARCHIVO;
    }
    Producto productos[CANT_MOV_INI] =
    {
        {"banana", "Banana", {2, 9, 2021}, 160, 150},
        {"kiwi", "Kiwi", {8, 2, 2021}, 200, 30},
        {"mango", "Mango",{5, 7, 2021}, 100, 30},
        {"mango", "Mango",{7, 7, 2021}, 105, 50},
        {"manz", "Manzana",{5, 5, 2021}, 80, 150},
        {"naran", "Naranja", {5, 3, 2021},50, 90},
        {"naran", "Naranja",{7, 3, 2021}, 55, 30},
        {"pera", "Pera", {6, 1, 2021}, 60, 100},
        {"pome", "Pomelo", {7, 8, 2021},140, 20},
        {"sandia", "Sandia", {8, 7, 2021},100, 40},
        {"zana", "Zanahoria",{7, 9, 2021}, 80, 30},
        {"zana", "Zanahoria", {8, 9, 2021},85, 20},


    };
    fwrite(productos, sizeof(Producto), CANT_MOV_INI, arch);

    fclose(arch);

    return TODO_OK;
}

int mostrarArchivo(const char* nombreArchivo)
{
    FILE* arch =fopen(nombreArchivo, "rb");

    if(!arch) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nombreArchivo);
        return ERR_ARCHIVO;
    }

    Producto prod;

    fread(&prod, sizeof(Producto), 1, arch);
    while (!feof(arch))
    {
        mostrarProd(&prod);
        fread(&prod, sizeof(Producto), 1, arch);
    }

    fclose(arch);

    return TODO_OK;
}


void mostrarProd(const Producto* prod)
{
    printf("[Codigo: %s, Descr: %s,Ult. Pre: %d/%d/%d PreUni: %.2f, Cant: %d]\n",
     prod->codigo, prod->descripcion, prod->ultPrecio.dia, prod->ultPrecio.mes, prod->ultPrecio.anio,
     prod->precioUnitario, prod->cantidad);
}


/**int actualizarArchivo()
{
    FILE* arch =fopen(NOM_ARCH_PROD, "r+b");

    if(!arch) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", NOM_ARCH_PROD);
        return ERR_ARCHIVO;
    }

    Producto prod;
    fread(&prod, sizeof(Producto), 1, arch);
    while (!feof(arch))
    {
        prod.precioUnitario *= 1.10f;///Tengo que retroceder el cursor si no me pisa el siguiente producto
        fseek(arch, -(long)sizeof(Producto), SEEK_CUR);/// - porque retrocede, seek_cur desde donde retrocede
        fwrite(&prod, sizeof(Producto), 1, arch);
        fseek(arch, 0, SEEK_CUR);///sin esto rompo el archivo
        fread(&prod, sizeof(Producto), 1, arch);
    }

    fclose(arch);

    return TODO_OK;
}
**/

int merge(const char* nombreProductos, const char* nombreMovimientos)
{
    FILE* archProd = fopen(nombreProductos, "rb");
    FILE* archMov = fopen(nombreMovimientos, "rb");
    FILE* archTmp = fopen("prod.tmp", "wb");

    if(!archProd || !archMov || !archTmp)
    {
        fclose(archMov);
        fclose(archProd);
        fclose(archTmp);
        return ERR_ARCHIVO;
    }

    Producto prod, mov, prodNue;
    int comp;

    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&mov, sizeof(Producto), 1, archMov);

    while(!feof(archProd) && !feof(archMov))
    {
        comp = strcmp(prod.codigo, mov.codigo); /// devuelve positivo si prod es mayor a mov

        if(comp == 0)
        {
            prod.cantidad += mov.cantidad;
            prod.precioUnitario = mov.precioUnitario;
            fread(&mov, sizeof(Producto), 1, archMov);
        }

        if(comp < 0)
        {
            fwrite(&prod, sizeof(Producto), 1, archTmp);
            fread(&prod, sizeof(Producto), 1, archProd);
        }

        if (comp > 0)
        {
            prodNue = mov;

            fread(&mov, sizeof(Producto), 1, archMov);
            while (!feof(archMov) && strcmp(mov.codigo, prodNue.codigo) == 0)
            {
                prodNue.cantidad += mov.cantidad;
                prodNue.precioUnitario = mov.precioUnitario;

                fread(&mov, sizeof(Producto), 1, archMov);
            }

            fwrite(&prodNue, sizeof(Producto), 1, archTmp);
        }
    }
    while (!feof(archProd))
    {
         fwrite(&prod, sizeof(Producto), 1, archTmp);
         fread(&prod, sizeof(Producto), 1, archProd);
    }

    while (!feof(archMov))
    {
            prodNue = mov;

            fread(&mov, sizeof(Producto), 1, archMov);
            while (!feof(archMov) && strcmp(mov.codigo, prodNue.codigo) == 0)
            {
                prodNue.cantidad += mov.cantidad;
                prodNue.precioUnitario = mov.precioUnitario;
                fread(&mov, sizeof(Producto), 1, archMov);
            }

            fwrite(&prodNue, sizeof(Producto), 1, archTmp);

    }

    fclose(archMov);
    fclose(archProd);
    fclose(archTmp);

    remove(nombreProductos);
    rename("prod.tmp", nombreProductos); /// borro el primero y luego el nombre que le quiero poner

    return TODO_OK;
}


int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nomArchBin, "rb"); ///

    if(!archBin) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nomArchBin);
        return ERR_ARCHIVO;
    }
    FILE* archTxt = fopen(nomArchTxt, "wt"); ///

    if(!archTxt) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nomArchTxt);
        return ERR_ARCHIVO;
    }
    Producto prod;

    const char* formato =  toupper(tipoTxt) == 'V'? "%s|%s|%d/%d/%d|%.2f|%d\n" : "%-30s%-100s%02d%02d%04d%07.2f%04d\n";

    fread(&prod, sizeof(Producto), 1, archBin);
    while (!feof(archBin))
    {///Parte fija cantidad total de campo con decimales y punto 7
        fprintf(archTxt, formato,
            prod.codigo, prod.descripcion, prod.ultPrecio.dia, prod.ultPrecio.mes, prod.ultPrecio.anio,
            prod.precioUnitario, prod.cantidad);

        fread(&prod, sizeof(Producto), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}


int archivoTxtABin(const char* nomArchTxt, char tipoTxt, const char* nomArchBin) /// Solo lo uso cuando el txt esta perfecto y no hay error en ningun campo
{
    FILE* archBin = fopen(nomArchBin, "wb"); ///

    if(!archBin) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nomArchBin);
        return ERR_ARCHIVO;
    }
    FILE* archTxt = fopen(nomArchTxt, "rt"); ///

    if(!archTxt) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nomArchTxt);
        return ERR_ARCHIVO;
    }
    Producto prod;

    const char* formato =  toupper(tipoTxt) == 'V'? "%[^|]|%[^|]|%d/%d/%d|%f|%d\n" : "%30s%100s%2d%2d%4d%7f%4d\n";

    int cantCampos;

    while ((cantCampos = fscanf(archTxt, formato, prod.codigo, prod.descripcion,
            &prod.ultPrecio.dia, &prod.ultPrecio.mes, &prod.ultPrecio.anio,
            &prod.precioUnitario, &prod.cantidad)) != EOF)
    {
        if(cantCampos == 7)
            fwrite(&prod, sizeof(Producto), 1, archBin);
       /// else
            ///Todo: escribir error en log.
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}


int archivoTxtABinCValidacion(const char* nomArchTxt, char tipoTxt, const char* nomArchBin)
{
    FILE* archBin = fopen(nomArchBin, "wb");

    if(!archBin) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nomArchBin);
        return ERR_ARCHIVO;
    }
    FILE* archTxt = fopen(nomArchTxt, "rt"); ///

    if(!archTxt) ///arch == NULL
    {
        printf("El Archivo %s no se pudo abrir.\n", nomArchTxt);
        return ERR_ARCHIVO;
    }
    Producto prod;
    char linea[TAM_LINEA];
    booleano errorCatastrofico = FALSO;
    int codError = TODO_OK;

    TxtABin txtABin = tipoTxt == 'V'? txtVarABin : txtFijoABin;

    while (!errorCatastrofico && fgets(linea, TAM_LINEA, archTxt)) /// fgets lee hasta que encuentra un enter. Paso el vector, el tamaño del vector y el puntero que leo.
    {
        int codError = txtABin(linea, &prod);

     ///errorCatastrofico = esErrorCatastrofico(codError);

        if(codError == TODO_OK)
            fwrite(&prod, sizeof(Producto), 1, archBin);
    /// else
            ///TODO: Informar el error en un archivo log.
    }

    fclose(archBin);
    fclose(archTxt);

    return codError;
}


int txtVarABin(char* linea, Producto* prod)
{
    int codError = TODO_OK;

    char* act = strchr(linea, '\n');

    if(!act) /// act == NULL
        codError = ERR_LINEA_LARGA;

    /*cantCampos = contarCampos(linea);

    if(cantCampos != 5)
        codError = ERR_CANT_CAMPOS;
    */
    ///Cantidad
    *act = '\0';
    act = strrchr(linea, '|');

    ///codError = verificarEntero(act + 1);

    if(codError == TODO_OK)
        sscanf(act + 1, "%d", &prod->cantidad);

    ///Precio Unitario
    *act = '\0';
    act = strrchr(linea, '|');

    ///codError = verificarDecimal(act + 1);

    if(codError == TODO_OK)
        sscanf(act + 1, "%f", &prod->precioUnitario);

    ///Fecha Ult precio
    *act = '\0';
    act = strrchr(linea, '|');

    ///codError = verificarFecha(act + 1);

    if(codError == TODO_OK)
        sscanf(act + 1, "%d/%d/%d", &prod->ultPrecio.dia, &prod->ultPrecio.mes, &prod->ultPrecio.anio);

    ///Descripcion
    *act = '\0';
    act = strrchr(linea, '|');

    ///codError = verificarDescripcion(act + 1);

    if(codError == TODO_OK)
        strcpy(prod->descripcion, act + 1);

    ///Código
    *act = '\0';

    ///codError = verificarCodigo(linea);

    if(codError == TODO_OK)
        strcpy(prod->codigo, linea);

    return codError;
}


int txtFijoABin(char* linea, Producto* prod)
{
    int codError = TODO_OK;

    char* act = strchr(linea, '\n');

    if(!act) /// act == NULL
        codError = ERR_LINEA_LARGA;

    /**
    if(codError == TODO_OK)
   /// cantCampos = contarCampos(linea);

    if(cantCampos != 5)
        codError = ERR_CANT_CAMPOS;
    */

    ///Cantidad
    *act = '\0';
    act -= 4;

    //if(codError == TODO_OK)
    ///codError = verificarEntero(act);

    if(codError == TODO_OK)
        sscanf(act, "%d", &prod->cantidad);

    ///Precio Unitario
    *act = '\0';
    act -= 7;

    //if(codError == TODO_OK)
    ///codError = verificarDecimal(act);

    if(codError == TODO_OK)
        sscanf(act, "%f", &prod->precioUnitario);

    ///Fecha Ult precio
    *act = '\0';
    act -= 8;

    ///codError = verificarFecha(act);

    if(codError == TODO_OK)
        sscanf(act, "%2d%2d%4d", &prod->ultPrecio.dia, &prod->ultPrecio.mes, &prod->ultPrecio.anio);

    ///Descripcion
    *act = '\0';
    act -= 100;

    ///codError = verificarDescripcion(act + 1);

    if(codError == TODO_OK)
    {
        /// rtrim(act); remueve los espacios del final a la derecha
        strcpy(prod->descripcion, act);
    }
    ///Código
    *act = '\0';

    ///codError = verificarCodigo(linea);

    if(codError == TODO_OK)
    {
       /// rtrim(act); remueve los espacios del final a la derecha
        strcpy(prod->codigo, linea);
    }

    return codError;
}
