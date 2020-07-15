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
  char *pathname;
  char buf[200];
  char cadena[300], cadena1[300], cadena2[300];
  pid_t pid;
  int fd[2], fd1, fd2[2];
  int numBytes;
  int n;

  if(argc!=2){
		printf("No has pasado un argumento\n");
		exit(EXIT_FAILURE);
	}else{
		pathname = argv[1];
	}

  pipe(fd);
  pipe(fd2);

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }

  if(pid==0){
    //Cerramos el cauce para lectura
    close(fd[0]);
    //Cambiamos la salida estandar por el cauce
    dup2(fd[1], STDOUT_FILENO);
    //Ejecutamos el programa tam_quijote
    execl("./tam_quijote", "tam_quijote", pathname, NULL);

    //Cierro el cauce al completo
    close(fd[1]);
  }

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }

  if(pid==0){
    //Cierro para lectura
    close(fd2[0]);
    //Cambiamos la salida estandar por el cauce
    dup2(fd2[1], STDOUT_FILENO);
    //Ejecutamos el programa tam_quijote
    execlp("wc", "wc", "-w", "quijote.txt", NULL);
    //Cierro el cauce al completo
    close(fd2[1]);
  }

//Primera parte: Leemos del cauce primero y escribimos el tamaño en bytes en resultado.txt
  //Cerramos el cauce para escritura
  close(fd[1]);

  //Leemos del cauce el valor si no hay valor finalizamos la aplicación por que eso quiere decir
  //que quijote.txt no fue encontrado o no tuvo los permisos que buscamos
  if((numBytes=read(fd[0], &n, sizeof(n))==0)){
    exit(EXIT_FAILURE);
  }

  //Cerramos el cauce al completo
  close(fd[0]);

  //Abro el fichero para poder escribir en el
  if( (fd1=open("resultado.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR))<0) {
    printf("\nError %d en open",errno);
    perror("\nError en open");
    exit(EXIT_FAILURE);
  }

  //Escribo en el fichero
  sprintf(cadena, "Tamaño quijote.txt: %d\n", n);
  write(fd1,cadena,strlen(cadena));

//Segunda parte: Leermos el cauce segundo y escribimos al final de resultado.txt
  //Escribo en el fichero dos saltos de linea
  write(fd1,"\n\n",strlen("\n\n"));

  //Cerramos el cauce para escritura donde tenemos el wc del quijote.txt
  close(fd2[1]);

  //Leemos del cauce el valor
  read(fd2[0], &cadena1, sizeof(cadena1));
  char* word_count=strtok(cadena1, " ");
  sprintf(cadena2, "Palabras: %s", word_count);
  write(fd1,cadena2,strlen(cadena2));

  //Cerramos el cauce al completo
  close(fd2[0]);

  //Cierro el fichero donde estaba escribiendo resultado.txt
  close(fd1);
}
