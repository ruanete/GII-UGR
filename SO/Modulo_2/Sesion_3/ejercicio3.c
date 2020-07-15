#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int nprocs = 20;
  pid_t childpid;

  //Jerarquía de procesos tipo 1
  //El hijo generado con el fork es el padre siempre del siguiente proceso creado.
  /*for (int i=1; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }

    printf("\nProceso con PID %d y mi padre con PID %d\n", getpid(), getppid());

    if (childpid)
      break;
  }*/

  //Jerarquía de procesos tipo 2
  //En cuanto se crea un nuevo proceso se finaliza al momento con el break.
  for (int i=1; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }

    printf("\nProceso con PID %d y mi padre con PID %d\n", getpid(), getppid());

    if (!childpid)
      break;
  }
}
