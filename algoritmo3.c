#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 2048000 //El tamaño de la memoria principal sacado en google.

// en el nombre del archivo va a decir si corresponde a una fila o a una columna
// tamanho es el tamaño de una fila de la matriz






/**
 * Funcion destruirMatriz3
 * 
 * Libera la memoria alocada para @param matriz
 * 
 * @param matriz la matriz
*/
void destruirMatriz3(int **matriz, int tamanho){
    for (int i = 0; i < tamanho; i++){
        free(matriz[i]);
    }
    free(matriz);
}

/**
 * Funcion min3
 * 
 * Entrega el min3imo de dos valores
 * 
 * @param val1 el primer valor
 * @param val2 el segundo valor
*/
int min3(int val1, int val2){
    if (val1 < val2){ 
        return val1;
    }
    else {
        return val2;
    }
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
    int tamano_del_arreglo = strlen(str1);
    //genero los arreglos originales, que serían dos lineas de tamaño, son +1 por que la casilla 0 para ellos, aun que es compartida originalmente
    //es necesaria para el subsiguiente calculo
    int *horizontales = malloc(sizeof(int)*(tamano_del_arreglo+1));
    int *verticales = malloc(sizeof(int)*(tamano_del_arreglo+1));

    if(horizontales==NULL){
        perror("malloc");
    }
    if(verticales==NULL){
        perror("malloc");
    }
    //genero el caso base
    for(int i = 0; i<tamano_del_arreglo+1;i++){
        horizontales[i]= i;
        verticales[i] = i;
    }
    //indicadores de como voy;
    int i = 1;
    int j = 1;
    //tengo que, dado que los ints son de 32 bits, entonces puedo guardar en memoria cache 64000 ints
    //esto implica que maximo puedo utilizar x=252.222..., o hago x=200.
    int x=200;
    //la iteración termin3a al colocar j e i en el tamaño del arreglo,
    while(i!=tamano_del_arreglo && j!=tamano_del_arreglo){
        int mi, mj;
        if (i+x > tamano_del_arreglo){
            mi= tamano_del_arreglo;
        }
        else{
            mi= i+x-1; 
        }
        if(j+x  > tamano_del_arreglo){
            mj=tamano_del_arreglo;
        }
        else{
            mj=x+j-1;
        }
        int myMatriz[mi-i+1][mj-j+1];
        //relleno el substring1 y la fila 0 del la matriz en cache
        for(int k=i; k<=mi; k++){
            myMatriz[k-i][0] = verticales[k-1];
            //printf("myMatriz[%i][%i]=%i\n",k-i,0,myMatriz[k-i][0]);
        }
        //relleno la columna 0 y el substring 2
        for(int k =j; k<= mj; k++){
            myMatriz[0][k-j] = horizontales[k-1];
            //printf("myMatriz[%i][%i]=%i\n",0,k-j,myMatriz[0][k-j]);
        }
        //hago el algoritmo en la submatriz:
        for(int pi = i+1; pi<=mi;pi++){
            for(int pj=j+1; pj<=mj; pj++){
                int m= min3(myMatriz[pi-i-1][pj-j], myMatriz[pi-i][pj-j-1]);
                if (myMatriz[pi-i-1][pj-j-1] > m){
                    myMatriz[pi-i][pj-j]=m+1;
                    //printf("myMatriz[%i][%i]=%i\n",pi-i,pj-j,myMatriz[pi-i][pj-j]);
                }
                else{
                    if(str1[pi-1]==str2[pj-1]){
                        myMatriz[pi-i][pj-j]=myMatriz[pi-i-1][pj-j-1];
                        //printf("myMatriz[%i][%i]=%i\n",pi-i,pj-j,myMatriz[pi-i][pj-j]);
                    }
                    else{
                        myMatriz[pi-i][pj-j]=myMatriz[pi-i-1][pj-j-1]+1;
                        //printf("myMatriz[%i][%i]=%i\n",pi-i,pj-j,myMatriz[pi-i][pj-j]);
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
            i=1;
        }
    }
    int result= horizontales[tamano_del_arreglo];
    free(horizontales);
    free(verticales);
    return result;
}

/*void TestComprobar(int expected, int got, int nTest){
       if (got != expected){
        fprintf(stderr, "Expected %i, got %i\n", expected, got);
    }
    else fprintf(stdout,"Test %i pasado\n", nTest);
}

int main(int argc, char *argv[]){
    printf("algoritmo3: %i\n", algoritmo3("xymog","mogul"));

    int valor1 = algoritmo3("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    int valor2 = algoritmo3("banana", "ananas"); //deberia ser 2
    int valor3 = algoritmo3("francoso", "francoso"); // deberia ser 0
    int valor4 = algoritmo3("abcfdef","abcgdef"); // deberia ser 1
    int valor5 = algoritmo3("111222333", "111444333"); // deberia ser 3
    int valor6 = algoritmo3("abcfdefghijk","abcdefghijkl"); // deberia ser 2

    TestComprobar(4, valor1, 1);
    TestComprobar(2, valor2, 2);
    TestComprobar(0, valor3, 3);
    TestComprobar(1, valor4, 4);
    TestComprobar(3, valor5, 5);
    TestComprobar(2, valor6, 6);
    return 0;
}*/