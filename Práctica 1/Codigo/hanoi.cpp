/**
   @file Resolución del problema de las Torres de Hanoi
*/

#include <ctime>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: número de discos. M > 1.
   @param i: número de columna en que están los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: námero de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta función imprime en la salida estándar la secuencia de
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restricción de que ningún
   disco se puede situar sobre otro de tamaño menor. Utiliza
   una única columna auxiliar.
*/
void hanoi(int M, int i, int j);

void hanoi(int M, int i, int j) {
  if (M > 0) {
    hanoi(M - 1, i, 6 - i - j);
    //cout << i << " -> " << j << endl;
    hanoi(M - 1, 6 - i - j, j);
  }
}

int main(int argc, char **argv) {

  // Comprobar que el número de argumentos sea dos.
  /*
  * El primero debe de ser el número de discos y el segundo el número de repeticiones
  */
  if (argc != 3) {
    cerr << "El programa necesita dos argumentos." << endl
         << "Uso: " << argv[0] << " <número de discos> <número de repeticiones>"
         << endl;

    return (-1);
  }

  int M = std::stoi(argv[1]);
  int iteraciones = std::stoi(argv[2]);

  // comprobar si el tamaño del array es correcto
  if (M < 0) {
    cerr << "ERROR: el número de discos es demasiado pequeño, "
         << "debe ser como mínimo 1." << endl;

    return (-2);
  }

  // comprobar si el número de iteraciones es correcto.
  if (iteraciones < 1) {
    cerr << "ERROR: El número de iteraciones debe igual o mayor que 1." << endl;

    return (-3);
  }

  double tiempo = 0.0f;
  for (int i = 0; i < iteraciones; ++i) {
    auto t1 = high_resolution_clock::now();
    hanoi(M, 1, 2);
    auto t2 = high_resolution_clock::now();

    tiempo += duration_cast<duration<double>>(t2 - t1).count();
  }

  tiempo /= iteraciones;

  cout << M << " " << tiempo << endl;


  return 0;
}
