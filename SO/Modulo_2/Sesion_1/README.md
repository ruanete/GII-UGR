# Sesión 1
### Ejercicio 1: ¿Qué hace el siguiente programa? Probad tras la ejecución del programa las siguientes órdenes del shell: $> cat archivo y $> od -c archivo
***
```
/*
tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probad tras la ejecución del programa: $>cat archivo y $> od -c archivo
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";
int main(int argc, char *argv[])
int fd;

/* En el primer if lo que se realiza es la apertura y si fuera necesario la creación de un fichero con permisos de lectura y escritura para el usuario.
*/
if( (fd=open("archivo",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
 printf("\nError %d en open",errno);
 perror("\nError en open");
 exit(-1);
}

/* En este segundo if lo que se realiza es la escritura en el fichero anteriormente abierto de los primeros 10 carácteres del buffer1 (buf1), es decir, escribiría abcdefghij.
*/
if(write(fd,buf1,10) != 10) {
 perror("\nError en primer write");
 exit(-1);
}

/* En este tercer if lo que se realiza es mover el puntero de escritura en el descriptor de archivo (fd) 40 bytes a la derecha del fichero es decir quedaria abcdefghij-40bytes-puntero.
*/
if(lseek(fd,40,SEEK_SET) < 0) {
 perror("\nError en lseek");
 exit(-1);
}

/* En este ultimo if lo que se realiza es la escritura en el descriptor de archivo de los 10 bytes existentes en buffer2 (buf2), quedando por lo tanto, abcdefghij-40 bytes vacios-ABCDEFGHIJ.
*/
if(write(fd,buf2,10) != 10) {
 perror("\nError en segundo write");
 exit(-1);
}
close(fd);
return 0;
}
```
El resultado de la ejecución con cat es el siguiente:
```
abcdefghijABCDEFGHIJ
```

El resultado de la ejecución con od es el siguiente:
```
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000040  \0  \0  \0  \0  \0  \0  \0  \0   A   B   C   D   E   F   G   H
0000060   I   J
0000062
```

### Ejercicio 2: Implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la siguiente información:
```
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
Bloque n
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
```
### Si no se pasa un argumento al programa se debe utilizar la entrada estándar como archivo de entrada.
### Modificación adicional. ¿Cómo tendrías que modificar el programa para que una vez finalizada la escritura en el archivo de salida y antes de cerrarlo, pudiésemos indicar en su primera línea el número de etiquetas ''Bloque i'' escritas de forma que tuviese la siguiente apariencia?:
```
El número de bloques es <nº_bloques>
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
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

int main(int argc, char *argv[]) {
	int fd;
	int fdFinal;
	int bytesLeidos;
	char cadena[80];
	char cadenaLeida[80];
	int contador=1;

	if( (fd=open(argv[1],O_RDONLY,S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	if( (fdFinal=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(-1);
	}

	while(bytesLeidos=read(fd, cadenaLeida, 80)){
		sprintf(cadena, "Bloque %d\n",contador);
		write(fdFinal, cadena, strlen(cadena));

		sprintf(cadena, "%s\n", cadenaLeida);
		write(fdFinal, cadena, strlen(cadena));
		contador++;
	}

	if(lseek(fdFinal,0,SEEK_SET) < 0) {
		perror("\nError en lseek");
		exit(EXIT_FAILURE);
	}

	sprintf(cadena, "El número de bloques es %d\n", contador);
	write(fdFinal,cadena,strlen(cadena));

	close(fd);
	return 0;
}
```

### Ejercicio 3: ¿Qué hace el siguiente programa?
```
/*
tarea2.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
int i;
struct stat atributos;
char tipoArchivo[30];

if(argc<2) {
	printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
	exit(EXIT_FAILURE);
}
for(i=1;i<argc;i++) {
	printf("%s: ", argv[i]);
	if(lstat(argv[i],&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de %s",argv[i]);
		perror("\nError en lstat");
	}
	else {
		if(S_ISREG(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
		else if(S_ISDIR(atributos.st_mode)) strcpy(tipoArchivo,"Directorio");
		else if(S_ISCHR(atributos.st_mode)) strcpy(tipoArchivo,"Especial de caracteres");
		else if(S_ISBLK(atributos.st_mode)) strcpy(tipoArchivo,"Especial de bloques");
		else if(S_ISFIFO(atributos.st_mode)) strcpy(tipoArchivo,"Tuberia con nombre (FIFO)");
		else if(S_ISLNK(atributos.st_mode)) strcpy(tipoArchivo,"Enlace relativo (soft)");
		else if(S_ISSOCK(atributos.st_mode)) strcpy(tipoArchivo,"Socket");
		else strcpy(tipoArchivo,"Tipo de archivo desconocido");
		printf("%s\n",tipoArchivo);
	}
}

return EXIT_SUCCESS;
}
```
***
Basicamente el funcionamiento del programa es la de comprobar que tipo de archivo es el fichero que le pasamos como argumento. Lo que realiza es coger los metadatos del fichero pasado como argumento y se van comprobando que valores son los que corresponden con los flags activos en ese momento y en función de esto como sabemos a que corresponde cada uno se imprime el tipo de dicho fichero.

### Ejercicio 4: Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode) usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de la struct stat, y comprueba que funciona en un programa simple. Consulta en un libro de C o en internet cómo se especifica una macro con argumento en C.
```
#define S_ISREG2(mode) ...
```
