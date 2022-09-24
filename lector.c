#include <stdio.h>
#include <stdlib.h>
#include <sys\timeb.h>
#include <time.h>

#include "tarea1.c"

#define tamanho 100
#define cantidad 100

typedef int (*Algoritmo)(char *string1, char *string2);

double average(double *data, double lenData){
    double sum = 0;
    for (int i= 0; i< lenData; i++){
        sum = sum + data[i];
    }
    return sum/lenData; 
}

int llenar_buff(char* buf,FILE*in){
    if(fgets(buf,tamanho + 1,in) == NULL){ //error
        fclose(in);
        perror("fgets");
        exit(-1);
    }
    return 1;
}

void hacerExperimentoParString(Algoritmo alg, char *string1, char *string2, double *time){
    clock_t start, end;
    double diff;

    start = clock();
    (*alg)(string1, string2);
    end = clock();

    diff = ((double) (end- start)) / CLOCKS_PER_SEC; 
    *time = diff;
}

void experimento1(){
    // nombre del archivo de palabras
    char destino[40];
    snprintf(destino, 40, "%s_%i.txt", "palabrasAleatorias", cantidad);

    // abriendo el archivo de palabras
    FILE*in = fopen(destino,"r");

    char buf1[cantidad/2][tamanho];
    char buf2[cantidad/2][tamanho];

    double stats[cantidad/2]; // para guardar los tiempos

    //se llenan los buffers
    for (int i = 0; i < cantidad/2; i++){
        llenar_buff(buf1[i], in);
        llenar_buff(buf2[i], in);
        printf("%s\n%s\n", buf1[i], buf2[i]);
    }
    
    for (int i = 0; i < cantidad/2; i++){
        printf("buf1, buf2 = %i, %i\n", strlen(buf1[i]), strlen(buf2[i]));
        hacerExperimentoParString(&obtenerValor, buf1[i], buf2[i], &stats[i]);
        printf("Iteracion %i completada en %f seg\n", i, stats[i]);
    }
    double avg = average(stats, (double) cantidad);
    printf("En promedio: %f seg\n", avg);
    fclose(in);
}


int main(){
    experimento1();
    return 0;    
}