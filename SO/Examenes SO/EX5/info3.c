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

#define MAXLEVEL 1

unsigned long inodoActual;

struct FTW {
  int base;
  int level;
};

int busquedaDirectorio(const char *pathname, const struct stat* stat, int flags, struct FTW* ftw){
  if(ftw->level > MAXLEVEL){
    return 0;
  }

  //Si el numero de inodo del fichero actual y el leido del cauce es el mismo lo imprimo
  if(stat->st_ino==inodoActual){
    printf("%s\n", pathname);
  }

  return 0;
}

void signalManagement(int signum) {
  wait(NULL);
}

int main(int argc, char *argv[]) {
  int info[2];
  pid_t pid;
  char rutabin[PATH_MAX];
  int bytesLeidos;
  char* opcion;
  struct stat atributos;
  char *nombrehome = getenv("HOME");
  int status;
  int fd;

  if(argc!=2){
		printf("No has pasado un argumento. USO: ./info3 <OPCION: p o s>\n");
		exit(EXIT_FAILURE);
	}else{
		opcion = argv[1];
    if(strcmp(opcion, "p")!=0 && strcmp(opcion,   "s")!=0){
      perror("Argumento no valido");
      exit(EXIT_FAILURE);
    }
	}

  pipe(info);

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }else if(pid==0){
    //Cerramos el cauce para lectura
    close(info[0]);
    //Cambiamos la salida estandar por el cauce
    dup2(info[1], STDOUT_FILENO);
    //Ejecutamos el programa tam_quijote
    execlp("find","find", "/bin", "-type", "f", "-name", "???", "-print0", NULL);
    //Cierro el cauce al completo por el otro extremo
    close(info[1]);
  }else{
    //Cuando un hijo acaba lo matamos para que no quede zombie
    signal(SIGCHLD, signalManagement);
    //Cerramos el cauce para escritura
    close(info[1]);
    //Leemos del cauce los valores cada 9bytes es una ruta
    while((bytesLeidos = read(info[0], rutabin, 9)) > 0){
      //Calculo el stat de la ruta y saco por pantalla la ruta y su nº de inodo
      if(stat(rutabin, &atributos) >= 0){
        //Guardamos el numero de inodo actual en una variable global para que la use NFTW
        inodoActual = atributos.st_ino;
        //Imprimo la ruta leida del cauce y su numero de inodo
        //printf("%s %lu\n", rutabin, atributos.st_ino);

        //Comprobamos si tiene enlaces duros recorriendo el directorio del usuario a un nivel
        if(nftw(nombrehome, busquedaDirectorio, 10, 0) != 0){
          perror("ntfw");
        }
      }

      const char* pathruta = rutabin;

      //Compruebo que tipo de ejecución de hijos se ha elegido: p=paralela o s=serie
      if(strcmp(opcion, "p")==0){
        if((pid = fork()) < 0){
          perror("\nError en el primer fork");
          exit(EXIT_FAILURE);
        }else if(pid==0){
          //printf("EJECUTO %s PID:%d PID PADRE:%d\n", pathruta, getpid(), getppid());
          //srand ( time(NULL) );
          //int num = rand()%10;
          //sleep(num);
          //printf("EJECUTO %s PID:%d PID PADRE:%d CON RETRASO: %d\n", pathruta, getpid(), getppid(), num);

          //Genero el nombre del fichero
          char *nombreorden, rutassalida[PATH_MAX];
          nombreorden=malloc(NAME_MAX);
          nombreorden=basename(rutabin);
          sprintf(rutassalida, "%s.sal", nombreorden);

          //Creo un fichero con el nombre anteriormente generado
          if( (fd=open(rutassalida,O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR))<0) {
            printf("\nError %d en open",errno);
            perror("\nError en open");
            exit(EXIT_FAILURE);
          }

          //Cambio la salida estandar por la del fichero
          dup2(fd, STDOUT_FILENO);

          //Ejecuto la orden
          execl(pathruta, pathruta, "--version", NULL);
          exit(0);
        }
      }else{
        //Esperamos a que un hijo anterior acabe antes de crear otro
        pid = wait(NULL);
        if((pid = fork()) < 0){
          perror("\nError en el primer fork");
          exit(EXIT_FAILURE);
        }else if(pid==0){
          //printf("EJECUTO %s PID:%d PID PADRE:%d\n", pathruta, getpid(), getppid());
          //srand ( time(NULL) );
          //int num = rand()%10;
          //sleep(num);
          //printf("EJECUTO %s PID:%d PID PADRE:%d CON RETRASO: %d\n", pathruta, getpid(), getppid(), num);

          //Ejecuto la orden
          execl(pathruta, pathruta, "--version", NULL);
          exit(0);
        }
      }
    }
    //Cerramos finalmente el cauce al completo, la lectura en este caso
    close(info[0]);
  }
}
