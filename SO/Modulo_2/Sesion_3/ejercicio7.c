//Compilar: gcc -std=c99 ejercici7.c -o ejercicio7

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
  pid_t pid;
  int estado;
  bool activarBG = false;
  char *orden;
	char *parametros[100];
  int numParams;
  int j=0;

  if(argc < 2) {
    printf("Modo de uso: %s <programa> [opciones] [bg]\n\n", argv[0]);
		exit(1);
  }else {
    numParams = argc;
    if(strcmp(argv[argc-1], "bg") == 0) {
      activarBG=true;
      numParams--;
    }

    orden = argv[1];

    for(int i=1; i < numParams; i++ ){
      parametros[j] = argv[i];
      j++;
    }

    if(j<=0){
      parametros[0] = "";
      parametros[1] = NULL;
    }else{
      parametros[j]= NULL;
    }

    if(activarBG){
      printf("Se ejecuta en modo background. \n");
      if((pid=fork())<0){
        perror("\nError en el fork");
      	exit(EXIT_FAILURE);
      }else if(pid!=0){
        exit(EXIT_SUCCESS);
      }

      /*printf("ORDEN: %s\n", orden);
      for(int i=0;i<=j;i++){
        printf("%s\n", parametros[i]);
      }*/

      if( (execv(orden,parametros)<0)) {
        perror("\nError en el execl");
        exit(EXIT_FAILURE);
      }
    }else{
      printf("Se ejecuta en modo foreground. \n");
      if( (execv(orden,parametros)<0)) {
    		perror("\nError en el execl");
    		exit(EXIT_FAILURE);
    	}
    }
  }

  exit(EXIT_SUCCESS);
}
