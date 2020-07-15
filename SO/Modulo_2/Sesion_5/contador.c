#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

static int senalesRecibidas[10];

static void sig_USR_hdlr(int sigNum){
  if(sigNum>=0 && sigNum<10){
    senalesRecibidas[sigNum]++;
    printf("La senal %d se ha recibido %d veces", sigNum, senalesRecibidas[sigNum]);
  }else{
    printf("No puedo manejar la senal %d", sigNum);
  }
}

int main(int argc, char *argv[]) {
  struct sigaction sig_USR_nact;
  if(setvbuf(stdout,NULL,_IONBF,0)) {
    perror("\nError en setvbuf");
  }

  sig_USR_nact.sa_handler= sig_USR_hdlr;

  sigemptyset (&sig_USR_nact.sa_mask);
  sig_USR_nact.sa_flags = 0;

  for(int i=1;i<10-1;i++){
    if (sigaction(i, &sig_USR_nact, NULL) < 0) {
			perror("Error al intentar establecer el manejador de senal\n");
			exit(-1);
		}
  }

  while(true);
}
