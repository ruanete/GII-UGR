# Sesión 3
### Ejercicio 1: Implementa un programa en C que tenga como argumento un número entero. Este programa debe crear un proceso hijo que se encargará de comprobar si dicho número es un número par o impar e informará al usuario con un mensaje que se enviará por la salida estándar. A su vez, el proceso padre comprobará si dicho número es divisible por 4, e informará si lo es o no usando igualmente la salida estándar.
***
```
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
```

### Ejercicio 2: ¿Qué hace el siguiente programa? Intenta entender lo que ocurre con las variables y sobre todo con los mensajes por pantalla cuando el núcleo tiene activado/desactivado el mecanismo de buffering.

```
//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int global=6;
char buf[]="cualquier mensaje de salida\n";

int main(int argc, char *argv[])
{
int var;
pid_t pid;

var=88;
if(write(STDOUT_FILENO,buf,sizeof(buf)+1) != sizeof(buf)+1) {
	perror("\nError en write");
	exit(EXIT_FAILURE);
}
//(1)if(setvbuf(stdout,NULL,_IONBF,0)) {
//	perror("\nError en setvbuf");
//}
//Se ejecuta este mensaje debido a que antes del fork se llenó el buffer y
//al no vaciarlo y crear un hijo el buffer sigue lleno pues se imprime.
//Al descomentar el if anterior lo que hacemos el vaciar el buffer.
printf("\nMensaje previo a la ejecución de fork");

if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(EXIT_FAILURE);
}
else if(pid==0) {
	//proceso hijo ejecutando el programa
	global++;
	var++;
} else  //proceso padre ejecutando el programa
	sleep(1);
printf("\npid= %d, global= %d, var= %d\n", getpid(),global,var);
exit(EXIT_SUCCESS);
}
```

### Ejercicio 3: Indica qué tipo de jerarquías de procesos se generan mediante la ejecución de cada uno de los siguientes fragmentos de código. Comprueba tu solución implementando un código para generar 20 procesos en cada caso, en donde cada proceso imprima su PID y el del padre, PPID.

```
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int nprocs = 20;
  pid_t childpid;

  //Jerarquía de procesos tipo 1
  //El hijo generado con el fork es el padre siempre del siguiente proceso creado.
  /*for (int i=1; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }

    printf("\nProceso con PID %d y mi padre con PID %d\n", getpid(), getppid());

    if (childpid)
      break;
  }*/

  //Jerarquía de procesos tipo 2
  //En cuanto se crea un nuevo proceso se finaliza al momento con el break.
  for (int i=1; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }

    printf("\nProceso con PID %d y mi padre con PID %d\n", getpid(), getppid());

    if (!childpid)
      break;
  }
}
```

### Ejercicio 4: Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se identificará en la salida estándar, mostrando un mensaje del tipo Soy el hijo PID. El proceso padre simplemente tendrá que esperar la finalización de todos sus hijos y cada vez que detecte la finalización de uno de sus hijos escribirá en la salida estándar un mensaje del tipo:
```
Acaba de finalizar mi hijo con <PID>
Sólo me quedan <NUM_HIJOS> hijos vivos
```

```
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int nprocs = 5, estado;
  pid_t pid;

  for (int i=0; i < nprocs; i++) {
    if((pid = fork())<0){
      perror("Error en fork\n");
      exit(-1);
    }

    if(pid==0){
      printf("Soy el hijo %d\n", getpid());
      exit(0);
    }
  }

  for(int i=4; i>=0; i--){
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con %d\n", pid);
    printf("Solo me quedan %i hijos vivos\n", i);
  }
}
```

### Ejercicio 5: Implementa una modificación sobre el anterior programa en la que el proceso padre espera primero a los hijos creados en orden impar (1º,3º,5º) y después a los hijos pares (2º y 4º).

```
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int nprocs = 5, estado;
  pid_t pid;
  int pids[5];

  for (int i=1; i <= nprocs; i++) {
    if((pids[i] = fork())<0){
      perror("Error en fork\n");
      exit(-1);
    }

    if(pids[i]==0){
      printf("Soy el hijo %d\n", getpid());
      exit(0);
    }
  }

  for(int i=nprocs; i>=0; i-=2){
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con %d\n", pids[i]);
    printf("Solo me quedan %i hijos vivos\n", i);
  }

  for(int i=nprocs-1; i>0; i-=2){
    pid = wait(&estado);
    printf("Acaba de finalizar mi hijo con %d\n", pids[i]);
    printf("Solo me quedan %i hijos vivos\n", i);
  }
}
```
### Ejercicio 6: ¿Qué hace el siguiente programa?
```
//tarea5.c
//Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

/*
	Lo que realiza el programa es ejecutar la orden ldd ./tarea5 usando un proceso hijo,
	cuando el proceso hijo termina se devuelve el PID del hijo junto con el estado que le
	ha devuelto el wait, se usa estado >> 8 por que se necesita saber que valor tiene el
	tiene el byte menos significativo para saber si se ha finalizado el hijo o no.
*/

int main(int argc, char *argv[])
{
pid_t pid;
int estado;

if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(EXIT_FAILURE);
}
else if(pid==0) {  //proceso hijo ejecutando el programa
	if( (execl("/usr/bin/ldd","ldd","./tarea5")<0)) {
		perror("\nError en el execl");
		exit(EXIT_FAILURE);
	}
}
wait(&estado);
/*
<estado> mantiene información codificada a nivel de bit sobre el motivo de finalización del proceso hijo
que puede ser el número de señal o 0 si alcanzó su finalización normalmente.
Mediante la variable estado de wait(), el proceso padre recupera el valor especificado por el proceso hijo como argumento de la llamada exit(), pero desplazado 1 byte porque el sistema incluye en el byte menos significativo
el código de la señal que puede estar asociada a la terminación del hijo. Por eso se utiliza estado>>8
de forma que obtenemos el valor del argumento del exit() del hijo.
*/

printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado>>8);

exit(EXIT_SUCCESS);

}
```

### Ejercicio 7: Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene, y opcionalmente la cadena “bg”. Nuesto programa deberá ejecutar el programa pasado como primer argumento en foreground si no se especifica la cadena “bg” y en background en caso contrario. Si el programa tiene argumentos hay que ejecutarlo con éstos.

```
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

      printf("ORDEN: %s\n", orden);
      for(int i=0;i<=j;i++){
        printf("%s\n", parametros[i]);
      }
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
```
