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
    ./$1 $c $5 >> $1.dat
  done
}

for I in "burbuja" "heapsort" "insercion" "quicksort" "mergesort" "seleccion"
do
  echo "Calculando los tiempos del algoritmo: $I"
  generateData $I 1000 25000 1000 10
done

echo "Calculando los tiempos del algoritmo: hanoi"
generateData hanoi 10 35 1 10

echo "Calculando los tiempos del algoritmo: floyd"
generateData floyd 100 2500 100 10

for D in "burbuja" "heapsort" "insercion" "quicksort" "mergesort" "seleccion" "hanoi" "floyd"
do
  echo "Generando gráfico de: $D"
  gnuplot <<< "\
  		set terminal svg; \
  		set output '$D.svg'; \
      set xlabel 'Tamaño'; \
      set ylabel 'Tiempo (seg)'; \
      plot '$D.dat' title 'Eficiencia de $D' with points"
done
