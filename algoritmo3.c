#include <stdio.h>
#include <stdlib.h>

#define M 25 //El tamaño de la ram

// en el nombre del archivo va a decir si corresponde a una fila o a una columna
// tamanho es el tamaño de una fila de la matriz

/**
 * 
 * Crea una submatriz desde el archivo @param archivoFila y @param archivoColumna
 * 
 * @param tamanho es el tamaño de una fila de la matriz
 * @param k es el indice desde donde se lee la fila o la columna solapada
 * @param nombreArchivoFila es el nombre del archivo que contiene la fila indicada
 * @param nombreArchivoColumna es el nombre del archivo que contiene la columna indicada
*/
int **matrizPequena(int tamanho,int k,int j, char *nombreArchivoFila, char *nombreArchivoColumna){
    int **matriz = calloc(tamanho,sizeof(int*));
    for(int i = 0; i < tamanho; i++){
        int *fila = calloc(tamanho, sizeof(int));
        matriz[i] = fila;
    }
    obtenerDatos(matriz[0], tamanho,k,nombreArchivoFila);

    int *columna = calloc(tamanho, sizeof(int));
    obtenerDatos(columna, tamanho, j, nombreArchivoColumna);
    
    for(int i = 0; i < tamanho; i++){
        matriz[0][i] = columna[i];
    }

    free(columna);

    return matriz;
}

/**
 * Funcion guardarDatos
 * 
 * Guarda los datos de @param fila en un archivo de nombre @param nombreArchivo
 * 
 * @param fila es el arreglo que se quiere guardar en  memoria externa
 * @param tamanhoDatos es el tamaño de una fila de la submatriz
 * @param k donde inician los datos de la fila o de la columna de la submatriz 
 * @param nombreArchivo es el nombre del archivo que tiene la fila o la columna
 * solapada de la matriz
*/
void guardarDatos(int *fila, int tamanhoDatos,int k, char *nombreArchivo){
    FILE *in = fopen(nombreArchivo, "w");
    fseek(in, sizeof(int) * tamanhoDatos * (k), SEEK_SET);
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
 * @param tamanhoDatos el tamaño de una fila de la submatriz
 * @param k donde inicia la fila o la columna solapada de la submatriz 
 * @param nombreArchivo el nombre del archivo
*/
void obtenerDatos(int *fila, int tamanhoDatos, int k, char *nombreArchivo){
    FILE *out = fopen(nombreArchivo, "r");
    fseek(out, sizeof(int) * tamanhoDatos * k, SEEK_SET);
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
void testguardarDelPrincipio(){
    char *nombreArchivo= "miColumna.bin";
    int misDatos[9] = {1,2,3,4,5,6,7,8,9};
    int tamanho = 9;
    guardarDatos(misDatos,tamanho,0,nombreArchivo);
    int deVuelta[9];
    obtenerDatos(deVuelta, tamanho,0,nombreArchivo);
    for (int i = 0; i < tamanho; i++){
        if( misDatos[i] != deVuelta[i]){
            fprintf(stderr,"Error: expected %i, got %i", misDatos[i], deVuelta[i]);
        }
    }
    fprintf(stdout,"Todo bien\n");
}

void testGuardarEnMedio(){
    char *nombreArchivo = "miColumna.bin";
    int misDatos[9] = {1,2,3,4,5,6,7,8,9};
    int tamanho = 9;
    guardarDatos(misDatos, tamanho, 3, nombreArchivo);
    int deVuelta[9];
    obtenerDatos(deVuelta, tamanho, 3, nombreArchivo);
    for(int i = 0; i < tamanho; i++){
        if (misDatos[i] != deVuelta[i]){
            fprintf(stderr,"Error, expected %i, got %i", misDatos[i], deVuelta[i]);
        }
    }
    fprintf(stdout, "Todo bien\n");

}


/**
 * Funcion destruirMatriz
 * 
 * Libera la memoria alocada para @param matriz
 * 
 * @param matriz la matriz
*/
void destruirMatriz(int **matriz, int tamanho){
    for (int i = 0; i < tamanho; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int main(int argc, char *argv[]){
    testguardarDelPrincipio();
    testGuardarEnMedio();
}