#include <stdio.h>
#include <stdlib.h>
#include <sys\timeb.h>
#include <time.h>

#include "tarea1.c"

#define tamanho 5000
#define cantidad 100

typedef int (*Algoritmo)(char *string1, char *string2);

int llenar_buff(char* buf,FILE*in){
    if(fgets(buf,tamanho + 2,in) == NULL){ //error
        fclose(in);
    }
    //buf[tamanho] = '\0';
    return 1;
}

void hacerExperimentoParString(Algoritmo alg, char *string1, char *string2, int *time){
    clock_t start, end;
    double diff;

    //ftime(&start);
    start = clock();
    int val = (*alg)(string1, string2);
    printf("val: %i", val);
    
    //ftime(&end);
    end = clock();

    /*diff = (int) ((end.time - start.time)
        + (end.millitm - start.millitm));*/
    diff = (double) (end- start) / CLOCKS_PER_SEC;
     
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

    int stats[cantidad]; // para guardar los tiempos
    
    for (int i = 0; i < cantidad - 1; i= i + 2){
        llenar_buff(buf1[i],in);
        llenar_buff(buf2[i],in);

        hacerExperimentoParString(&obtenerValor, buf1[i], buf2[i], &stats[i]);
        printf("Iteracion %i completada en %i milliseg\n", i, stats[i]);
    }

    fclose(in);
}

int main(){
    experimento1();
    return 0;    
}