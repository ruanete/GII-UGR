# Sesión 4
### Ejercicio 1: Consulte en el manual las llamadas al sistema para la creación de archivos especiales en general (mknod) y la específica para archivos FIFO (mkfifo). Pruebe a ejecutar el siguiente código correspondiente a dos programas que modelan el problema del productor/consumidor, los cuales utilizan como mecanismo de comunicación un cauce FIFO. Determine en qué orden y manera se han de ejecutar los dos programas para su correcto funcionamiento y cómo queda reflejado en el sistema que estamos utilizando un cauce FIFO. Justifique la respuesta.

Para realizar el uso del productor y el consumidor primero hay que ejecutar el consumidor que es el que esperará a recibir datos del productor y luego hay que ejecutar el productor pasandole como parámetro el mensaje que será enviado por el cauce al consumidor que lo sacará por pantalla. En el sistema se puede ver que se ha generado un fichero ComunicaciónFIFO que es el cauce generado con la llamada correspondiente.
***

### Ejercicio 2: Consulte en el manual en línea la llamada al sistema pipe para la creación de cauces sin nombre. Pruebe a ejecutar el siguiente programa que utiliza un cauce sin nombre y describa la función que realiza. Justifique la respuesta.

Basicamente pipe genera un descriptor de archivo para lectura y escritura, lo que se realiza en el programa es crear un hijo y se cierra el descriptor de archivo la lectura y se empieza a escribir el mensaje en el cauce cuando se acaba el padre se encarga de leer el cauce cerrando la escritura del mismo. Finalmente lo que se devuelve es el numero de bytes transmitidos así como la cadena que se ha transmitido por el pipe.

***

### Ejercicio 3: Redirigiendo las entradas y salidas estándares de los procesos a los cauces podemos escribir un programa en lenguaje C que permita comunicar órdenes existentes sin necesidad de reprogramarlas, tal como hace el shell (por ejemplo ls | sort). En particular, ejecute el siguiente programa que ilustra la comunicación entre proceso padre e hijo a través de un cauce sin nombre redirigiendo la entrada estándar y la salida estándar del padre y el hijo respectivamente.

Lo que realiza es crear un hijo y en el pipe que se crea se inserta la información obtenida y cuando termina y el padre coge la información para luego usarla con sort y ordenarla.

***

### Ejercicio 4: Compare el siguiente programa con el anterior y ejecútelo. Describa la principal diferencia, si existe, tanto en su código como en el resultado de la ejecución.

No hay diferencia en la salida, la única diferencia es que uno usa dup y otro dup2, la diferencia entre ambos es que uno puedes especificar donde copiar el descriptor y el otro usa el por defecto.

***

### Ejercicio 5: Este ejercicio se basa en la idea de utilizar varios procesos para realizar partes de una computación en paralelo. Para ello, deberá construir un programa que siga el esquema de computación maestro-esclavo, en el cual existen varios procesos trabajadores (esclavos) idénticos y un único proceso que reparte trabajo y reúne resultados (maestro). Cada esclavo es capaz de realizar una computación que le asigne el maestro y enviar a este último los resultados para que sean mostrados en pantalla por el maestro. El ejercicio concreto a programar consistirá en el cálculo de los números primos que hay en un intervalo. Será necesario construir dos programas, maestro y esclavo. Ten en cuenta la siguiente especificación:
### 1. El intervalo de números naturales donde calcular los número primos se pasará como argumento al programa maestro. El maestro creará dos procesos esclavos y dividirá el intervalo en dos subintervalos de igual tamaño pasando cada subintervalo como argumento a cada programa esclavo. Por ejemplo, si al maestro le proporcionamos el intervalo entre 1000 y 2000, entonces un esclavo debe calcular y devolver los números primos comprendidos en el subintervalo entre 1000 y 1500, y el otro esclavo entre 1501 y 2000. El maestro creará dos cauces sin nombre y se encargará de su redirección para comunicarse con los procesos esclavos. El maestro irá recibiendo y mostrando en pantalla (también uno a uno) los números primos calculados por los esclavos en orden creciente.

### 2. El programa esclavo tiene como argumentos el extremo inferior y superior del intervalo sobre el que buscará números primos. Para identificar un número primo utiliza el siguiente método concreto: un número n es primo si no es divisible por ningún k tal que 2 < k <= sqrt(n), donde sqrt corresponde a la función de cálculo de la raíz cuadrada (consulte dicha función en el manual). El esclavo envía al maestro cada primo encontrado como un dato entero (4 bytes) que escribe en la salida estándar, la cuál se tiene que encontrar redireccionada a un cauce sin nombre. Los dos cauces sin nombre necesarios, cada uno para comunicar cada esclavo con el maestro, los creará el maestro inicialmente. Una vez que un esclavo haya calculado y enviado (uno a uno) al maestro todos los primos en su correspondiente intervalo terminará.

***

```
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
```

```
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
```
