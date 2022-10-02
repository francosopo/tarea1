import random
import sys
#genera un archivo con caracteres de tamaño (size)*numPalabras
def generarPalabra(size):
    l = []
    abc = "abcdefghijklmnopqrstuvwxyz"

    for i in range(size):
        l.append(abc[random.randint(0,len(abc) - 1 )])
    l="".join(l)
    return l

def testPalabra():
    largoPalabra = 30
    palabraGenerada = generarPalabra(largoPalabra)
    assert len(palabraGenerada) == largoPalabra
    
def testLength():
    size= 30
    numPalabras = 100
    generarPalabrass(size,numPalabras)
    nombreArchivo = f"palabrasAleatorias_{numPalabras}.txt"
    contenido=[]
    with open(nombreArchivo,"r") as f:
        contenido = f.readlines()
    print(len(contenido))
    print(numPalabras)
    assert len(contenido) == numPalabras    

    
def generarPalabrass(size, numPalabras):
    f= open(f"palabrasAleatorias_tam_{size}_cant_{numPalabras}.txt", 'w')
    palabras = []
    for _ in range(numPalabras):
        palabra = generarPalabra(size)
        palabras.append(palabra)
    palabras = "\n".join(palabras)
    f.write(palabras)
    f.close()

if(__name__=="__main__"):
    #testLength()
    #testPalabra()
    generarPalabrass(int(sys.argv[1]), int(sys.argv[2]))