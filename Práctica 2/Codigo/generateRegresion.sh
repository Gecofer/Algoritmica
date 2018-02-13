#!/bin/bash
# http://computingnote.blogspot.com.es/2013/04/calculating-r2-with-gnuplot.html

#Argumentos
# $1 nombre del fichero
# $2 formula con la que ejecutas la regresion
# $3 variables de la regresion
function createGraphAndData() {
  echo "Generando gráfico de: $1"
  gnuplot <<< "\
  		set terminal png; \
  		set output 'grafico_$1.png'; \
      set xlabel 'Tamaño'; \
      set ylabel 'Tiempo (seg)'; \
      mean(x)= m; \
      fit mean(x) '$1.dat' using 1:2 via m; \
      SST = FIT_WSSR/(FIT_NDF+1); \
      f(x) = $2; \
      fit f(x) '$1.dat' using 1:2 via $3; \
      SSE=FIT_WSSR/(FIT_NDF); \
      SSR=SST-SSE; \
      R2=SSR/SST; \
      set title '$1'; \
      set key left Left; \
      set title sprintf('R^2=%f', R2); \
      plot '$1.dat' title 'Eficiencia de $1', f(x) title 'Curva ajustada'" \
      2> regresion_$1.txt
}

# variables de las formulas.
cuadrada="a0*x*x+a1*x+a2";
logaritmica="a0*x*log10(x)";
cubica="a0*x*x*x+a1*x*x+a2*x+a3";
exponencial="a0*2**x+a1";

# variables de la regresion por formula
v_cuadrada="a0,a1,a2";
v_logaritmica="a0";
v_cubica="a0,a1,a2,a3";
v_exponencial="a0,a1";

createGraphAndData "repetidos_sencillo" $cuadrada $v_cuadrada

createGraphAndData "repetidos_divide" $logaritmica $v_logaritmica
