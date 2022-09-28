#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimo(int *arr, int len){
    int m = arr[0];
    for(int i = 1; i < len; i++){
        if(arr[i]< m){
            m = arr[i];
        }
    }
    return m;
}

int calcular_w(int *arr,int arr_len, char a, char b){
    int m = minimo(arr, arr_len);
    if( a == b) return m;
    else return m + 1;
}

int obtenerValor2(char *str1, char *str2, int i, int j, int *buf){
    if(i == 0) return j;
    else if(j == 0) return i;
    else{
    	int x = obtenerValor2(str1, str2, i-1, j-1, buf);
    	int y = obtenerValor2(str1, str2, i-1, j, buf);
    	int z = obtenerValor2(str1, str2, i, j-1, buf);
    	//int buf[3] = {x,y,z};
        buf[0] = x;
        buf[1] = y;
        buf[2] = z;
    	int w = calcular_w(buf, 3, str1[i], str2[j]);
    	return w;
    } 
}

int obtenerValorv2(char *str1, char *str2){
    int str_len = strlen(str1);
    int *valoresX = calloc(str_len, sizeof(int));
    int *valoresY = calloc(str_len, sizeof(int));
    

    free(valoresX);
    free(valoresY);
}


int obtenerValorAlg2(char *str1, char *str2){
	int str_len = strlen(str1);
    int buf[3];
    int res = obtenerValor2(str1, str2, str_len, str_len, buf);
    return res;
}

void TestComprobar(int expected, int got, int nTest){
       if (got != expected){
        fprintf(stderr, "Expected %i, got %i\n", expected, got);
    }
    else fprintf(stdout,"Test %i pasado\n", nTest);
}

/*int main(int argc, char *argv[]){
    int valor1 = obtenerValorAlg2("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    int valor2 = obtenerValorAlg2("banana", "ananas"); //deberia ser 2
    int valor3 = obtenerValorAlg2("francoso", "francoso"); // deberia ser 0
    int valor4 = obtenerValorAlg2("abcfdef","abcgdef"); // deberia ser 1
    int valor5 = obtenerValorAlg2("111222333", "111444333"); // deberia ser 3

    TestComprobar(4, valor1, 1);
    TestComprobar(2, valor2, 2);
    TestComprobar(0, valor3, 3);
    TestComprobar(1, valor4, 4);
    TestComprobar(3, valor5, 5);
}*/
