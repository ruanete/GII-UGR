# Ejercicio de cauces 1
Crea un programa en C de tal forma que realice el siguiente cauce linux: ls -l | tail -N, donde N será un número entero que se le pasa como entrada a dicho programa. El comando ls -l lista los ficheros/directorios y sus permisos del directorio actual; y tail -N muestra las últimas N líneas de una entrada. Como sabéis, el carácter barra vertical «|» realiza un pipe (cauce).

TIP: sprintf() o concat() concatena strings: https://stackoverflow.com/questions/308695/how-do-i-concatenate-const-literal-strings-in-c

1) Por lo que, nuestro programa, finalmente deberá imprimir por la consola los últimos N ficheros/directorios con sus permisos como esta salida:

-rwxr-xr-x@  1 garmo  staff   9056 Nov  7 00:04 productorFIFO

-rw-r--r--@  1 garmo  staff  29389 Nov  7 12:59 sesion4.cbp

-rwxr-xr-x@  1 garmo  staff   9292 Nov  7 00:23 tarea6

2) Tarea adicional: mostrar sólo los permisos (quizás tengas que crear más procesos hijos) de esos N ficheros como sigue:

-rwxr-xr-x

-rw-r--r--

-rwxr-xr-x
