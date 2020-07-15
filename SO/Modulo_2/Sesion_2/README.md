# Sesión 2
### Ejercicio 1: ¿Qué hace el siguiente programa?
***
```
/*
tarea3.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Este programa fuente est� pensado para que se cree primero un programa con la parte
 de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y entender
 la llamada umask.
En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
 con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo
 a los permisos que actualmente tiene un archivo frente a un establecimiento de permisos
 absoluto.
*/

#include<sys/types.h>
#include<unistd.h>		
#include<sys/stat.h>
#include<fcntl.h>		
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
int fd1,fd2;
struct stat atributos;

//CREACION DE ARCHIVOS
/*
Se abre el fichero (o se crea si no existe) con nombre "archivo1", se limpia y se abre
con permisos solo de escritura. Además al fichero se le dan permisos de lectura,
escritura y ejecución para el grupo.
*/
if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
	printf("\nError %d en open(archivo1,...)",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

/*
Se pone la máscara de permisos por defecto sin ningún permisos, para así los valores
siguiente de permisos que le añadamos sean respecto a que no tiene nada, ya que la
mascara lo que hace es coger la máscara actual y le hace la operación and con la
negación de los permisos que le pasemos.
*/
umask(0);

//Se abre un fichero o se crea similar al primero.
if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
	printf("\nError %d en open(archivo2,...)",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

//CAMBIO DE PERMISOS
/*
Se cargan los metadatos del archivo1 en la variable atributos que serán utilizados para
luego cambiar los permisos del mismo.
*/
if(stat("archivo1",&atributos) < 0) {
	printf("\nError al intentar acceder a los atributos de archivo1");
	perror("\nError en lstat");
	exit(EXIT_FAILURE);
}

/*
En estos dos chmod que se realizar se cambian los permisos del fichero1 y fichero2 de
diferentes formas el primero lo que hace es darle permisos de ejecución al grupo y se
activa la asignación del GID del propietario al GID efectivo del proceso que ejecute
el archivo. En el fichero2 en cambio lo que se le añaden son permisos de escritura,
lectura y ejecución para el usuario, lectura y escritura para el grupo y de lectura
para otros.
*/
if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
	perror("\nError en chmod para archivo1");
	exit(EXIT_FAILURE);
}
if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
	perror("\nError en chmod para archivo2");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
```

### Ejercicio 2: Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte como entrada:
```
  - Un argumento que representa el 'pathname' de un directorio.
  - Otro argumento que es un número octal de 4 dígitos (similar al que se puede utilizar
    para cambiar los permisos en la llamada al sistema chmod). Para convertir este
    argumento tipo cadena a un tipo numérico puedes utilizar la función strtol. Consulta
    el manual en línea para conocer sus argumentos.
```
### El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los permisos de todos los archivos que se encuentren en el directorio indicado en el primer argumento.
### El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio que esté formada por:
```
<nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>
```
### Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente información en la línea de salida:
```
<nombre_de_archivo> : <errno> <permisos_antiguos>
```
***

```
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
```

### Ejercicio 3:  Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el grupo y para otros. Además del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de espacio ocupado por dichos archivos. El formato de la nueva orden será:
```
$> ./buscar <pathname>
```
### donde <pathname> especifica la ruta del directorio a partir del cual queremos que empiece a analizar la estructura del árbol de subdirectorios. En caso de que no se le de argumento, tomará como punto de partida el directorio actual. Ejemplo de la salida después de ejecutar el programa:
```
Los i-nodos son:
./a.out 55
./bin/ej 123
./bin/ej2 87
...
Existen 24 archivos regulares con permiso x para grupo y otros
El tamaño total ocupado por dichos archivos es 2345674 bytes
```
***

```
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
```

### Ejercicio 4: Implementa de nuevo el programa buscar del ejercicio 3 utilizando la llamada al sistema nftw.

```
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
```
