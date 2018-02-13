/**
 * @file Solucion.cpp
 * @brief Implementacion de la clase Solucion
 */
#include <algorithm>
#include "Solucion.h"

using namespace std;

// Constructor
Solucion::Solucion(unsigned tam) {
  this->tam_solucion = tam;
  this->reservarMemoria(tam);
}

// Constructor copia
Solucion::Solucion(const Solucion &other) {
  this->copiar(other);
}

// Destructor
Solucion::~Solucion() {
  this->liberarMemoria();
}

// Operador de asignacion
Solucion & Solucion::operator=(const Solucion &other) {
  this->liberarMemoria();
  this->copiar(other);

  return(*this);
}

// Copiar la solucion de un vector
void Solucion::copyVecSolucion(int *sol, int tam) {
  this->liberarMemoria();

  this->tam_solucion = tam;
  this->reservarMemoria(tam);

  copy(sol, sol + tam, this->solucion);

}

// Setter de unidad
void Solucion::setUnidadLocalizacion(int unidad, unsigned localizacion) {
  if(this->tam_solucion > localizacion)
    this->solucion[localizacion] = unidad;
}

// Getter de unidad
int Solucion::getUnidadLocalizacion(unsigned localizacion) const {
  return(this->solucion[localizacion]);
}

// Getter del tamaño de la solucion.
int Solucion::getTamanioSolucion() const {
  return this->tam_solucion;
}

// Funcion para copiar otra solucion
void Solucion::copiar(const Solucion &other) {
  this->tam_solucion = other.getTamanioSolucion();

  this->reservarMemoria(this->tam_solucion);

  copy(other.solucion, other.solucion + this->tam_solucion, this->solucion);
}

// Reservar memoria
void Solucion::reservarMemoria(unsigned n) {
  this->solucion = new int[n];
}

// Liberar Memoria
void Solucion::liberarMemoria() {
  delete [] this->solucion;
}
