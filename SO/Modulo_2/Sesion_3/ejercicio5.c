#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int nprocs = 5, estado;
  pid_t pid;
  int pids[5];

  for (int i=1; i <= nprocs; i++) {
    if((pids[i] = fork())<0){
      perror("Error en fork\n");
      exit(-1);
    }

    if(pids[i]==0){
      printf("Soy el hijo %d\n", getpid());
      exit(0);
    }
  }

  for(int i=nprocs; i>=0; i-=2){
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con %d\n", pids[i]);
    printf("Solo me quedan %i hijos vivos\n", i);
  }

  for(int i=nprocs-1; i>0; i-=2){
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con %d\n", pids[i]);
    printf("Solo me quedan %i hijos vivos\n", i);
  }
}
