from random import randrange
import sys

def numeroAleatorio(numeroMax):
    return randrange(numeroMax);

if __name__ == "__main__":
    numRandom = numeroAleatorio(100);

    # print('Esto es una prueba',numRandom)

    for i in range(1,10):
        numeroUsuario = int(input('Introduzca un numero: '))
        if numRandom==numeroUsuario:
            print('¡Has acertado el numero!')
            sys.exit()
            break
        else:
            if numeroUsuario > numRandom:
                print('El valor que buscas es menor que el introducido.')
            else:
                print('El valor que buscas es mayor que el introducido.')
    print('¡Has perdido, no has acertado el número!')
