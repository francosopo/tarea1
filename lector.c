#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "algoritmo1.c"
#include "algoritmo2a.c"
#include "algoritmo3.c"


/** 
 * Puntero Algoritmo
 * 
 * Es un puntero a una funcion que resuleve cada algoritmo
 * 
 * @param string1 es un string de input
 * @param string2 es un string de input
*/
typedef long long (*Algoritmo)(char *string1, char *string2);

typedef void (*Experimento)(Algoritmo alg, char *str1, char *str2, double *stats);

/** 
 * Funcion average
 * 
 * Calcula el promedio del arreglo de doubles
 * 
 * @param data es el arreglo,
 * @param lenData es el largo del arreglo
*/
double average(double *data, double lenData){
    double sum = 0;
    for (int i= 0; i< lenData; i++){
        sum = sum + data[i];
    }
    return sum/lenData;
}

/**
 * Funcion llenar_buf
 * 
 * Lee de un archivo @param in una linea de @param tamanho tamaño
 * 
 * @param buf donde guardar la linea
 * @param in de donde leer la linea
*/
int llenar_buff(char* buf,FILE*in, int tamanho){
    if(fgets(buf,tamanho + 2,in) == NULL){ //error
        fclose(in);
        perror("fgets");
        printf("%i", errno);
        exit(-1);
    }
    //printf("buf: %s, size: %i \n ", buf, sizeof(buf));
    return 1;
}

/**
 * Funcion hacerExperimento1
 * 
 * Funcion que ejecuta el algoritmo uno y guarda
 * el tiempo en segundos en el puntero @param time
 * 
 * @param alg puntero funcion que ejecuta el algoritmo
 * @param string1 input
 * @param string2 input
 * @param time tiempo que se demora
 * 
*/
void hacerExperimento(Algoritmo alg, char *string1, char *string2, double *time){
    clock_t start, end;
    double diff;

    start = clock();
    (*alg)(string1, string2);
    end = clock();

    diff = ((double) (end- start)) / CLOCKS_PER_SEC; 
    *time = diff;
}

/**
 * Funcion promedioExpobtenerValorAlg2
 * retiradas veces y calcula el promedio de los tiempos de ejecucion
 * 
 * @param exp el experimento que calcula una iteracion 
 * @param alg el algoritmo
 * 
*/

void promedioExp(Experimento exp, Algoritmo alg, int numeroAlg, int tamanho, int cantidad){
    // nombre del archivo de palabras
    char destino[100];
    snprintf(destino, 100, "%s_%s_%i_%s_%i.txt", "palabrasAleatorias","tam", tamanho,"cant", cantidad);

    // abriendo el archivo de palabras
    FILE*in = fopen(destino,"r");

    //char buf1[cantidad/2][tamanho + 1];
    //char buf2[cantidad/2][tamanho + 1];
    char **buf1 = calloc(cantidad/2, sizeof(char*));
    if (buf1 == NULL){
        perror("buf1");
    }

    for(int i = 0; i < cantidad/2; i++){
        buf1[i] = calloc(tamanho, sizeof(char));
        if(buf1[i] == NULL){
            perror("buf1[i]");
        }
    }

    char **buf2 = calloc(cantidad/2, sizeof(char*));
    if(buf2 == NULL){
        perror("buf2");
    }
    for(int i = 0; i < cantidad/2; i++){
        buf2[i] = calloc(tamanho, sizeof(char));
        if(buf2 == NULL){
            perror("buf2[i]");
        }
    }

    double stats[cantidad/2]; // para guardar los tiempos

    //se llenan los buffers
    for (long i = 0; i < cantidad/2; i++){
        llenar_buff(buf1[i], in, tamanho);
        llenar_buff(buf2[i], in, tamanho);
        if(i == cantidad/2 -1){
          buf1[i][tamanho] = '\0';  
        }
        //printf("%s\n%s\n", buf1[i], buf2[i]);
        (*exp)(*alg, buf1[i], buf2[i], &stats[i]);
    }
    double avg = average(stats, (double) cantidad/2);
    // nalg, cantidad, largo, tiempo promedio
    FILE *statsFile = fopen("stats2.csv", "a+");
    fprintf(statsFile,"%i,%i,%i,%f\n",numeroAlg, cantidad, tamanho, avg);
    fclose(in);
    fclose(statsFile);

    for(int i = 0; i< cantidad/2; i++){
        free(buf1[i]);
        free(buf2[i]);
    }

    free(buf1);
    free(buf2);
}

