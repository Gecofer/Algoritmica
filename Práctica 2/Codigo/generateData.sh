#!/bin/bash

# Argumentos
# $1 nombre del programa a ejecutar
# $2 tamaño de datos inicial
# $3 tamaño de datos de la ultima iteracion
# $4 incremento entre cada iteracion
# $5 número de veces que el programa repetirá el calculo para sacar la media
function generateData() {
  echo "" > $1.dat

  for ((c = $2; c <= $3; c += $4)); do
    echo "Calculo con $c datos y $5 iteraciones."
    ./$1 $c $5 >> $1.dat
  done
}

echo "Calculando los tiempos del algoritmo: eliminar sencillo"
generateData repetidos_sencillo 10000 250000 10000 15

echo "Calculando los tiempos del algoritmo: eliminar divide y venceras"
generateData repetidos_divide 10000 250000 10000 30
