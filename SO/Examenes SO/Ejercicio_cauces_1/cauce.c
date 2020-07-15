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
  int numero_entero;
  char argumento_tail[100];
  int fd[2], fd1[2];
  pid_t pid;
  char whitespace = ' ';
  char argumento_cut[100];

  if(argc!=2){
    printf("USO: ./cauce <numero_entero>\n");
    exit(EXIT_FAILURE);
  }

  numero_entero = atoi(argv[1]);

  sprintf(argumento_tail, "-%d", numero_entero);

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
    execlp("tail", "tail", argumento_tail, NULL);
  }else{
    close(fd1[1]);
    dup2(fd1[0], STDIN_FILENO);
    sprintf(argumento_cut, "-d%c", whitespace);
    execlp("cut", "cut", argumento_cut, "-f1", NULL);
  }

  close(fd1[0]);

  return 0;
}
