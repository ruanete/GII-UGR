/*
Se compila como: gcc contar.c -o contar
USO: ./contar <archivo_salida> <directorio>
*/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

unsigned long suma_bloques = 0;

int main(int argc, char *argv[]) {
  char *archivo_salida, *directorio;
  DIR *directorioAbierto;
  int fd;
  struct dirent *dir;
  struct stat atributos;
  char fichero[300];
  char texto[300];

  if(argc!=3){
		printf("USO: ./contar <archivo_salida> <directorio>\n");
		exit(EXIT_FAILURE);
	}

  //Guardo los argumentos en dos variables.
  archivo_salida = argv[1];
  directorio = argv[2];

  //Imprimo los valores pasados como argumentos para comprobarlos.
  //printf("Archivo salida es %s y el directorio es %s.\n", archivo_salida, directorio);

  //Compruebo que exista el directorio dado como argumento
  if((directorioAbierto = opendir(directorio)) == NULL){
    printf("\nError %d en opendir",errno);
    perror("\nError en opendir");
    exit(EXIT_FAILURE);
  }

  //Compruebo si existe o no el fichero dado como argumento, se crea si no y se abre
  if( (fd = open(archivo_salida, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0 ) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

  //Recorro el directorio dado como argumento y se comprueban aquellos archivos de tipo directorio que tengan permiso para el grupo.
  while((dir = readdir(directorioAbierto)) != NULL){
    //printf("%s\n", dir->d_name);
    sprintf(fichero, "%s/%s", directorio, dir->d_name);

    //Se calcula el stat del fichero actual
    if(stat(fichero, &atributos) < 0){
      printf("\nError al intentar acceder a los atributos de %s\n", dir->d_name);
      perror("\nError en lstat");
      exit(EXIT_FAILURE);
    }

    //Se comprueba que el fichero leido del directorio pasado como argumento es un directorio y además tiene permisos de ejecución para el grupo
    if(S_ISDIR(atributos.st_mode) && (atributos.st_mode & S_IXGRP)){
      //Se suman el numero de bloques del directorio elegido
      suma_bloques += atributos.st_blocks;

      //Se genera el mensaje que se va a introducir en el fichero
      sprintf(texto, "Fichero %s con un número de bloques total %ld\n", fichero, atributos.st_blocks);

      //Se introduce en el fichero la línea con el mensaje
      write(fd, texto, strlen(texto));
    }
  }

  printf("%ld\n", suma_bloques);

  close(fd);
  closedir(directorioAbierto);
  return EXIT_SUCCESS;
}
