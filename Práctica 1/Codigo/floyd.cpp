/**
   @file Cálculo del coste de los caminos mínimos. Algoritmo de Floyd.
*/

#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;

static int const MAX_LONG = 10;

/**********************************************************************/

/**
   @brief Reserva espacio en memoria dinámica para una matriz cuadrada.

   @param dim: dimensión de la matriz. dim > 0.

   @returns puntero a la zona de memoria reservada.
*/
int **ReservaMatriz(int dim);

/**********************************************************************/

/**
   @brief Libera el espacio asignado a una matriz cuadrada.

   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param dim: dimensión de la matriz. dim > 0.

   Liberar la zona memoria asignada a M y lo pone a NULL.
*/
void LiberaMatriz(int **&M, int dim);

/**********************************************************************/

/**
   @brief Rellena una matriz cuadrada con valores aleaotorias.

   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param dim: dimensión de la matriz. dim > 0.

   Asigna un valor aleatorio entero de [0, MAX_LONG - 1] a cada
   elemento de la matriz M, salvo los de la diagonal principal
   que quedan a 0..
*/
void RellenaMatriz(int **M, int dim);

/**********************************************************************/
/**
   @brief Cálculo de caminos mínimos.

   @param M: Matriz de longitudes de los caminos. Es MODIFICADO.
   @param dim: dimensión de la matriz. dim > 0.

   Calcula la longitud del camino mínimo entre cada par de nodos (i,j),
   que se almacena en M[i][j].
*/
void Floyd(int **M, int dim);

/**********************************************************************/
/**
   @brief Copia de una matriz

   @param M: Matriz de longitudes de los caminos. Se crea una copia.
   @param dim: dimensión de la matriz. dim > 0.

   @returns puntero a la zona de memoria de la copia de la matriz
*/
int **makeCopyMatriz(int **M, int dim);

/**********************************************************************/

/**
   Implementación de las funciones
**/

int **ReservaMatriz(int dim) {
  int **M;
  if (dim <= 0) {
    cerr << "\n ERROR: Dimension de la matriz debe ser mayor que 0" << endl;
    exit(1);
  }
  M = new int *[dim];
  if (M == NULL) {
    cerr << "\n ERROR: No puedo reservar memoria para un matriz de " << dim
         << " x " << dim << "elementos" << endl;
    exit(1);
  }
  for (int i = 0; i < dim; i++) {
    M[i] = new int[dim];
    if (M[i] == NULL) {
      cerr << "ERROR: No puedo reservar memoria para un matriz de " << dim
           << " x " << dim << endl;
      for (int j = 0; j < i; j++)
        delete[] M[i];
      delete[] M;
      exit(1);
    }
  }
  return M;
}

/**********************************************************************/

void LiberaMatriz(int **&M, int dim) {
  for (int i = 0; i < dim; i++)
    delete[] M[i];
  delete[] M;
  M = NULL;
}

/**********************************************************************/
void RellenaMatriz(int **M, int dim) {
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
      if (i != j)
        M[i][j] = (rand() % MAX_LONG);
}

/**********************************************************************/
void Floyd(int **M, int dim) {
  for (int k = 0; k < dim; k++)
    for (int i = 0; i < dim; i++)
      for (int j = 0; j < dim; j++) {
        int sum = M[i][k] + M[k][j];
        M[i][j] = (M[i][j] > sum) ? sum : M[i][j];
      }
}

/**********************************************************************/
int **makeCopyMatriz(int **M, int dim) {
  int **copy;
  if (dim <= 0) {
    cerr << "\n ERROR: Dimension de la matriz debe ser mayor que 0" << endl;
    exit(1);
  }
  copy = new int *[dim];
  if (copy == NULL) {
    cerr << "\n ERROR: No puedo reservar memoria para un matriz de " << dim
         << " x " << dim << "elementos" << endl;
    exit(1);
  }
  for (int i = 0; i < dim; i++) {
    copy[i] = new int[dim];

    if (copy[i] == NULL) {
      cerr << "ERROR: No puedo reservar memoria para un matriz de " << dim
           << " x " << dim << endl;
      for (int j = 0; j < i; j++)
        delete[] M[i];
      delete[] M;
      exit(1);
    }

    std::copy(M[i], M[i] + dim, copy[i]);
  }
  return copy;
}

/**********************************************************************/
int main(int argc, char **argv) {

  // Comprobar que el número de argumentos sea dos.
  /*
  * El primero debe de ser el número de nodos, el segundo es el número de repeticiones.
  */
  if (argc != 3) {
    cerr << "El programa necesita dos argumentos." << endl
         << "Uso: " << argv[0] << " <número de nodos> <número de repeticiones>"
         << endl;

    return (-1);
  }

  int dim = std::stoi(argv[1]);
  int iteraciones = std::stoi(argv[2]);

  // comprobar si el tamaño del array es correcto
  if (dim < 2) {
    cerr << "ERROR: el de nodos es demasiado pequeño, "
         << "Debe ser como mínimo dos componentes." << endl;

    return (-2);
  }

  // comprobar si el número de iteraciones es correcto.
  if (iteraciones < 1) {
    cerr << "ERROR: El número de iteraciones debe igual o mayor que 1." << endl;

    return (-3);
  }


  int **M = ReservaMatriz(dim);

  RellenaMatriz(M, dim);

  double tiempo = 0.0f;

  for(int i = 0; i < iteraciones; ++i) {
    int ** copy = makeCopyMatriz(M, dim);

    auto t1 = high_resolution_clock::now();
    // Empieza el algoritmo de floyd
    Floyd(M, dim);
    auto t2 = high_resolution_clock::now();

    tiempo += duration_cast<duration<double>>(t2 - t1).count();

    LiberaMatriz(copy, dim);
  }

  tiempo /= iteraciones;

  cout << dim << " " << tiempo << endl;

  LiberaMatriz(M, dim);


  return 0;
}
