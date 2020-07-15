#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>

int tamanio=0, numeroFicheros=0;

void busquedaDirectorio(char *pathname){
	DIR *directorioAbierto;
	struct dirent *directorio;
	struct stat atributos;
	char fichero[200];

  if((directorioAbierto = opendir(pathname)) == NULL){
    printf("\nError %d en opendir",errno);
    perror("\nError en opendir");
    exit(EXIT_FAILURE);
  }

  while((directorio = readdir(directorioAbierto)) != NULL){
    if(strcmp(directorio->d_name, ".") && strcmp(directorio->d_name, "..")){
      sprintf(fichero, "%s/%s", pathname, directorio->d_name);

      if(stat(fichero, &atributos) < 0){
        printf("\nError al intentar acceder a los atributos de %s\n", directorio->d_name);
        perror("\nError en lstat");
        exit(EXIT_FAILURE);
      }

      if(S_ISREG(atributos.st_mode) && (atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){
        printf("%s %ld\n", fichero, directorio->d_ino);
        tamanio += (int) atributos.st_size;
        numeroFicheros++;
      }else if(S_ISDIR(atributos.st_mode)){
        busquedaDirectorio(fichero);
      }
    }
  }

  closedir(directorioAbierto);
}

int main(int argc, char *argv[]) {
	char *pathname;

	if(argc!=2){
		printf("No has pasado un argumento\n");
		exit(EXIT_FAILURE);
	}else{
		pathname = argv[1];
	}

  printf("Los i-nodos son: \n");
  busquedaDirectorio(pathname);
  printf("Existen %d archivos regulares con permiso x para el grupo y otros.\n", numeroFicheros);
  printf("El tamaño total ocupado por dichos ficheros es %d bytes.\n", tamanio);

	return 0;
}
