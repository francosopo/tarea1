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
    /*if(m < arr[0]){
        return m + 1;
    }else{
        if(a == b) return arr[0];
        else return arr[0] + 1;
    }*/
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

int llenarArreglos(int *arr1, int *arr2, int arr_len, char *str1, char *str2){
    char *str1_copy = calloc(arr_len, sizeof(char));
    char *str2_copy = calloc(arr_len, sizeof(char));

    strcpy(str1_copy, str1);
    strcpy(str2_copy, str2);

    for (int i = 0; i < arr_len; i++){
        //caso base
        if(i == 0){
            int buf[3] = {arr1[0], arr1[1], arr2[1]};
            arr1[i] = calcular_w(buf, 3, *str1_copy, *str2_copy);
            str1_copy++;
            //str2_copy++;
        }else if(*str1 == '\0'){
            return arr1[0];
        }
        else{//caso iterativo
            //printf("%s, %s\n", str1_copy, str2_copy);
            int buf[3] = {arr1[i - 1], arr1[i], arr1[i + 1]};
        
            arr1[i] = calcular_w(buf, 3, *str1_copy, *str2_copy);
            str1_copy++;
            //str2_copy++;
        }
        //printf("|%i|", arr1[i]);
    }
    //printf("\n---------------------------------------------------\n");
    free(str1_copy);
    free(str2_copy);
    return arr1[0];
}

int obtenerValorv2(char *str1, char *str2, int *valoresX, int *valoresY){
    int str_len = strlen(str1);
    
    //inicializando los arreglos
    for (int i = 0; i < str_len + 1; i++){
        valoresX[i] = valoresY[i] = i;
    }

    for(int i = 0; i < str_len; i++){
        llenarArreglos(valoresX, valoresY, str_len - i + 1, str1 + i, str2 + i);
        valoresY[0] = valoresX[0];
        //printf("Columna %i completa\n", i);
        llenarArreglos(valoresY, valoresX, str_len - i + 1, str2 + i, str1 + i);
        //printf("Fila %i completa\n", i);
        //printf("Aquii %i", i);
    }
    int res = valoresX[0];
    //printf("res: %i\n", res);
    return res;
}


int obtenerValorAlg2(char *str1, char *str2){
	int str_len = strlen(str1) + 1;
    //int buf[3];
    int *valoresX = calloc(str_len, sizeof(int));
    int *valoresY = calloc(str_len, sizeof(int));
    int res = obtenerValorv2(str1, str2, valoresX, valoresY);
    free(valoresX); free(valoresY);
    return res;
}

void TestComprobar(int expected, int got, int nTest){
       if (got != expected){
        fprintf(stderr, "Expected %i, got %i\n", expected, got);
    }
    else fprintf(stdout,"Test %i pasado\n", nTest);
}

/*int main(int argc, char *argv[]){
    printf("Holi\n");
    int valor1 = obtenerValorAlg2("xxabcdefghijk", "abcdefghijkyy"); // deberia ser 4
    int valor2 = obtenerValorAlg2("banana", "ananas"); //deberia ser 2
    int valor3 = obtenerValorAlg2("francoso", "francoso"); // deberia ser 0
    int valor4 = obtenerValorAlg2("abcfdef","abcgdef"); // deberia ser 1
    int valor5 = obtenerValorAlg2("111222333", "111444333"); // deberia ser 3
    int valor6 = obtenerValorAlg2("abcfdefghijk","abcdefghijkl"); // deberia ser 2

    TestComprobar(4, valor1, 1);
    TestComprobar(2, valor2, 2);
    TestComprobar(0, valor3, 3);
    TestComprobar(1, valor4, 4);
    TestComprobar(3, valor5, 5);
    TestComprobar(2, valor6, 6);
}
*/