#!/bin/csh
@ inicio = 100
@ fin = 15000
@ incremento = 100
@ i = $inicio
echo > tiemposmaxminmatriz.dat
while ( $i <= $fin )
 echo Ejecución tam = $i
 echo `./maxminmatriz $i 9` >> tiemposmaxminmatriz.dat
 @ i += $incremento
end
