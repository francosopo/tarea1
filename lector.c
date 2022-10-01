#include <stdio.h>
#include <stdlib.h>
//#include "sys\timeb.h"
#include <time.h>
#include <errno.h>
#//include "algoritmo1.c"
#include "algoritmo2a.c"
//#include "algoritmo3.c"

#define tamanho 8192
#define cantidad 1000

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
int llenar_buff(char* buf,FILE*in){
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

void promedioExp(Experimento exp, Algoritmo alg, int numeroAlg){
    // nombre del archivo de palabras
    char destino[100];
    snprintf(destino, 100, "%s_%s_%i_%s_%i.txt", "palabrasAleatorias","tam", tamanho,"cant", cantidad);

    // abriendo el archivo de palabras
    FILE*in = fopen(destino,"r");

    char buf1[cantidad/2][tamanho + 1];
    char buf2[cantidad/2][tamanho + 1];

    double stats[cantidad/2]; // para guardar los tiempos

    //se llenan los buffers
    for (long i = 0; i < cantidad/2; i++){
        llenar_buff(buf1[i], in);
        llenar_buff(buf2[i], in);
        if(i == cantidad/2 -1){
          buf1[i][tamanho] = '\0';  
        }
        //printf("%s\n%s\n", buf1[i], buf2[i]);
        (*exp)(*alg, buf1[i], buf2[i], &stats[i]);
    }
    double avg = average(stats, (double) cantidad/2);
    // nalg, cantidad, largo, tiempo promedio
    FILE *statsFile = fopen("stats.csv", "a+");
    fprintf(statsFile,"%i,%i,%i,%f\n",numeroAlg, cantidad, tamanho, avg);
    fclose(in);
    fclose(statsFile);
}

/**
 * Funcion main
 * 
 * ejecuta el experimento 1
 * 
*/
int main(){
    //promedioExp(&hacerExperimento, &obtenerValor, 1);
    promedioExp(&hacerExperimento, &obtenerValorAlg2, 2);/**/
    //promedioExp(&hacerExperimento,&algoritmo3,3);
    return 0;    
}
