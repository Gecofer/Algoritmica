/**
@file Ordenación por inserción
*/

#include <iostream>
#include <chrono>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <ctime>

#include "timecolletor.h"
#include "mergesort.h"

using namespace std;
using namespace std::chrono;


/* ************************************************************ */
/*  Estructura de datos que contiene un puntero al inicio de    */
/*  un vector y su número de elementos                          */
/*                                                              */
struct Vector {
	int *v = nullptr;
	int n_elem = 0;
};

/* ************************************************************ */
/*  Método de eliminación de repetidos por fuerza bruta         */

/**
@brief Elimina los elementos repetidos de un vector

@param vec: referncia al vector de elementos con el número de elementos.
No se modifica.

@return Devuelve un nuevo vector sin elementos repetidos.

*/
inline static Vector* elimina_repetidos(const Vector &vec);



/**
Implementación de las funciones
**/


/* VERSION DIVIDE Y VENCERAS */
inline static Vector* elimina_repetidos(const Vector &vec) {
  int elem, sig_elem, n_elem_max = vec.n_elem;

	int *copia = new int[n_elem_max];
	std::copy(vec.v, vec.v + n_elem_max, copia);

	mergesort(copia, n_elem_max);

	Vector* sin_repetidos = new Vector;
	sin_repetidos->v = new int[n_elem_max];

  sin_repetidos->v[0] = copia[0];
  ++sin_repetidos->n_elem;

	for (int i = 0; i < n_elem_max - 1; ++i) {

		elem = copia[i];
		sig_elem = copia[i + 1];

		if (elem != sig_elem) {
			sin_repetidos->v[sin_repetidos->n_elem] = sig_elem;
			++sin_repetidos->n_elem;
		}
	}

	delete []copia;

	return sin_repetidos;
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

	// comprobar si el n�mero de iteraciones es correcto.
	if (iteraciones < 1) {
		cerr << "ERROR: El número de iteraciones debe igual o mayor que 1." << endl;

		return (-3);
	}

	TimeCollector collector(n, iteraciones);

	Vector vec;
	vec.v = new int[n];
	vec.n_elem = n;
	assert(vec.v);

	srandom(time(0));


	for (int i = 0; i < n; i++) {
		vec.v[i] = random()%n;
	};

	Vector* sin_repetidos;
	for (int i = 0; i < iteraciones; ++i) {

		auto t1 = high_resolution_clock::now();
		sin_repetidos = elimina_repetidos(vec);
		auto t2 = high_resolution_clock::now();

		collector.addTime(duration_cast<duration<double>>(t2 - t1).count());

		#ifdef DEBUG
			cout << "Repetidos: ";
			for(int i = 0; i < vec.n_elem; ++i) {
				cout << vec.v[i] << " ";
			}

			cout << endl << "Sin repetidos: ";
			for(int i = 0; i < sin_repetidos->n_elem; ++i) {
				cout << sin_repetidos->v[i] << " ";
			}

			cout << endl;
		#endif

		delete[] sin_repetidos->v;
		delete sin_repetidos;
	}

	collector.print();
	collector.writeToCsv("repetidos_divide.csv");

	delete[] vec.v;

	return 0;
};
