#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tarea1.h"

/**
 * Funcion completeMatrix
 * 
 * Completa la matriz asociada al algoritmo uno
 * 
 * @param matrix la matriz
 * @param string1 el input 
 * @param string2 el input
 * 
*/
void completeMatrix(int **matrix, char *string1, char *string2);

/**
 * Funcion construirMatriz
 * 
 * Inicializa la matriz cuadrada de tamaño @param n x @param n
 * 
 * @param n el tamaño de una fila de la matriz
 * 
*/
int **construirMatriz(int n){
    int **miMatriz = malloc(sizeof(int*) * (n + 1));
    for(int i = 0; i < n + 1; i++){
        miMatriz[i] = malloc(sizeof(int) * (n + 1));
    }

    for (int i = 0; i < n + 1; i++){
            miMatriz[0][i] = i;
            miMatriz[i][0] = i;
            //printf("%i, %i, %i\n", i, 0, miMatriz[i][0]);
            //printf("%i, %i, %i\n", 0, i, miMatriz[0][i]);
    }

    return miMatriz;

}

/**
 * Funcion destruirMatriz
 * 
 * Funcion que libera la memoria asociada a la matriz
 * 
 * @param matriz la matriz
 * @param n el tamaño de una fila de la matriz
*/
void destruirMatriz(int **matriz, int n){
    for (int i = 0; i < n + 1; i++){
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

/*
    Algoritmo 1
    Hipotesis 2.1: Omega(n) y 2n, => Theta(n) //tiempo
    hipotesis de espacio = O(n^2)

*/

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
 * Funcion obtenerValor
 * 
 * Obtiene el valor calculado con programacion dinámica,
 * es decir, el valor asociado a la celda (n-1, n-1)
 * 
 * @param str1 el string 1
 * @param str2 el string 2
*/
int obtenerValor(char *str1, char *str2){
    if(compararTamano(str1, str2) == 0){
        perror("Los strings no coinciden");
        return 0;
    }else{
        int str_len = strlen(str1);
        // generar la matriz
        int **miMatriz = construirMatriz(str_len);
        completeMatrix(miMatriz,str1,str2);
        int miValor=miMatriz[str_len][str_len];
        destruirMatriz(miMatriz, str_len);
        return miValor;
    }
}
     // | diagonal \+1o0| Arriba   | +1|
     // ---------------------      v
    //  | Al lado ->+1  |Este          |
void completeMatrix(int **matrix, char *string1, char *string2){
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
            //printf("|%i|" ,matrix[i][j])
        } 
        //printf("\n ---------------------------------------------------------------------------------------------------------------------\n");
    }
}

/*int main(int argc, char* argv[]){
    //algoritmo 1 test   
    printf("%i\n",obtenerValor("fanfarria", "industria"));
    
    return 0;
}*/