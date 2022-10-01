#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long minimo(long *arr, long len){
    long m = arr[0];
    for(long i = 1; i < len; i++){
        if(arr[i]< m){
            m = arr[i];
        }
    }
    return m;
}

long calcular_w(long *arr,long arr_len, char a, char b){
    long m = minimo(arr, arr_len);
    if( a == b) return m;
    else return m + 1;
    /*if(m < arr[0]){
        return m + 1;
    }else{
        if(a == b) return arr[0];
        else return arr[0] + 1;
    }*/
}

long obtenerValor2(char *str1, char *str2, long i, long j, long *buf){
    if(i == 0) return j;
    else if(j == 0) return i;
    else{
    	long x = obtenerValor2(str1, str2, i-1, j-1, buf);
    	long y = obtenerValor2(str1, str2, i-1, j, buf);
    	long z = obtenerValor2(str1, str2, i, j-1, buf);
    	//long buf[3] = {x,y,z};
        buf[0] = x;
        buf[1] = y;
        buf[2] = z;
    	long w = calcular_w(buf, 3, str1[i], str2[j]);
    	return w;
    } 
}

long llenarArreglos(long *arr1, long *arr2, long arr_len, char *str1, char *str2){
    char *str1_copy = calloc(arr_len, sizeof(char));
    char *str2_copy = calloc(arr_len, sizeof(char));

    if(str1_copy == NULL){
        perror("calloc 3");
    }

    if(str2_copy == NULL){
        perror("calloc 4");
    }

    strcpy(str1_copy, str1);
    strcpy(str2_copy, str2);
    for (long i = 0; i < arr_len; i++){
        //caso base
        if(i == 0){
            long buf[3] = {arr1[0], arr1[1], arr2[1]};
            arr1[i] = calcular_w(buf, 3, *str1_copy, *str2_copy);
            str1_copy++;
            //str2_copy++;
        }else if(*str1 == '\0'){
        	long ret = arr1[0];
        	str1_copy = str1_copy - i;
        	free(str1_copy);
        	free(str2_copy);
        	return ret;
        }
        else{//caso iterativo
            //printf("%s, %s\n", str1_copy, str2_copy);
            long buf[3] = {arr1[i - 1], arr1[i], arr1[i + 1]};
        
            arr1[i] = calcular_w(buf, 3, *str1_copy, *str2_copy);
            str1_copy++;
            //str2_copy++;
        }
        //printf("|%i|", arr1[i]);
    }
    //printf("\n---------------------------------------------------\n");
    free(str1_copy - arr_len);
    //printf("%s\n", *str1_copy);
    free(str2_copy);
    return arr1[0];
}

long obtenerValorv2(char *str1, char *str2, long *valoresX, long *valoresY){
    long str_len = strlen(str1);
    
    //inicializando los arreglos
    for (long i = 0; i < str_len + 1; i++){
        valoresX[i] = valoresY[i] = i;
    }

    for(long i = 0; i < str_len; i++){
        llenarArreglos(valoresX, valoresY, str_len - i + 1, str1 + i, str2 + i);
        valoresY[0] = valoresX[0];
        //printf("Columna %i completa\n", i);
        llenarArreglos(valoresY, valoresX, str_len - i + 1, str2 + i, str1 + i);
        //printf("Fila %i completa\n", i);
        //printf("Aquii %i", i);
    }
    long res = valoresX[0];
    //printf("res: %i\n", res);
    return res;
}


long obtenerValorAlg2(char *str1, char *str2){
	long str_len = strlen(str1) + 1;
    //long buf[3];
    long *valoresX = calloc(str_len, sizeof(long));
    if(valoresX == NULL){
        perror("calloc 1");
    }
    long *valoresY = calloc(str_len, sizeof(long));
    if (valoresY == NULL){
        perror("calloc 2");
    }
    long res = obtenerValorv2(str1, str2, valoresX, valoresY);
    free(valoresX); free(valoresY);
    return res;
}

void TestComprobar(long expected, long got, long nTest){
       if (got != expected){
        fprintf(stderr, "Expected %i, got %i\n", expected, got);
    }
    else fprintf(stdout,"Test %i pasado\n", nTest);
}

int main(int argc, char *argv[]){
    printf("Holi\n");
    long valor1 = obtenerValorAlg2("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    long valor2 = obtenerValorAlg2("banana", "ananas"); //deberia ser 2
    long valor3 = obtenerValorAlg2("francoso", "francoso"); // deberia ser 0
    long valor4 = obtenerValorAlg2("abcfdef","abcgdef"); // deberia ser 1
    long valor5 = obtenerValorAlg2("111222333", "111444333"); // deberia ser 3
    long valor6 = obtenerValorAlg2("abcfdefghijk","abcdefghijkl"); // deberia ser 2

    TestComprobar(4, valor1, 1);
    TestComprobar(2, valor2, 2);
    TestComprobar(0, valor3, 3);
    TestComprobar(1, valor4, 4);
    TestComprobar(3, valor5, 5);
    TestComprobar(2, valor6, 6);
}
