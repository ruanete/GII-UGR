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

char** obtener_datos(int total_datos, char* buf){
  char *datos[total_datos];
  char *t;
  int i=0;
  t=strtok(buf, "|");
  while(t!=NULL){
    datos[i]=t;
    t=strtok(NULL, "|");
    i++;
  }
  return datos;
}

int main(int argc, char *argv[]) {
  char *pathname;
  char buf[200];
  pid_t pid;
  int fd[2];
  int numBytes;

	if(argc!=2){
		printf("No has pasado un argumento\n");
		exit(EXIT_FAILURE);
	}else{
		pathname = argv[1];
	}

  pipe(fd);

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }else if(pid==0){
    //Cerramos el cauce para lectura
    close(fd[0]);
    //Cambiamos la salida estandar por el cauce
    dup2(fd[1], STDOUT_FILENO);
    //Ejecutamos el programa ejercicio1
    execlp("./ejercicio1", "ejercicio1", pathname, NULL);
    close(fd[1]);
  }else{
    //Cerramos el cauce para escritura
    close(fd[1]);
    //Leemos del cauce y vamos sacando por pantalla los valores
    char *mensaje;
    while((numBytes=read(fd[0], buf, sizeof(buf))>0)){
      printf("%s", &buf[0]);
      //mensaje = &buf[0];
      //mensaje = mensaje - 1;
      //printf("%s y numero de bytes leidos: %d\n", mensaje, strlen(mensaje));
      char **datos = obtener_datos(3, &buf[0]);
      //char* nombre = datos[0];
      //char* permisos = datos[1];
      //char* tamanio = datos[2];
      //printf ("PRUEBA y TAM %ld: %s\n", sizeof(buf), buf);
      //printf("Nombre %s con permisos %s y tamanio %s", nombre, permisos, tamanio);
  	}

    close(fd[0]);
  }
}
