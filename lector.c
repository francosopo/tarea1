#include <stdio.h>
#include "utils.h"
#define tamanho 30
#define cantidad 100

int llenar_buff(char* buf,FILE*in){
    for(int i =0 ;i<30;i++){
        if(fread(buf,tamanho,1,in)!=tamanho){ //no ha leído o se ya se acabó
           fprintf(stderr,"error aquí");
           fclose(in);
           exit(1);
        }
        buf[tamanho]="\0";
    }
    return 1;
}


int main(){
    
    FILE*in = fopen("palabrasAleatorias_{colocar_cantidad}.txt","w");
    //char destino[40];
    //snprintf(destino, 40, "%s_%i.txt", "palabras_aleatorias", 3000);
    for (int i=0;i<cantidad;i++){
       char 
    }
    char buf[tamanho+1]; //para almacenar una palabra
    char buf2[tamanho+1]; // || 
    char comp[cantidad][tamanho+1];
    llenar_buff(buf,in);
    llenar_buff(buf2,in);
    


    return 0;    
}