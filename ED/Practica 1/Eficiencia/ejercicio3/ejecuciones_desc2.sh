#!/bin/bash
inicio=100
fin=30000
incremento=500
ejecutable="ejercicio_desc2"
salida="tiempos_desc2.dat"

i=$inicio
echo > $salida
while [ $i -lt $fin ]
do
  echo "Ejecución tam = " $i
  echo `./$ejecutable $i` >> $salida
  i=$[$i+$incremento]
done
