#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 25 //El tamaño de la memoria principal

// en el nombre del archivo va a decir si corresponde a una fila o a una columna
// tamanho es el tamaño de una fila de la matriz



/**
 * Funcion compararTamano
 * 
 * Compara el tamaño de dos string, retornando 0 si son distintos
 * y 1 si son iguales
 * 
 * @param str1 el string 1
 * @param str2 el string 2
*/
int compararTamano( char * str1, char * str2){
    int len_str1 = strlen(str1);
    int len_str2 = strlen(str2);
    if(len_str1 != len_str2){
        printf("tamanho str1: %i, str2: %i", len_str1, len_str2);
        return 0; // los string no tienen el mismo tamaño FALSE
    }
    return 1; // los string tienen el mismo tamaño TRUE
}

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

/**
 * Función modificada del algoritmo 1, la cual rellena una matriz en base a los string 1 y 2, util para rellenar la submatríz
 * @param matrix matriz a modificar
 * @param string1 sección de string que será analizado y comparado
 * @param string2 sección de string que será analizado y comparado
 */
int **completeMatrix(int **matrix, char *string1, char *string2){
    //Asumimos que, para este punto, ya se hizo la comprobación del tamaño de ambos strings.
    int str_len = strlen(string1);
    for(int i=1 ;i<str_len+1;i++){
        for(int j=1 ; j<str_len+1;j++){
            int m = min(matrix[i-1][j], matrix[i][j-1]);
            if (m < matrix[i-1][j-1]){
                matrix[i][j] =  m +1;
            }
            else{
                if(string1[i-1] == string2[j-1]){
                    matrix[i][j]= matrix[i-1][j-1];
                }
                else{
                    matrix[i][j] = matrix[i-1][j-1]+1;
                }
            }
            //printf("|%i|" ,matrix[i][j]);
            //printf("|%i|" ,matrix[i][j]);
        } 
    }
    return matrix;
}


/**
 * Función que actua tal como el algoritmo 3
 * @param str1 primer string
 * @param str2 segundo string
 */ 
int algoritmo3(char *str1, char *str2){
    //verifico si ambos strings coinciden:
    if (compararTamano(str1,str2) == 0){
        fprintf(stderr, "los tamaños no coinciden");
        exit(1);
    }
    int tamaño_del_arreglo = strlen(str1);
    //genero los arreglos originales, que serían dos lineas de tamaño
    int *horizontales = malloc(sizeof(int)*(tamaño_del_arreglo+1));
    int *verticales = malloc(sizeof(int)*(tamaño_del_arreglo+1));

    //genero el caso base
    for(int i = 0; i<tamaño_del_arreglo+1;i++){
        horizontales[i]= i;
        verticales[i] = i;
    }
    int i = 0;
    int j = 0;

    
    
}

int main(int argc, char *argv[]){
    testguardarDelPrincipio();
    testGuardarEnMedio();
}