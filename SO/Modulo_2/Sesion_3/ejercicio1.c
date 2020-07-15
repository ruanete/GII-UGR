#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
  int numero;
  pid_t pid;

  if(argc!=2){
    printf("No has pasado un argumento\n");
    exit(EXIT_FAILURE);
  }else{
    numero = strtol(argv[1], NULL, 10);
  }

  printf("El numero entero es %d\n", numero);

  if((pid=fork()) < 0){
    perror("\nError en el fork.\n");
    exit(-1);
  }else if(pid==0){
    printf("\nSoy el proceso hijo %d\n", getpid());

    if((numero%2)==0)
      printf("El numero %d es par.\n", numero);
    else
      printf("El numero %d es impar.\n", numero);
  }else{
    printf("Soy el proceso padre %d\n", getppid());

    if((numero%4)==0)
      printf("El numero %d es divisible por 4.\n", numero);
    else
      printf("El numero %d no es divisible por 4.\n", numero);
  }
}
