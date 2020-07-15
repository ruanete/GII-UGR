import random
from time import time

def algoritmoSeleccion(lista):
    for i in range(len(lista)):
        for j in range(i+1,len(lista)):
            if(lista[j] < lista[i]):
                aux = lista[i]
                lista[i] = lista[j]
                lista[j] = aux

    return lista

def algoritmoBurbuja(lista):
    for i in range(1,len(lista)):
        for j in range(len(lista) - i):
            if(lista[j] > lista[j+1]):
                aux = lista[j]
                lista[j] = lista[j+1]
                lista[j+1] = aux

    return lista

if __name__ == "__main__":
    tamañoArray = int(input('Introduzca el tamaño del array: '))
    lista=[]

    for i in range(tamañoArray):
        lista.append(random.randint(0, 100))

    print('LISTA INICIAL SIN ORDENAR: ', lista)

    start_time = time()
    solucionSeleccion = algoritmoSeleccion(lista)
    elapsed_time = time() - start_time
    print('ALGORITMO SELECCION: ', solucionSeleccion)
    print("Elapsed time SELECCION: %0.10f seconds." % elapsed_time)

    start_time = time()
    solucionSeleccion = algoritmoBurbuja(lista)
    elapsed_time = time() - start_time
    print('ALGORITMO BURBUJA: ', algoritmoBurbuja(lista))
    print("Elapsed time SELECCION: %0.10f seconds." % elapsed_time)
