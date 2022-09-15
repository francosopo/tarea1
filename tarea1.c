#include <stdlib.h>
#include <stdio.h>

int **construirMatriz(int n){
    int **miMatriz = malloc(sizeof(int*) * (n + 1));
    for(int i = 0; i < n + 1; i++){
        miMatriz[i] = malloc(sizeof(int) * (n + 1));
    }

    for (int i = 0; i < n + 1; i++){
            miMatriz[0][i] = i;
            miMatriz[i][0] = i;
            printf("%i, %i, %i\n", i, 0, miMatriz[i][0]);
            printf("%i, %i, %i\n", 0, i, miMatriz[0][i]);
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

    Hipotesis 2.1: Omega(n) y 2n, => Theta(n)

*/
string[1]

void completeMatrix(int **matrix, char *string1, char *string2){
    for(i=0;i<n+1;i++){
        for(j)
    } 

}

int main(int argc, char* argv[]){
    int **miMatriz = construirMatriz(10);
    destruirMatriz(miMatriz, 10);
    return 0;
}