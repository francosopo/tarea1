#include <stdio.h>
#include <stdlib.h>

int min(int val1, int val2){
    if (val1 < val2){ 
        return val1;
    }
    else {
        return val2;
    }
}

int compararTamano( char * str1, char * str2){
    int len_str1 = strlen(str1);
    int len_str2 = strlen(str2);
    if(len_str1 != len_str2){
        printf("tamanho str1: %i, str2: %i", len_str1, len_str2);
        return 0; // los string no tienen el mismo tamaño FALSE
    }
    return 1; // los string tienen el mismo tamaño TRUE
}

int minDiagonal(int tentativo, int diagonal, char c1, char c2){
    if(tentativo >= diagonal){
        if(c1 == c2){
            return diagonal;
        }else{
            return diagonal + 1;
        }
    }else{
        return tentativo + 1;
    }
}

int comparador(int z, int y, int w){
    if(w==z && z==y){
        return 3; //me voy en diagonal
    }
    else if (z>y){
        if(y>w){
            return 3; //me voy por la diagonal
        }
        else{
            return 1; // me voy para el lado
        }
    }else{
        if(z>w){
            return 3; //me voy por la diagonal
        }
        else{
            return 2; //me voy para abajo
        }
    }
}

int minimo2()

int algoritmo2(char *str1, char *str2){
    // diagonal, arriba, izq, valor
    if(compararTamano() == 0){
        fprintf(stderr, "Los tamaños no coinciden");
        exit(1);
    }
    int len_str = strlen(str1);

    int buff[4] = {0,0,0,0};
    int posiciones[2] = {0,0}; //para saber si llego al borde
    int cuanto_falta_para_el_borde = len_str;
    int i = 0;
    int j = 0;
    while(i < len_str && j < len_str){
        int camino_a_seguir = comparador(buf[2], buf[1], buf[3]);
        if(camino_a_seguir == 3) {
            i++;j++;
            buff[1] = buf[3];
            
        }

        int min_tentativo = min(buff[1], buff[2]);
        int minimo = minDiagonal(min_tentativo, buff[0]);
        buff[3] = minimo;
    }

}

int obtenerValor(char *str1, char *str2){
    if(compararTamano(str1, str2) == 0){
        perror("Los strings no coinciden");
        return 0;
    }
}