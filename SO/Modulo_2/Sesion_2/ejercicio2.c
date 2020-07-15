#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>

int main(int argc, char *argv[]) {
	int permisos;
	char *pathname;
	DIR *directorioAbierto;
	struct dirent *directorio;
	struct stat atributos;
	char fichero[200];

	if(argc!=3){
		printf("No has pasado dos argumento\n");
		exit(EXIT_FAILURE);
	}else{
		pathname = argv[1];
		permisos = strtol(argv[2], NULL, 8);
		printf("Este es el pathname: %s y estos los permisos nuevos: %d\n", pathname, permisos);
	}

	if((directorioAbierto = opendir(pathname)) == NULL){
		printf("\nError %d en opendir",errno);
		perror("\nError en opendir");
		exit(EXIT_FAILURE);
	}

	while((directorio = readdir(directorioAbierto)) != NULL){
		if(strcmp(directorio->d_name, ".") && strcmp(directorio->d_name, "..")){
			sprintf(fichero, "%s%s", pathname, directorio->d_name);
			printf("El fichero es: %s\n", fichero);
			if(stat(fichero, &atributos) < 0){
				printf("\nError al intentar acceder a los atributos de %s\n", directorio->d_name);
				perror("\nError en lstat");
				exit(EXIT_FAILURE);
			}

			if(S_ISREG(atributos.st_mode)){
				int permisosAntiguos = atributos.st_mode;

				if(chmod(fichero, permisos) < 0){
					printf("%s : %d %d\n", directorio->d_name, errno, permisosAntiguos);
				}else{
					stat(fichero,&atributos);
					printf("%s : %d %d\n", directorio->d_name, permisosAntiguos, atributos.st_mode);
				}
			}
		}
	}

	closedir(directorioAbierto);
	return 0;
}
