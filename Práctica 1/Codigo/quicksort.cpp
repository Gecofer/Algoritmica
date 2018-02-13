/**
   @file Ordenación rápida (quicksort).
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
/*  Método de ordenación rápida  */

/**
   @brief Ordena un vector por el método quicksort.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo quicksort.
*/
inline static void quicksort(int T[], int num_elem);

/**
   @brief Ordena parte de un vector por el método quicksort.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
                   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo quicksort.
*/
static void quicksort_lims(int T[], int inicial, int final);

/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static void insercion(int T[], int num_elem);

/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
                   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserción.
*/
static void insercion_lims(int T[], int inicial, int final);

/**
   @brief Redistribuye los elementos de un vector según un pivote.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
                   inicial < final.
   @param pp: Posición del pivote. Es MODIFICADO.

   Selecciona un pivote los elementos de T situados en las posiciones
   entre inicial y final - 1. Redistribuye los elementos, situando los
   menores que el pivote a su izquierda, después los iguales y a la
   derecha los mayores. La posición del pivote se devuelve en pp.
*/
static void dividir_qs(int T[], int inicial, int final, int &pp);

/**
   Implementación de las funciones
**/

inline static void insercion(int T[], int num_elem) {
  insercion_lims(T, 0, num_elem);
}

static void insercion_lims(int T[], int inicial, int final) {
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j - 1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j - 1];
      T[j - 1] = aux;
      j--;
    };
  };
}

const int UMBRAL_QS = 50;

inline void quicksort(int T[], int num_elem) { quicksort_lims(T, 0, num_elem); }

static void quicksort_lims(int T[], int inicial, int final) {
  int k;
  if (final - inicial < UMBRAL_QS) {
    insercion_lims(T, inicial, final);
  } else {
    dividir_qs(T, inicial, final, k);
    quicksort_lims(T, inicial, k);
    quicksort_lims(T, k + 1, final);
  };
}

static void dividir_qs(int T[], int inicial, int final, int &pp) {
  int pivote, aux;
  int k, l;

  pivote = T[inicial];
  k = inicial;
  l = final;
  do {
    k++;
  } while ((T[k] <= pivote) && (k < final - 1));
  do {
    l--;
  } while (T[l] > pivote);
  while (k < l) {
    aux = T[k];
    T[k] = T[l];
    T[l] = aux;
    do
      k++;
    while (T[k] <= pivote);
    do
      l--;
    while (T[l] > pivote);
  };
  aux = T[inicial];
  T[inicial] = T[l];
  T[l] = aux;
  pp = l;
};

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
    quicksort(copy, n);
    auto t2 = high_resolution_clock::now();

    tiempo += duration_cast<duration<double>>(t2 - t1).count();

    delete[] copy;
  }

  tiempo /= iteraciones;

  cout << n << " " << tiempo << endl;

  delete[] T;

  return 0;
};
