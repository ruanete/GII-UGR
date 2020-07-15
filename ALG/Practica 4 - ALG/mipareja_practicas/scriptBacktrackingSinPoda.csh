#!/bin/csh

@ inicio = 1
@ fin = 13
@ incremento = 1
@ i = $inicio

echo > BacktrackingBasico.dat

while ( $i <= $fin )
  echo Ejecución tam = $i
  echo  "      Backtracking Basico"
  echo `./bin/BacktrackingBasico $i ` >> BacktrackingBasico.dat

@ i+= $incremento
end