void TestComprobar(long long expected, long long got, long long nTest){
       if (got != expected){
        fprintf(stderr, "Expected %lli, got %lli\n", expected, got);
    }
    else fprintf(stdout,"Test %lli pasado\n", nTest);
}

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
 * Funcion main
 * 
 * ejecuta el experimento 1
 * 
*/
int main(){
    printf("\nTiempo Total estimado en un AMD A9-9425\n con 2 NUCLEOS en DEBIAN 11 64 BITS\ncon gcc para 64 bits:\n17min\n ");
    // HACIENDO LAS PRUEBAS DE CADA ALGORITMO

    // PRUEBAS ALGORITMO1
    printf("-----PRUEBAS ALGORITMO 1-----\n");
    int valor11 = obtenerValor("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    int valor21 = obtenerValor("banana", "ananas"); //deberia ser 2
    int valor31 = obtenerValor("francoso", "francoso"); // deberia ser 0
    int valor41 = obtenerValor("abcfdef","abcgdef"); // deberia ser 1
    int valor51 = obtenerValor("111222333", "111444333"); // deberia ser 3
    int valor61 = obtenerValor("abcfdefghijk","abcdefghijkl"); // deberia ser 2

    TestComprobar(4, valor11, 1);
    TestComprobar(2, valor21, 2);
    TestComprobar(0, valor31, 3);
    TestComprobar(1, valor41, 4);
    TestComprobar(3, valor51, 5);
    TestComprobar(2, valor61, 6);

    printf("\n-----PRUEBAS ALGORITMO 2-----\n");

    long long valor12 = obtenerValorAlg2("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    long long valor22 = obtenerValorAlg2("banana", "ananas"); //deberia ser 2
    long long valor32 = obtenerValorAlg2("francoso", "francoso"); // deberia ser 0
    long long valor42 = obtenerValorAlg2("abcfdef","abcgdef"); // deberia ser 1
    long long valor52 = obtenerValorAlg2("111222333", "111444333"); // deberia ser 3
    long long valor62 = obtenerValorAlg2("abcfdefghijk","abcdefghijkl"); // deberia ser 2

    TestComprobar(4, valor12, 1);
    TestComprobar(2, valor22, 2);
    TestComprobar(0, valor32, 3);
    TestComprobar(1, valor42, 4);
    TestComprobar(3, valor52, 5);
    TestComprobar(2, valor62, 6);

    printf("\n-----PRUEBAS ALGORITMO 3-----\n");

    int valor13 = algoritmo3("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    int valor23 = algoritmo3("banana", "ananas"); //deberia ser 2
    int valor33 = algoritmo3("francoso", "francoso"); // deberia ser 0
    int valor43 = algoritmo3("abcfdef","abcgdef"); // deberia ser 1
    int valor53 = algoritmo3("111222333", "111444333"); // deberia ser 3
    int valor63 = algoritmo3("abcfdefghijk","abcdefghijkl"); // deberia ser 2

    TestComprobar(4, valor13, 1);
    TestComprobar(2, valor23, 2);
    TestComprobar(0, valor33, 3);
    TestComprobar(1, valor43, 4);
    TestComprobar(3, valor53, 5);
    TestComprobar(2, valor63, 6);

    int tamanho[13] = {8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
    int cantidad = 100;

    // GENERANDO ARCHIVOS
    printf("\n-----GENERANDO INPUTS PARA LOS ALGORITMOS-----\n");
    printf("En este paso se crean los archivos que servirán\nde entrada a los diferentes algoritmos\n");
    for (int i = 0; i < 13; i++){
        char myBuf[30];
        snprintf(myBuf,30,"python utils.py %i %i", tamanho[i], cantidad);
        system(myBuf);
    }
    // GENERANDO ESTADISTICAS
    printf("\n-----GENERANDO ESTADISTICAS-----\n");
    for (int i = 0; i < 13; i++){
        promedioExp(&hacerExperimento,(long long (*)(char*, char*)) &obtenerValor, 1,tamanho[i], cantidad);
        Algoritmo alg = &obtenerValorAlg2;
        promedioExp(&hacerExperimento, alg, 2, tamanho[i], cantidad);/**/
        promedioExp(&hacerExperimento,(long long (*)(char*, char*))&algoritmo3,3, tamanho[i], cantidad);
    }
    printf("\n-----ESTADISTICAS COMPLETAS-----\n");
    printf("\nRevise stats.csv\n");
    return 0;    
}
