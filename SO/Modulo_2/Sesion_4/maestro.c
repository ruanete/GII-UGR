#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
  int intervalo_inferior, intervalo_superior;
  int subintervalo_inferior1, subintervalo_inferior2;
  int subintervalo_superior1, subintervalo_superior2;
  int fd1[2], fd2[2];
  int params1[2];
  int params2[2];
  pid_t pid;
  char ini[100];
  char fin[100];
  int bytesLeidos1, bytesLeidos2, val1, val2;

  if(argc!=3){
    printf("No has pasado dos argumentos: ./maestro [intervalo inferior] [intervalo superior]\n");
    exit(EXIT_FAILURE);
  }else{
    intervalo_inferior = strtol(argv[1], NULL, 10);
    intervalo_superior = strtol(argv[2], NULL, 10);
    subintervalo_inferior1 = intervalo_inferior;
    subintervalo_superior1 = intervalo_inferior + ((intervalo_superior - intervalo_inferior)/2);
    subintervalo_inferior2 = subintervalo_superior1;
    subintervalo_superior2 = intervalo_superior;
    params1[0] = subintervalo_inferior1;
    params1[1] = subintervalo_superior1;
    params2[0] = subintervalo_inferior2;
    params2[1] = subintervalo_superior2;
  }

  pipe(fd1);
  pipe(fd2);

  if((pid = fork()) < 0){
    perror("\nError en el fork");
    exit(EXIT_FAILURE);
  }else if(pid==0){
    close(fd1[0]);
    sprintf(ini, "%d", params1[0]);
    sprintf(fin, "%d", params1[1]);
    dup2(fd1[1], STDOUT_FILENO);
    execl("./esclavo", "esclavo", ini, fin, NULL);
  }else{
    if((pid = fork()) < 0){
      perror("\nError en el fork");
      exit(EXIT_FAILURE);
    }else if(pid==0){
      close(fd2[0]);
      sprintf(ini, "%d", params2[0]);
      sprintf(fin, "%d", params2[1]);
      dup2(fd2[1], STDOUT_FILENO);
      execl("./esclavo", "esclavo", ini, fin, NULL);
    }else{
      close(fd1[1]);

      dup2(fd1[0],STDIN_FILENO);
      while ((bytesLeidos1 = read(fd1[0], &val1, sizeof(int))) > 0) {
				printf("Valor: %d\n",val1);
		 	}
      close(fd1[0]);
    }

    close(fd2[1]);

    dup2(fd2[0],STDIN_FILENO);
    while ((bytesLeidos2 = read(fd2[0], &val2, sizeof(int))) > 0) {
      printf("Valor: %d\n",val2);
    }
    close(fd2[0]);
  }
}
