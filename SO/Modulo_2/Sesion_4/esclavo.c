#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<math.h>

int compruebaPrimo(int n){
  for(int i=2;i<=sqrt(n);i++)
    if(n%i==0) return 0;

  return 1;
}

int main(int argc, char *argv[]) {
  int intervalo_inferior, intervalo_superior;
  int i, j;
  char c[1];

  if(argc!=3){
    printf("No has pasado dos argumentos: ./esclavo [intervalo inferior] [intervalo superior]\n");
    exit(EXIT_FAILURE);
  }else{
    intervalo_inferior = strtol(argv[1], NULL, 10);
    intervalo_superior = strtol(argv[2], NULL, 10);
  }

  for(i=intervalo_inferior; i <= intervalo_superior;i++){
    if(compruebaPrimo(i)){
      write(STDOUT_FILENO, &i, sizeof(int));
    }
  }

  return 0;
}
