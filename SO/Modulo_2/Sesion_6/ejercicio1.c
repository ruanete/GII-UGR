#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[]) {
  char *orden, *fichero, *redireccion;
  int fd;

  if(argc!=4){
    printf("No has pasado tres argumentos: ./ejercicio1 [orden de linux] < o > [nombre de fichero]\n");
    exit(EXIT_FAILURE);
  }else{
    orden = argv[1];
    redireccion = argv[2];
    fichero = argv[3];

    if(strcmp(redireccion, "<")==0){
      printf("ORDEN: %s, REDIRECCION: %s, FICHERO: %s\n", orden, redireccion, fichero);
      fd=open(fichero,O_RDONLY);
      close(STDIN_FILENO);
      if(fcntl(fd, F_DUPFD, STDIN_FILENO) == -1) perror("Fallo en fcntl\n");
    }else if(strcmp(redireccion, ">")==0){
      printf("ORDEN: %s, REDIRECCION: %s, FICHERO: %s\n", orden, redireccion, fichero);
      fd=open(fichero,O_CREAT|O_WRONLY);
      close(STDOUT_FILENO);
      if(fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1) perror("Fallo en fcntl\n");
    }else{
      printf("El segundo argumento debe ser < o >.\n");
      return 0;
    }

    if(execlp(orden, "", NULL) < 0){
      perror("Error en el execlp.\n");
      exit(-1);
    }

    close(fd);
  }
}
