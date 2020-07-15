1.[3pts] Implementa un programa en C llamado contar que tiene la siguiente sintaxis:
	contar <archivo_salida> <directorio>
donde :

a) Ambos argumentos son obligatorios: el primer argumento debe ser el nombre de un
archivo regular que puede o no existir y el segundo debe ser el nombre de un directorio existente. Realiza el control de errores adecuado.

b)La orden debe escribir en archivo_salida el nombre y tamaño en bloques de todos
los archivos de tipo directorio del directorio dado como argumento que , ademas
tengan permiso de ejecución para grupo. También va sumando los bloques
ocupados por todos los subdirectorios que cumplen la condicion dada.

c)archivo_salida debe crearse en el diretorio actual si no existe. Si existiera, se sustituirá su contenido por el que genera este programa.

d)Ademas, y justo antes de terminar, debe imprimir por la salida estandar la suma total
de los bloques ocupados por todos los archivos que cumplían las condiciones dadas en b). Imprime solo un numero.

=======================================================================================
2.[7 pts] Implementa un progrma en C llamado maestro que tenga como argumentos
nombres de directorios (d1,d2 ... dn)y que realiza las siguientes acciones:

a)Por cada argumento (al menos debe haber uno), crea un proceso hijo que se encargará
de ejecutar el programa contar.

b) Cada hijo usará como argumento del programa contar que va a ejecutar el nombre del
directorio por el cual se creo y el nombre de un archivo que se llamra <pid del hijo>.Directorios.

c)El proceso padre crea un unico archivo de tipo cauce (con o sin nombre) que le
comunicará con sus procesos hijos. De este cauce leerá números que recibira de sus
hijos (que habran cambiado su salida estandar por la escritura en dicho cauce).
El padre, ademas, ira sumando los numeros leidos.

d)Cuando todos los procesos hijos finalicen, el proceso padre imprimira en pantalla el siguiente mensaje "la suma de los bloques de todos
los archivos de tipo directorio de todos los directorios dados como argumentos es  <numero>" y finalizará.
Los procesos hijos no deben quedar zombies.
