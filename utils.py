import random
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
    generarPalabra(size,numPalabras)
    nombreArchivo = f"palabrasAleatorias_{size*numPalabras}.txt"
    contenido=""
    with open(nombreArchivo,"r") as f:
        contenido=f.read()
    print(len(contenido))
    print(size*numPalabras)
    assert len(contenido)==size*numPalabras    

    
def generarPalabrass(size, numPalabras):
    for i in range(numPalabras):
        generarPalabra(size,numPalabras)

#testPalabra("abcdefghijklmnopqrstuvwxyz")
if(__name__=="__main__"):
    #generarPalabrass(30,100)
    #testLength()
    testPalabra()