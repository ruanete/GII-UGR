#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
  char *archivo_regular;
  struct stat atributos;
  int inicial=0, actual=0, tamAux=0;

  if(argc!=2){
    printf("USO: ./chequeoarchivo <archivo_regular>\n");
    exit(EXIT_FAILURE);
  }

  //Guardo la ruta del fichero regular dado como argumento.
  archivo_regular = argv[1];

  //Saco el stat del archivo regular usado para comprobar su tamaño
  if(stat(archivo_regular, &atributos) < 0){
    printf("\nError al intentar acceder a los atributos de %s\n", archivo_regular);
    perror("\nError en lstat");
    exit(EXIT_FAILURE);
  }

  //Guardo el tamaño inicial en dos variables una nunca cambiará y la otra puede cambiar, la que nos dirá cuando salir del bucle while.
  actual = atributos.st_size;
  inicial = actual;

  while(stat(archivo_regular, &atributos) >= 0){
    actual = atributos.st_size;
    if(tamAux!=actual){
      printf("%10d\n", actual-inicial);
    }
    tamAux = actual;
  }
}
