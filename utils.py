import random

def generarPalabra(size,numPalabras ):
    l = []
    abc = "abcdefghijklmnopqrstuvwxyz"

    for i in range(size):
        l.append(abc[random.randint(0,len(abc) - 1 )])
    "".join(l)

    f = open(f'palabrasAleatorias_{size * numPalabras}.txt', 'a+')
    for i in range(len(l)):
        f.write(l[i])

    f.close()

def testPalabra(abc):
    while True:
        index = random.randint(0, len(abc) - 1)
        if (index > 25):
            print(index)
            break
def testLength():
    size= 30
    numPalabras = 100
    generarPalabrass(size,numPalabras)
    nombreArchivo = f"palabrasAleatorias_{size*numPalabras}.txt"
    with open()
    
def generarPalabrass(size, numPalabras):
    for i in range(numPalabras):
        generarPalabra(size)

#testPalabra("abcdefghijklmnopqrstuvwxyz")
generarPalabrass(30,100)
