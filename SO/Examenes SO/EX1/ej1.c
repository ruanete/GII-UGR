#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>

int busquedaEnTmp(char* fichero){
  DIR *directorioTmpAbierto;
  char *nombretmp = "/tmp";
  struct dirent *directorio;

  if((directorioTmpAbierto = opendir(nombretmp)) == NULL){
    printf("\nError %d en opendir",errno);
    perror("\nError en opendir");
    exit(EXIT_FAILURE);
  }

  while((directorio = readdir(directorioTmpAbierto)) != NULL){
    if(strcmp(directorio->d_name, fichero)==0){
      //printf("%s\n", directorio->d_name);
      closedir(directorioTmpAbierto);
      return 1;
    }
  }

  closedir(directorioTmpAbierto);
  return 0;
}

void busquedaDirectorio(char *pathname){
	DIR *directorioAbierto;
	struct dirent *directorio;
	struct stat atributos;
	char fichero[300];

  if((directorioAbierto = opendir(pathname)) == NULL){
    printf("\nError %d en opendir",errno);
    perror("\nError en opendir");
    exit(EXIT_FAILURE);
  }

  while((directorio = readdir(directorioAbierto)) != NULL){
    if(strcmp(directorio->d_name, ".") && strcmp(directorio->d_name, "..")){
      sprintf(fichero, "%s/%s", pathname, directorio->d_name);
      //printf("FICHERO: %s\n", fichero);
      if(busquedaEnTmp(directorio->d_name)==1){
        struct stat atributos;
        if(lstat(directorio->d_name, &atributos) < 0){
          perror("Error lstat\n");
        }

        printf("Fichero %s con tamaño %ld y su propietario %d\n", directorio->d_name, atributos.st_size, atributos.st_uid);
      }
    }
  }

  closedir(directorioAbierto);
}

int main(int argc, char *argv[]) {
	char *pathname;
  char pathnameAux[200];
  char *nombretmp = "/tmp";
  char *nombrehome = getenv("HOME");

	if(argc!=2){
		printf("No has pasado un argumento\n");
		exit(EXIT_FAILURE);
	}else{
    sprintf(pathnameAux, "%s/%s", nombrehome, argv[1]);
    pathname = pathnameAux;
    printf("Directorio TMP: %s\n", nombretmp);
    printf("Pathname elegido: %s\n", pathname);
	}

  printf("Los i-nodos son: \n");
  busquedaDirectorio(pathname);

	return 0;
}
