#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 2048000 //El tamaño de la memoria principal sacado en google.

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
 * Funcion min
 * 
 * Entrega el minimo de dos valores
 * 
 * @param val1 el primer valor
 * @param val2 el segundo valor
*/
int min(int val1, int val2){
    if (val1 < val2){ 
        return val1;
    }
    else {
        return val2;
    }
}

/**
 * Función modificada del algoritmo 1, la cual rellena una matriz en base a los string 1 y 2, util para rellenar la submatríz
 * @param matrix matriz a modificar
 * @param string1 sección de string que será analizado y comparado
 * @param string2 sección de string que será analizado y comparado
 
 *void completeMatrix(int **matrix, char *string1, char *string2){
 *    //Asumimos que, para este punto, ya se hizo la comprobación del tamaño de ambos strings.
 *   int str_len1 = strlen(string1);
 *   int str_len2 = strlen(string2);
 *   for(int i=1 ;i < str_len1 ;i++){
 *       for(int j=1 ; j < str_len2 ;j++){
 *           int m = min(matrix[i-1][j], matrix[i][j-1]);
 *           if (m < matrix[i-1][j-1]){
 *               matrix[i][j] =  m +1;
 *           }
 *           else{
 *               if(string1[i-1] == string2[j-1]){
 *                   matrix[i][j]= matrix[i-1][j-1];
 *               }
 *               else{
 *                   matrix[i][j] = matrix[i-1][j-1]+1;
 *               }
 *           }
 *           //printf("|%i|" ,matrix[i][j]);
 *           //printf("|%i|" ,matrix[i][j]);
 *       } 
 *   }
 *}
 */

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
    int tamano_del_arreglo = strlen(str1);
    //genero los arreglos originales, que serían dos lineas de tamaño, son +1 por que la casilla 0 para ellos, aun que es compartida originalmente
    //es necesaria para el subsiguiente calculo
    int *horizontales = malloc(sizeof(int)*(tamano_del_arreglo+1));
    int *verticales = malloc(sizeof(int)*(tamano_del_arreglo+1));

    //genero el caso base
    for(int i = 0; i<tamano_del_arreglo+1;i++){
        horizontales[i]= i;
        verticales[i] = i;
    }
    //indicadores de como voy;
    int i = 1;
    int j = 1;
    //tengo que, dado que los ints son de 32 bits, entonces puedo guardar en memoria cache 64000 ints
    //esto implica que maximo puedo utilizar x=252.222..., o aproximando x=250.
    int x=250;
    //la iteración termina al colocar j e i en el tamaño del arreglo,
    while(i!=tamano_del_arreglo && j!=tamano_del_arreglo){
        int mi, mj;
        if (i+x > tamano_del_arreglo){
            mi= tamano_del_arreglo;
        }
        else{
            mi= i+x;
        }
        if(j+x  > tamano_del_arreglo){
            mj=tamano_del_arreglo;
        }
        else{
            mj=x+j;
        }
        int myMatriz[mi-i+1][mj-j+1];
        //relleno el substring1 y la fila 0 del la matriz en cache
        for(int k=i; k<=mi; k++){
            myMatriz[k-i][0] = verticales[k];
        }
        //relleno la columna 0 y el substring 2
        for(int k =j; k<= mj; k++){
            myMatriz[0][k-j] = horizontales[k];
        }
        //hago el algoritmo en la submatriz:
        for(int pi = i+1; pi<=mi;pi++){
            for(int pj=j+1; pj<=mj; pj++){
                int m= min(myMatriz[pi-1][pj], myMatriz[pi][pj-1]);
                if (myMatriz[pi-1][pj-1] > m){
                    myMatriz[pi-i][pj-i]=m+1;
                }
                else{
                    if(str1[pi-1]==str2[pj-1]){
                        myMatriz[pi][pj]=myMatriz[pi-1][pj-1];
                    }
                    else{
                        myMatriz[pi][pj]=myMatriz[pi-1][pj-1]+1;
                    }
                }
            }
        }
        //reemplazo el valor de los tramos que borde horizontal y vertical obtenidos
        for(int k=i; k<= mi; k++){
            verticales[k] = myMatriz[k-i][mj-j];
        }
        for(int k=j; k<= mj; k++){
            horizontales[k]= myMatriz[mi-i][k-j];
        }
        //luego me muevo a la derecha
        i=mi;
        //si ya estoy pegado a la derecha, pero aun no alcanzo la esquina, voy para abajo;
        if(i==tamano_del_arreglo && j !=tamano_del_arreglo){
            j=mj;
            i=0;
        }
    }
    int result= horizontales[tamano_del_arreglo];
    free(horizontales);
    free(verticales);
    return result;
}

int main(int argc, char *argv[]){
    printf("algoritmo3: %i\n", algoritmo3("ananas","banana"));
    return 0;
}