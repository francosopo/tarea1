#include <stdio.h>
#include <stdlib.h>

#define M 25 //El tamaño de la ram

// en el nombre del archivo va a decir si corresponde a una fila o a una columna
// tamanho es el tamaño de una fila de la matriz
int **matrizPequena(int tamanho, char *nombreArchivoFila, char *nombreArchivoColumna){
    int **matriz = calloc(tamanho,sizeof(int*));
    int *fila = calloc(tamanho, sizeof(int));
    int *columna =
    return matriz;
}

/**
 * Funcion guardarDatos
 * 
 * Guarda los datos de @param fila en un archivo de nombre @param nombreArchivo
 * 
 * @param fila es el arreglo que se quiere guardar en  memoria externa
 * @param tamanhoDatos es el tamaño de una fila de la matriz
 * @param i es en donde inician los datos de esta matriz
 * @param j es en donde inician los datos de esta matriz
 * @param nombreArchivo es el nombre del archivo que tiene la fila o la columna
 * de la matriz
*/
void guardarDatos(int *fila, int tamanhoDatos,int i, int j, char *nombreArchivo){
    FILE *in = fopen(nombreArchivo, "w");
    for(int i =0; i < tamanhoDatos; i++){
        fwrite(&fila[i], sizeof(int), 1, in);
    }
    fclose(in);
}

/**
 * Funcion obtenerDatos
 * 
 * Funcion que lee los datos del archivo @param nombreArchivo
 * 
 * @param fila donde guardar los datos
 * @param tamanhoDatos el tamaño de @param fila
 * @param nombreArchivo el nombre del archivo
*/
void obtenerDatos(int *fila, int tamanhoDatos, char *nombreArchivo){
    FILE *out = fopen(nombreArchivo, "r");
    for(int i = 0; i < tamanhoDatos; i++){
        fread(&fila[i], sizeof(int), 1, out);
    }
    fclose(out);
}


/**
 * Test guardar
 * 
 * Prueba que se guarde la informacion correctamente
*/
void testguardar(){
    char *nombreArchivo= "miColumna.bin";
    int misDatos[9] = {1,2,3,4,5,6,7,8,9};
    int tamanho = 9;
    guardarDatos(misDatos,tamanho,nombreArchivo);
    int deVuelta[9];
    obtenerDatos(deVuelta, tamanho, nombreArchivo);
    for (int i = 0; i < tamanho; i++){
        if( misDatos[i] != deVuelta[i]){
            printf("Error: expected %i, got %i", misDatos[i], deVuelta[i]);
        }
    }
    printf("Todo bien");
}


/**
 * Funcion destruirMatriz
 * 
 * Libera la memoria alocada para @param matriz
 * 
 * @param matriz la matriz
*/
void destruirMatriz(int **matriz){
    free(matriz);
}

int main(int argc, char *argv[]){
    testguardar();
}