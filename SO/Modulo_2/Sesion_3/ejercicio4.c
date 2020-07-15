#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int nprocs = 5, estado;
  pid_t pid;

  for (int i=0; i < nprocs; i++) {
    if((pid = fork())<0){
      perror("Error en fork\n");
      exit(-1);
    }

    if(pid==0){
      printf("Soy el hijo %d\n", getpid());
      exit(0);
    }
  }

  for(int i=4; i>=0; i--){
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con %d\n", pid);
    printf("Solo me quedan %i hijos vivos\n", i);
  }
}
