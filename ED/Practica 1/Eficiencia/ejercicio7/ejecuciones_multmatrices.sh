#!/bin/bash
inicio=100
fin=2000
incremento=100
ejecutable="multmatrices"
salida="tiempos_multmatrices.dat"

i=$inicio
echo > $salida
while [ $i -lt $fin ]
do
  echo "Ejecución tam = " $i
  echo `./$ejecutable $i 100` >> $salida
  i=$[$i+$incremento]
done
