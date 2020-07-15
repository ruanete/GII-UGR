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
  char *archivo_regular1, *archivo_regular2;
  pid_t pid;
  int fd, bytesLeidos;
  char val[12];
  val[11]='\0';

  if(setvbuf(stdout,NULL,_IONBF,0)){
    perror("\nError en setbuf");
  }

  if(argc!=3){
    printf("USO: ./chequeoconjunto <archivo_regular1> <archivo_regular2>\n");
    exit(EXIT_FAILURE);
  }

  //Guardo las rutas de los ficheros regulares dados como argumentos.
  archivo_regular1 = argv[1];
  archivo_regular2 = argv[2];

  //Genero el cauce con nombre "datos"
  umask(0);
  mkfifo("datos", 0666);

  //Abro el cauce "datos"
  if((fd=open("datos", O_RDWR,S_IRWXU)<0)){
    perror("Error al abrir el cauce con nombre.");
    exit(-1);
  }

  //write (fd, "ptr", strlen("ptr"));

  //Creo dos hijos con el mismo padre.
  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }else if(pid==0){
    dup2(fd, STDOUT_FILENO);
    execl("./chequeoarchivo", "chequeoarchivo", archivo_regular1, NULL);
  }else{
    if((pid = fork()) < 0){
      perror("\nError en el segundo fork");
      exit(EXIT_FAILURE);
    }else if(pid==0){
      dup2(fd, STDOUT_FILENO);
      execl("./chequeoarchivo", "chequeoarchivo", archivo_regular2, NULL);
    }

    while (bytesLeidos = read(fd, val, 11) != 0) {
      printf("Valor: %s\n",val);
    }
  }
}
