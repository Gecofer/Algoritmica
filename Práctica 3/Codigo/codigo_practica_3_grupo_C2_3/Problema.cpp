/**
 * @file Problema.cpp
 * @brief Implementacion de la clase Problema
 */
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Problema.h"


using namespace std;

// Constructor por defecto
Problema::Problema() {
  this->tam_problema = 0;
  this->distancias = nullptr;
	this->flujos = nullptr;
}

// Constructor de copia
Problema::Problema(const Problema &other) {
  this->copiar(other);
}

// Destructor
Problema::~Problema() {
  this->liberarMemoria();
}

// Liberar Memoria
void Problema::liberarMemoria() {

  for (int i = 0; i < this->tam_problema; ++i) {
	  delete [] this->distancias[i];
	  delete [] this->flujos[i];
  }

  delete [] this->distancias;
  delete [] this->flujos;
}

// Operador de asignacion
Problema & Problema::operator=(const Problema &other) {
  this->liberarMemoria();
  this->copiar(other);

  return(*this);
}

// Copiar los datos de un problema a otro
void Problema::copiar(const Problema &other) {

  this->tam_problema = other.getTamanioProblema();

  this->reservarMemoria(this->tam_problema);

  int** other_distancias = other.distancias;
  int** other_flujos = other.flujos;

  for(int i = 0; i < this->tam_problema; ++i) {
    copy(other_distancias[i], other_distancias[i] + this->tam_problema, this->distancias[i]);
    copy(other_flujos[i], other_flujos[i] + this->tam_problema, this->flujos[i]);
  }
}

// Reservar memoria
void Problema::reservarMemoria(int n) {
  this->distancias = new int* [n];
	this->flujos = new int* [n];

	for (int i = 0; i < n; ++i) {
	  this->distancias[i] = new int [n];
	  this->flujos[i] = new int [n];
	}
}

// Funcion que carga el archivo del problema
void Problema::cargarArchivo (const char* filename) {

  int entrada = 0;
	ifstream file (filename);

	// Comprobar que el archivo se ha podido abrir con exito
	if (!file) {
	  cerr << "No se ha podido abrir el archivo " << filename <<  endl;
	  exit(-1);
	}

	file >> this->tam_problema;

	this->reservarMemoria(this->tam_problema);

	// Rellenamos nuestras matrices
	for (int i = 0; i < this->tam_problema; ++i) {
		for (int j = 0; j < this->tam_problema; ++j) {
			file >> entrada;
			this->distancias[i][j] = entrada;
		}
	}

	for (int i = 0; i < this->tam_problema; ++i) {
		for (int j = 0; j < this->tam_problema; ++j) {
			file >> entrada;
			this->flujos[i][j] = entrada;
		}
	}

	file.close();
}

// Devolvemos el tamanio del problema
int Problema::getTamanioProblema () const {
  return this->tam_problema;
}

// Devolvemos la distancia entre la habitacion i y la j
int Problema::getDistancia (int i, int j) const {
  return this->distancias[i][j];
}

// Devolvemos el flujo entre el oficinista i y el j
int Problema::getFlujo (int i, int j) const {
  return this->flujos[i][j];
}
