#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Funcion min
 * 
 * Entrega el minimo de dos valores
 * 
 * @param val1 el valor 1
 * @param val2 el valor 2
*/
int min(int val1, int val2){
    if (val1 < val2){ 
        return val1;
    }
    else {
        return val2;
    }
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
 * Funcion minDiagonal
 * 
 * Entrega el minimo entre @param tentativo y @param diagonal
 * dependiendo de los caracteres @param c1 y @param c2
 * 
 * @param tentativo el minimo tentativo
 * @param diagonal el valor de arriba a la izquierda
 * @param c1 el caracter de la primera palabra
 * @param c2 el caracter de la segunda palabra
 * 
*/
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

/**
 * Funcion comparador
 * 
 * Entrega el camino por el cual irse, si hacia abajo, diagonal o derecha
 * 
 * @param z el valor de la izquierda
 * @param y el valor de arriba
 * @param w el valor de la diagonal derecha abajo
 * @param i el indice del caracter de la primera palabra
 * @param j el indice del caracter de la segunda palabra
 * @param str1 el string 1 
 * @param str2 el string 2
*/
int comparador(int z, int y, int w, int i, int j, char *str1, char *str2){
    if(w==z && z==y){
        if (str1[i+1] == str2[j+1]){
            return 3; //me voy por la diagonal
        }
        else if (str1[i]== str2[j+1]){
            return 2; //me voy para abajo
        }
        else if(str1[i+1]== str2[j+1]){
            return 1;//me voy para abajo
        }
        else{
            return 1;
        }
    }
    else if(z == y){
        if(w < y) return 3; //me voy en la diagonal
        else if(str1[i]==str2[j+1]) return 2; //me voy hacia abajo
        else{ 
            return 1; // me voy hacia el lado (o cualquiera)
        }
    }
    else if (z>y){
        if(y>=w){
            return 3; //me voy por la diagonal
        }
        else{
            return 1; // me voy para el lado
        }
    }else{
        if(z>=w){
            return 3; //me voy por la diagonal
        }
        else{
            return 2; //me voy para abajo
        }
    }
}

/**
 * Funcion calcular_W
 * 
 * Funcion que calcula el valor asociado a la derecha y 
 * abajo de una cuadricula de 2x2
 * 
 * @param x el valor de arriba a la izquierda
 * @param y el valor de arriba
 * @param z el valor de la izquierda
*/
int calcular_W(int x, int y, int z, char c1, char c2){
    int min_tentativo = min(y, z);
    int minimo = minDiagonal(min_tentativo, x, c1, c2);
    return minimo;
}

/**
 * Funcion algoritmo2
 * 
 * Ejecuta el algoritmo en cache
 * 
 * @param str1 el string 1
 * @param str2 el string 2
*/
int algoritmo2(char *str1, char *str2){
    // diagonal, arriba, izq, valor
    if(compararTamano(str1, str2) == 0){
        fprintf(stderr, "Los tamaños no coinciden");
        exit(1);
    }
    int len_str = strlen(str1);
    int buff[4] = {0,1,1,0};
    //int posiciones[2] = {0,0}; //para saber si llego al borde
    //int cuanto_falta_para_el_borde = len_str;
    int i = 0;
    int j = 0;
    //Relleno la casilla faltante;
    int minimo = calcular_W(buff[0],buff[1],buff[2],str1[i],str2[j]);
    buff[3] = minimo;
    while(1){
        if (i == len_str || j == len_str){
            printf("buf[3] = %i, i= %i, j=%i\n",buff[3], i, j);
            return buff[3];
        }
        int camino_a_seguir = comparador(buff[2], buff[1], buff[3],i,j, str1, str2);
        if(camino_a_seguir == 3) {
            printf("str1: %s, str1[%i]: %c, str2: %s str2[%i]: %c\n", str1,i, str1[i], str2,j,str2[j]);
            //calculo nuevo y
            int new_y= calcular_W(buff[1],buff[1]+1,buff[3],str1[i],str2[j+1]);
            buff[1]= new_y;
            int new_z= calcular_W(buff[2], buff[3], buff[2]+1, str1[i+1], str2[j]);
            buff[2]= new_z;
            buff[0]=buff[3];
            buff[3]= calcular_W(buff[0],buff[1],buff[2],str1[i+1],str2[j+1]);
            i++;j++;
        }
        else if (camino_a_seguir==2){
            printf("str1: %s, str1[%i]: %c, str2: %s str2[%i]: %c\n", str1,i, str1[i], str2,j,str2[j]);
            int z=buff[2];
            int w= buff[3];
            buff[0]=z;
            buff[1]=w;
            buff[2]=z+1;
            buff[3]=calcular_W(buff[0],buff[1], buff[2], str1[i],str2[j+1]);
            j++;
        }
        else if(camino_a_seguir==1){
            printf("str1: %s, str1[%i]: %c, str2: %s str2[%i]: %c\n", str1,i, str1[i], str2,j,str2[j]);
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

/**
 * Funcion obtenerValor
 * 
 * Entrega la solucion del algoritmo 2
 * 
 * @param str1 el string 1
 * @param str2 el string 2
*/
int obtenerValor(char *str1, char *str2){
    if(compararTamano(str1, str2) == 0){
        perror("Los strings no coinciden");
        return 0;
    }
    return algoritmo2(str1, str2);
}

int main(int argc, char *argv[]){
    int res = obtenerValor("banana", "ananas");
    printf("res 2 == %i\n", res);

    int res2 = obtenerValor("francoso", "francoso");
    printf("res2 0 == %i\n", res2);
    

    int res3 = obtenerValor("bbbaaa", "abbaaa");
    printf("res3 expected 1 = got: %i\n", res3);

    int res4 = obtenerValor("xxabcdefghijk","abcdefghijkyy");
    printf("res4 expected 4 = got %i\n", res4);

    return 0;
}