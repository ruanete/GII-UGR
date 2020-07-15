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
  int bytesLeidos=0,
  valorMaximo=-9999,
  valorMinimo=9999,
  menoresCincoAnios=0,
  totalPersonas=0,
  sumaEdad=0,
  mediaEdad=0;
  int fd[2];
  pid_t pid;
  char n;
  char edad[10]="";
  char mensaje_final[100];
  int fdFichero;

  pipe(fd);

  if((pid = fork()) < 0){
    perror("\nError en el primer fork");
    exit(EXIT_FAILURE);
  }else if(pid==0){
    //Cerramos el cauce para lectura
    close(fd[0]);
    //Cambiamos la salida estandar por el cauce
    dup2(fd[1], STDOUT_FILENO);
    //Ejecutamos el programa tam_quijote
    execlp("cut","cut", "-d", ";", "-f", "6", "titanic.csv", NULL);
    //Cierro el cauce al completo por el otro extremo
    close(fd[1]);
  }else{
    //Cierro el cauce para escritura
    close(fd[1]);

    while((bytesLeidos = read(fd[0], &n, sizeof(char))) > 0){
      if(n!='\n'){
        sprintf(edad + strlen(edad), "%c", n);
      }else{
        //Convertimos el valor a entero
        int numero_entero = atoi(edad);

        //Aumento en uno el numero de personas
        totalPersonas++;
        //Sumo el valor a la suma de edades para realizar la media
        sumaEdad = sumaEdad + numero_entero;

        //Si el valor es mayor que el actual maximo actualizamos
        if(numero_entero > valorMaximo)
          valorMaximo = numero_entero;

        //Si el valor es menor que el actual minimo actualizamos
        if(numero_entero < valorMinimo)
          valorMinimo = numero_entero;

        //Si el valor es menor que 5 aumentamos el numero de menores de 5 años
        if(numero_entero < 5)
          menoresCincoAnios++;

        sprintf(edad, "");
      }
    }

    //Cerramos el cauce para lectura
    close(fd[0]);

    //Calculamos la media total
    mediaEdad = sumaEdad / totalPersonas;

    sprintf(mensaje_final, "Total personas: %d\nMedia edad: %d\nMás joven: %d\nMás viejo: %d\nMenores de 5 años: %d\n", totalPersonas, mediaEdad, valorMinimo, valorMaximo, menoresCincoAnios);

    //Abro el fichero para poder escribir en el
    if( (fdFichero=open("resultado_titanic.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR))<0) {
      printf("\nError %d en open",errno);
      perror("\nError en open");
      exit(EXIT_FAILURE);
    }

    write(fdFichero, mensaje_final, strlen(mensaje_final));
  }
}
