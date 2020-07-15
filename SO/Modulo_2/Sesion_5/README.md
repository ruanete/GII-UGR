# Sesión 5
### Ejercicio 1: Compila y ejecuta los siguientes programas y trata de entender su funcionamiento.

Lo que realizan dichos programas son uno la recepción de señales que son enviadas por uno de ellos, las señales que recibe las trata y las maneja,
para ello si recibe un 0, envía la señal de matar el proceso con el PID que se le pase, en este caso el del otro programa, si se le pasa un 1 o un 2 se escribe un mensaje en el programa recibeSeñal cuando este esta siendo ejecutado en segundo plano, el mensaje no es más que ha recibido la señal 1 o la señal 2.

### Ejercicio 2: Escribe un programa en C llamado contador, tal que cada vez que reciba una señal que se pueda manejar, muestre por pantalla la señal y el número de veces que se ha recibido ese tipo de señal, y un mensaje inicial indicando las señales que no puede manejar. En el cuadro siguiente se muestra un ejemplo de ejecución del programa.

```
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

static int senalesRecibidas[10];

static void sig_USR_hdlr(int sigNum){
  if(sigNum>=0 && sigNum<10){
    senalesRecibidas[sigNum]++;
    printf("La senal %d se ha recibido %d veces", sigNum, senalesRecibidas[sigNum]);
  }else{
    printf("No puedo manejar la senal %d", sigNum);
  }
}

int main(int argc, char *argv[]) {
  struct sigaction sig_USR_nact;
  if(setvbuf(stdout,NULL,_IONBF,0)) {
    perror("\nError en setvbuf");
  }

  sig_USR_nact.sa_handler= sig_USR_hdlr;

  sigemptyset (&sig_USR_nact.sa_mask);
  sig_USR_nact.sa_flags = 0;

  for(int i=1;i<10-1;i++){
    if (sigaction(i, &sig_USR_nact, NULL) < 0) {
			perror("Error al intentar establecer el manejador de senal\n");
			exit(-1);
		}
  }

  while(true);
}
```

### Ejercicio 3: Escribe un programa que suspenda la ejecución del proceso actual hasta que se reciba la señal SIGUSR1. Consulta en el manual en línea sigemptyset para conocer las distintas operaciones que permiten configurar el conjunto de señales de un proceso.

```
#include <stdio.h>
#include <signal.h>

int main(){
  sigset_t new_mask;

  /* inicializar la nueva mascara de se�ales */
  sigemptyset(&new_mask);

  sigdelset(&new_mask, SIGUSR1);

  /*esperar a cualquier se�al excepto SIGUSR1 */
  sigsuspend(&new_mask);
}
```

### Ejercicio 4: Compila y ejecuta el siguiente programa y trata de entender su funcionamiento.

Se genera un manejador de señales y se inicializa dicho manejador a 0. Seguidamente se genera un conjunto de mascaras vacias a la que se añade SIGTERM y bloquea la señal, se hace una pausa de 10 segundos, se restaura la señal y se espera a recibir las señales que estaban en espera en dicho manejador cambiando su valor de signal_recibida a 1.
