#!/bin/csh
@ inicio = 10
@ fin = 1000
@ incremento = 20
@ i = $inicio


echo > Voraz.dat


while ( $i <= $fin )
  echo Ejecución tam = $i
  echo  "     Voraz"
  echo `./bin/Voraz $i ` >> Voraz.dat

@ i+= $incremento
end
