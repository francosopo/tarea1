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

int calcular_W(int x, int y, int z, char c1, char c2){
    int min_tentativo = min(y, z);
    int minimo = minDiagonal(min_tentativo, x, c1, c2);
    return minimo;
}

int algoritmo2(char *str1, char *str2){
    // diagonal, arriba, izq, valor
    if(compararTamano() == 0){
        fprintf(stderr, "Los tamaños no coinciden");
        exit(1);
    }
    int len_str = strlen(str1);
    int buff[4] = {0,1,1,0};
    int posiciones[2] = {0,0}; //para saber si llego al borde
    int cuanto_falta_para_el_borde = len_str;
    int i = 0;
    int j = 0;
    //Relleno la casilla faltante;
    int minimo = calcular_W(buff[0],buff[1],buff[2],str1[i],str2[j])
    buff[3] = minimo;
    i++;
    j++;
    while(true){
        if (i == len_str || j == len_str){
            return buff[3]+ (len_str-i) + (len_str-j);
        }
        int camino_a_seguir = comparador(buf[2], buf[1], buf[3]);
        else if(camino_a_seguir == 3) {
            //calculo nuevo y
            int new_y= calcular_W(buff[1],buff[1]+1,buff[3],str1[i],str2[j-1]);
            buff[1]= new_y;
            int new_z= calcular_W(buff[2], buff[3], buff[2]+1, str1[i-1], str2[j]);
            buff[2]= new_z;
            buff[1]=buff[3];
            buff[3]= calcular_W(buff[0],buff[1],buff[2],str1[i],str2[j]);
            i++;j++;
        }
        else if (camino_a_seguir==2){
            int z=buff[2];
            int w= buff[3];
            buff[0]=z;
            buff[1]=w;
            buff[2]=z+1;
            buff[3]=calcular_W(buff[0],buff[1], buff[2], str1[i],str2[j+1]);
            j++;
        }
        else if(camino_a_seguir==1){
            int y=buff[1];
            int w=buff[3];
            buff[0]=y;
            buff[1]=y+1;
            buff[2]=w;
            buff[3]=calcular_W(buff[0],buff[1],buff[2],str1[i+1],str2[j]);
            i++;
        }
    }
    return 0;
}

int obtenerValor(char *str1, char *str2){
    if(compararTamano(str1, str2) == 0){
        perror("Los strings no coinciden");
        return 0;
    }
}