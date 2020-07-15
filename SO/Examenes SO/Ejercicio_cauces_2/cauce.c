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

int main(int argc, char *argv[]) {
  int bytesLeidos=0, numero_entero=0;
  int fd[2], fd1[2];
  pid_t pid;
  char n;

  pipe(fd);
  pipe(fd1);

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }

  if(pid==0){
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    execlp("ls", "ls", "-l", NULL);
  }

  close(fd[1]);

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }

  if(pid==0){
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);

    close(fd1[0]);
    dup2(fd1[1], STDOUT_FILENO);
    execlp("wc", "wc", "-l", NULL);
  }else{
    close(fd1[1]);

    if((bytesLeidos = read(fd1[0], &n, sizeof(char))) < 0){
      perror("Fallo en el read\n");
      exit(EXIT_FAILURE);
    }
    int numero_entero = (int)n - 48;

    if(numero_entero % 2 == 0){
      printf("El número %d es par\n", numero_entero);
    }else{
      printf("El número %d es impar\n", numero_entero);
    }
  }

  close(fd1[0]);

  return 0;
}
