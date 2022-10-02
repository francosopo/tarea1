#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long minimo(long long *arr, long long len){
    long long m = arr[0];
    for(long long i = 1; i < len; i++){
        if(arr[i]< m){
            m = arr[i];
        }
    }
    return m;
}

long long calcular_w(long long *arr,long long arr_len, char a, char b){
    long long m = minimo(arr, arr_len);
    if( a == b) return m;
    else return m + 1;
    /*if(m < arr[0]){
        return m + 1;
    }else{
        if(a == b) return arr[0];
        else return arr[0] + 1;
    }*/
}

long long obtenerValor2(char *str1, char *str2, long long i, long long j, long long *buf){
    if(i == 0) return j;
    else if(j == 0) return i;
    else{
    	long long x = obtenerValor2(str1, str2, i-1, j-1, buf);
    	long long y = obtenerValor2(str1, str2, i-1, j, buf);
    	long long z = obtenerValor2(str1, str2, i, j-1, buf);
    	//long long buf[3] = {x,y,z};
        buf[0] = x;
        buf[1] = y;
        buf[2] = z;
    	long long w = calcular_w(buf, 3, str1[i], str2[j]);
    	return w;
    } 
}

long long llenarArreglos(long long *arr1, long long *arr2, long long arr_len, char *str1, char *str2){
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
    for (long long i = 0; i < arr_len; i++){
        //caso base
        if(i == 0){
            long long buf[3] = {arr1[0], arr1[1], arr2[1]};
            arr1[i] = calcular_w(buf, 3, *str1_copy, *str2_copy);
            str1_copy++;
            //str2_copy++;
        }else if(*str1 == '\0'){
        	long long ret = arr1[0];
        	str1_copy = str1_copy - i;
        	free(str1_copy);
        	free(str2_copy);
        	return ret;
        }
        else{//caso iterativo
            //printf("%s, %s\n", str1_copy, str2_copy);
            long long buf[3] = {arr1[i - 1], arr1[i], arr1[i + 1]};
        
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

long long obtenerValorv2(char *str1, char *str2, long long *valoresX, long long *valoresY){
    long long str_len = strlen(str1);
    
    //inicializando los arreglos
    for (long long i = 0; i < str_len + 1; i++){
        valoresX[i] = valoresY[i] = i;
    }

    for(long long i = 0; i < str_len; i++){
        llenarArreglos(valoresX, valoresY, str_len - i + 1, str1 + i, str2 + i);
        valoresY[0] = valoresX[0];
        //printf("Columna %i completa\n", i);
        llenarArreglos(valoresY, valoresX, str_len - i + 1, str2 + i, str1 + i);
        //printf("Fila %i completa\n", i);
        //printf("Aquii %i", i);
    }
    long long res = valoresX[0];
    //printf("res: %i\n", res);
    return res;
}


long long obtenerValorAlg2(char *str1, char *str2){
	long long str_len = strlen(str1) + 1;
    //long long buf[3];
    long long *valoresX = calloc(str_len, sizeof(long long));
    if(valoresX == NULL){
        perror("calloc 1");
    }
    long long *valoresY = calloc(str_len, sizeof(long long));
    if (valoresY == NULL){
        perror("calloc 2");
    }
    long long res = obtenerValorv2(str1, str2, valoresX, valoresY);
    free(valoresX); free(valoresY);
    return res;
}

/*void TestComprobar(long long expected, long long got, long long nTest){
       if (got != expected){
        fprintf(stderr, "Expected %lli, got %lli\n", expected, got);
    }
    else fprintf(stdout,"Test %lli pasado\n", nTest);
}

int main(int argc, char *argv[]){
    printf("Holi\n");
    long long valor1 = obtenerValorAlg2("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    long long valor2 = obtenerValorAlg2("banana", "ananas"); //deberia ser 2
    long long valor3 = obtenerValorAlg2("francoso", "francoso"); // deberia ser 0
    long long valor4 = obtenerValorAlg2("abcfdef","abcgdef"); // deberia ser 1
    long long valor5 = obtenerValorAlg2("111222333", "111444333"); // deberia ser 3
    long long valor6 = obtenerValorAlg2("abcfdefghijk","abcdefghijkl"); // deberia ser 2

    TestComprobar(4, valor1, 1);
    TestComprobar(2, valor2, 2);
    TestComprobar(0, valor3, 3);
    TestComprobar(1, valor4, 4);
    TestComprobar(3, valor5, 5);
    TestComprobar(2, valor6, 6);
}
*/