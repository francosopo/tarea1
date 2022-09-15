#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void destruirMatriz(int **matriz, int n){
    for (int i = 0; i < n + 1; i++){
        free(matriz[i]);
    }
    free(matriz);
}

/*

    Hipotesis 2.1: Omega(n) y 2n, => Theta(n) //tiempo
    hipotesis de espacio = O(n^2)

*/

int compararTamano( char * str1, char * str2){
    int len_str1 = strlen(str1);
    int len_str2 = strlen(str2);
    if(len_str1 != len_str2){
        return 0; // los string no tienen el mismo tamaño FALSE
    }
    return 1; // los string tienen el mismo tamaño TRUE
}

int obtenerValor(char *str1, char *str2){
    if(compararTamano(str1, str2) == 0){
        perror("Los strings no coinciden");
        return 0;
    }else{
        int str_len = strlen(str1);
        // generar la matriz
        int **miMatriz = construirMatriz(str_len);
        for (int i = 1; i < str_len + 1; i++){
            for (int j = 1; j < str_len + 1; j++){
        
                //comparaciones
        
                if(str1[i] == str2[j]){
                    miMatriz[i][j] = miMatriz[i- 1][j -1];
                }else {
                    miMatriz[i][j] = miMatriz[i-1][j-1] + 1;
                }
            }
        }
        printf("%i == 2\n", miMatriz[str_len-1][str_len - 1]);

        for(int i = 1; i < str_len + 1; i++){
            for (int j = 1; j < str_len + 1; j++) {
                printf("i= %i, j=%i, valor = %i\n", i,j,miMatriz[i][j]);
            }
        }

        destruirMatriz(miMatriz, str_len);
        return 1;
    }

}

int main(int argc, char* argv[]){
    
    obtenerValor("banana", "ananas");
    return 0;
}