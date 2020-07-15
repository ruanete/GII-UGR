#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<ftw.h>

int tamanio=0, numeroFicheros=0;

int busquedaDirectorio(const char *pathname, const struct stat* stat, int flags, struct FTW* ftw){
  if(S_ISREG(stat->st_mode) && (stat->st_mode & S_IXGRP) && (stat->st_mode & S_IXOTH)){
    printf("%s %ld\n", pathname, stat->st_ino);
    tamanio += (int) stat->st_size;
    numeroFicheros++;
  }
  return 0;
}

int main(int argc, char *argv[]) {
	char *pathname;

	if(argc!=2){
		printf("No has pasado un argumento\n");
		exit(EXIT_FAILURE);
	}else{
		pathname = argv[1];
	}

  printf("Los i-nodos son %s: \n", pathname);
  if(nftw(pathname, busquedaDirectorio, 10, 0) != 0){
    perror("ntfw");
  }
  printf("Existen %d archivos regulares con permiso x para el grupo y otros.\n", numeroFicheros);
  printf("El tamaño total ocupado por dichos ficheros es %d bytes.\n", tamanio);

	return 0;
}
