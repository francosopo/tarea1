/**
 * Retorna una palabra de tamaño @param size
*/
char *generarPalabra(int size);

/**
 * Destruye la memoria alocada para @param palabra
*/
void destruirPalabra(char *palabra){
    free(palabra);
}


/**
 * Retorna palabras de tamaño @param size cada una
*/
char  **generarPalabras(int size);

