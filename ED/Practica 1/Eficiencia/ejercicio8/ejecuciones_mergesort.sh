#!/bin/bash
inicio=100
fin=100000
incremento=500
ejecutable="mergesort"
salida="tiempos_mergesort.dat"

i=$inicio
echo > $salida
while [ $i -lt $fin ]
do
  echo "Ejecución tam = " $i
  echo `./$ejecutable $i` >> $salida
  i=$[$i+$incremento]
done
