/**
   @file Ordenación por selección
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
/*  Método de ordenación por selección  */

/**
   @brief Ordena un vector por el método de selección.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de selección.
*/
inline static void seleccion(int T[], int num_elem);

/**
   @brief Ordena parte de un vector por el método de selección.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
                   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de selección.
*/
static void seleccion_lims(int T[], int inicial, int final);

/**
   Implementación de las funciones
**/

void seleccion(int T[], int num_elem) { seleccion_lims(T, 0, num_elem); }

static void seleccion_lims(int T[], int inicial, int final) {
  int i, j, indice_menor;
  int menor, aux;
  for (i = inicial; i < final - 1; i++) {
    indice_menor = i;
    menor = T[i];
    for (j = i; j < final; j++)
      if (T[j] < menor) {
        indice_menor = j;
        menor = T[j];
      }
    aux = T[i];
    T[i] = T[indice_menor];
    T[indice_menor] = aux;
  };
}

int main(int argc, char *argv[]) {

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

  const int TAM_GRANDE = 2000;
  const int NUM_VECES = 100;

  double tiempo = 0.0f;

  for (int i = 0; i < iteraciones; ++i) {

    int *copy = new int[n];
    std::copy(T, T + n, copy);

    assert(copy);

    auto t1 = high_resolution_clock::now();
    seleccion(copy, n);
    auto t2 = high_resolution_clock::now();

    tiempo += duration_cast<duration<double>>(t2 - t1).count();

    delete[] copy;
  }

  tiempo /= iteraciones;

  cout << n << " " << tiempo << endl;

  delete[] T;

  return 0;
};
