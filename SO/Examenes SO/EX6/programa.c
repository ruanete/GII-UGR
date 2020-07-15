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
#include<limits.h>
#include<ftw.h>
#include<libgen.h>

void signalManagement(int signum) {
  printf("Finalizado hijo inesperadamente\n");
  wait(NULL);
}

int main(int argc, char *argv[]) {
  int fd[2];
  pid_t pid;
  char *directorioactual = "./";
  DIR *directorioAbierto;
	struct dirent *directorio;
	struct stat atributos;
  char ruta[200]="";
  int bytesLeidos;
  char n;
  char *rutaCauce;
  struct flock bloqueo;

  pipe(fd);

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }else if(pid==0){
    //printf("ES EL HIJO\n");
    //Cierro el cauce para escritura
    close(fd[1]);

    //Leo el cauce y lo saco por pantalla (INICIALIZAR VECTOR USADO A "" Y REINICIAR CUANDO LLEGA A /n)
    while((read(fd[0], &n, sizeof(char))) > 0){
      if(n!='\n'){
        sprintf(ruta + strlen(ruta), "%c", n);
      }else{
        //printf("%s\n", ruta);
        execlp("cat", "cat", ruta, NULL);
        sprintf(ruta, "");
      }
    }

    //Cierro el cauce para lectura finalmente
    close(fd[0]);
  }else{
    //Cuando un hijo acaba lo matamos para que no quede zombie
    signal(SIGPIPE, signalManagement);
    //Abrimos el directorio actual
    if((directorioAbierto = opendir(directorioactual)) == NULL){
      printf("\nError %d en opendir",errno);
      perror("\nError en opendir");
      exit(EXIT_FAILURE);
    }

    //Recorremos el directorio actual y realizamos las comprobaciones pertinentes
    while((directorio = readdir(directorioAbierto)) != NULL){
      //Calculo las stat de cada fichero
      if(stat(directorio->d_name, &atributos) < 0){
        printf("\nError al intentar acceder a los atributos de %s\n", directorio->d_name);
        perror("\nError en lstat");
        exit(EXIT_FAILURE);
      }

      //Cierro el cauce para lectura
      close(fd[0]);

      //Compruebo si es regular y escribo en pantalla y parte al cauce
      if(S_ISREG(atributos.st_mode)){
        printf("%ld %d\n", atributos.st_ino, atributos.st_uid);
        sprintf(rutaCauce, "%s\n", directorio->d_name);
        write(fd[1], rutaCauce, strlen(rutaCauce));

        if(!(atributos.st_mode & S_IRUSR)){
          if(chmod(directorio->d_name, S_IRUSR) < 0){
            perror("\nError en chmod para el archivo");
            exit(-1);
          }
        }
      }
    }
  }
}
