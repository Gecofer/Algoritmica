/**
   @file Ordenación por mezcla
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
/*  Método de ordenación por mezcla  */

/**
   @brief Ordena un vector por el método de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static void mergesort(int T[], int num_elem);

/**
   @brief Ordena parte de un vector por el método de mezcla.

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
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(int T[], int inicial, int final);

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
   Aplica el algoritmo de la inserción.
*/
static void insercion_lims(int T[], int inicial, int final);

/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a escribir.
   @param final: Posición detrás de la última de la parte del
                   vector a escribir
                   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El número de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static void fusion(int T[], int inicial, int final, int U[], int V[]);

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

const int UMBRAL_MS = 100;

void mergesort(int T[], int num_elem) { mergesort_lims(T, 0, num_elem); }

static void mergesort_lims(int T[], int inicial, int final) {
  if (final - inicial < UMBRAL_MS) {
    insercion_lims(T, inicial, final);
  } else {
    int k = (final - inicial) / 2;

    int *U = new int[k - inicial + 1];
    assert(U);
    int l, l2;
    for (l = 0, l2 = inicial; l < k; l++, l2++)
      U[l] = T[l2];
    U[l] = INT_MAX;

    int *V = new int[final - k + 1];
    assert(V);
    for (l = 0, l2 = k; l < final - k; l++, l2++)
      V[l] = T[l2];
    V[l] = INT_MAX;

    mergesort_lims(U, 0, k);
    mergesort_lims(V, 0, final - k);
    fusion(T, inicial, final, U, V);
    delete[] U;
    delete[] V;
  };
}

static void fusion(int T[], int inicial, int final, int U[], int V[]) {
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++) {
    if (U[j] < V[k]) {
      T[i] = U[j];
      j++;
    } else {
      T[i] = V[k];
      k++;
    };
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

  const int TAM_GRANDE = 10000;
  const int NUM_VECES = 1000;

  double tiempo = 0.0f;

  for (int i = 0; i < iteraciones; ++i) {

    int *copy = new int[n];
    std::copy(T, T + n, copy);

    assert(copy);

    auto t1 = high_resolution_clock::now();
    mergesort(copy, n);
    auto t2 = high_resolution_clock::now();

    tiempo += duration_cast<duration<double>>(t2 - t1).count();

    delete[] copy;
  }

  tiempo /= iteraciones;

  cout << n << " " << tiempo << endl;

  delete[] T;

  return 0;
};
