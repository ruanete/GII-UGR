#!/bin/csh

@ inicio = 2
@ fin = 26
@ incremento = 2
@ i = $inicio

echo > BranchAndBound.dat

while ( $i <= $fin )
  echo Ejecución tam = $i
  echo  "      Branch And Bound"
  echo `./bin/BranchAndBound $i ` >> BranchAndBound.dat

@ i+= $incremento
end
