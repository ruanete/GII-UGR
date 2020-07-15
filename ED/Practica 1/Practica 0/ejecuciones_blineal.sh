#!/bin/bash
inicio=100
fin=1000000
incremento=100
ejecutable="busqueda_lineal"
salida="tiempos_busqueda.dat"
 
i=$inicio
echo > $salida
while [ $i -lt $fin ] 
do
  echo "Ejecución tam = " $i
  echo `./$ejecutable $i 10000` >> $salida
  i=$[$i+$incremento]
done
