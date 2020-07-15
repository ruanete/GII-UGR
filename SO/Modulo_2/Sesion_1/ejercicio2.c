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
