#!/bin/csh

@ inicio = 1
@ fin = 14
@ incremento = 1
@ i = $inicio

echo > BacktrackingPoda.dat

while ( $i <= $fin )
  echo Ejecución tam = $i
  echo  "      Backtracking Poda"
  echo `./bin/BacktrackingPoda $i ` >> BacktrackingPoda.dat

@ i+= $incremento
end
