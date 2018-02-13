/**
   @file Ordenación por montones
*/

#include <iostream>
#include <chrono>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

/* ************************************************************ */
/*  Método de ordenación por montones  */

/**
   @brief Ordena un vector por el método de montones.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de ordenación por montones.
*/
inline static void heapsort(int T[], int num_elem);

/**
   @brief Reajusta parte de un vector para que sea un montón.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.
   @param k: índice del elemento que se toma com raíz

   Reajusta los elementos entre las posiciones k y num_elem - 1
   de T para que cumpla la propiedad de un montón (APO),
   considerando al elemento en la posición k como la raíz.
*/
static void reajustar(int T[], int num_elem, int k);

/**
   Implementación de las funciones
**/

static void heapsort(int T[], int num_elem) {
  int i;
  for (i = num_elem / 2; i >= 0; i--)
    reajustar(T, num_elem, i);
  for (i = num_elem - 1; i >= 1; i--) {
    int aux = T[0];
    T[0] = T[i];
    T[i] = aux;
    reajustar(T, i, 0);
  }
}

static void reajustar(int T[], int num_elem, int k) {
  int j;
  int v;
  v = T[k];
  bool esAPO = false;
  while ((k < num_elem / 2) && !esAPO) {
    j = k + k + 1;
    if ((j < (num_elem - 1)) && (T[j] < T[j + 1]))
      j++;
    if (v >= T[j])
      esAPO = true;
    T[k] = T[j];
    k = j;
  }
  T[k] = v;
}

int main(int argc, char **argv) {
  // Comprobar que el número de argumentos sea dos.
  /*
  * El primero debe de ser el número de datos que debe contener el vector y
  * deben ser ordenados y el segundo es él número de veces que se va a realizar
  * la ordenación con distintos vectores para hacer la media de tiempos.
  */
  if (argc != 3) {
    cerr << "El programa necesita dos argumentos." << endl
         << "Uso: " << argv[0] << " <número de datos> <número de repeticiones>"
         << endl;

    return (-1);
  }

  int n = std::stoi(argv[1]);
  int iteraciones = std::stoi(argv[2]);

  // comprobar si el tamaño del array es correcto
  if (n < 2) {
    cerr << "ERROR: el tamaño del array de datos es demasiado pequeño, "
         << "un array tiene que tener como mínimo dos componentes." << endl;

    return (-2);
  }

  // comprobar si el número de iteraciones es correcto.
  if (iteraciones < 1) {
    cerr << "ERROR: El número de iteraciones debe igual o mayor que 1." << endl;

    return (-3);
  }

  int *T = new int[n];
  assert(T);

  srandom(time(0));

  for (int i = 0; i < n; i++) {
    T[i] = random();
  };

  double tiempo = 0.0f;

  for (int i = 0; i < iteraciones; ++i) {

    int *copy = new int[n];
    std::copy(T, T + n, copy);

    assert(copy);

    auto t1 = high_resolution_clock::now();
    heapsort(copy, n);
    auto t2 = high_resolution_clock::now();

    tiempo += duration_cast<duration<double>>(t2 - t1).count();

    delete[] copy;
  }

  tiempo /= iteraciones;

  cout << n << " " << tiempo << endl;

  delete[] T;

  return 0;
};
