#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *orden1, *redireccion, *orden2;
  int fd[2];
  pid_t pid;

  if(argc!=4){
    printf("No has pasado tres argumentos: ./ejercicio1 [orden de linux 1] \"|\" [orden de linux 2]\n");
    exit(EXIT_FAILURE);
  }else{
    orden1 = argv[1];
    redireccion = argv[2];
    orden2 = argv[3];

    if(strcmp(redireccion, "|")!=0){
      printf("El segundo argumento debe ser \"|\".\n");
      return 0;
    }
  }

  pipe(fd);

  if((pid = fork()) < 0){
    perror("\nError en el fork");
    exit(EXIT_FAILURE);
  }

  if(pid==0){
    close(fd[0]);
    if(fcntl(fd[1], F_DUPFD, 0) == -1) perror("Fallo en fcntl\n");
    execlp(orden1, orden1, NULL);
  }else{
    close(fd[1]);
    if(fcntl(fd[0], F_DUPFD, 1) == -1) perror("Fallo en fcntl\n");
    execlp(orden2, orden2, NULL);
  }

  return 0;
}
