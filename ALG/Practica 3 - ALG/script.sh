#!/bin/csh
@ inicio = 1
@ fin = 10000
@ incremento = 10
@ i = $inicio


echo > ./datos_obtenidos/voraz_maximo.dat


while ( $i <= $fin )
  echo Ejecución tam = $i
  echo `./bin/Voraz_maximo ./datos/numeros2.txt $i ` >> ./datos_obtenidos/voraz_maximo.dat

@ i+= $incremento
end
