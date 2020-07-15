/*
Se compila como: gcc maestro.c -o maestro
USO: ./maestro <directorio1> <directorio2> <directorioN>
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
#include<unistd.h>

int main(int argc, char *argv[]) {
  int numDirectorios=0;
  pid_t pid;
  char nombreFichero[300];
  int fd[2];
  int bytesLeidos;
  char datoLeido[500];
  int bloquesTotales=0;

  if(argc<2){
		printf("USO: ./maestro <directorio1> <directorio2> <directorioN>\n");
		exit(EXIT_FAILURE);
	}

  //Genero un vector de todos los nombres de los directorios con el tamaño del número de argumentos pasados y guardo el tamaño en una variable
  numDirectorios = argc - 1;
  char *directorios[numDirectorios];

  //Recorremos todos los argumentos y los vamos metiendo en cada posición del vector de directorios
  for(int i=1;i<argc;i++){
    directorios[i-1] = argv[i];
  }

  //Creamos un pipe (cauce) para recoger valores y el padre los sumará
  pipe(fd);

  //Recorremos el vector de directorios y generamos un hijo que ejecutará "contar"
  for(int i=0;i<numDirectorios;i++){
    if((pid = fork()) < 0){
      perror("\nError en el fork");
      exit(EXIT_FAILURE);
    }

    if(pid == 0){
      close(fd[0]);
      sprintf(nombreFichero, "%d.Directorios", getpid());
      dup2(fd[1], STDOUT_FILENO);
      execl("./contar", "contar", nombreFichero, directorios[i], NULL);
    }
  }

  //Leemos el cauce y se van sumando valores
  close(fd[1]);
  dup2(fd[0],STDIN_FILENO);
  while((read(fd[0],&datoLeido, sizeof(datoLeido))) > 0){
    bloquesTotales += atoi(datoLeido);
	}

  printf("Bloques totales leidos: %d\n", bloquesTotales);

  return EXIT_SUCCESS;
}
