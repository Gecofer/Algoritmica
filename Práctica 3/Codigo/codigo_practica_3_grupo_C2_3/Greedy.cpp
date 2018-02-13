#include <climits>
#include <cmath>
#include "Greedy.h"

using namespace std;

Solucion greedyQAP(const Problema &p) {

  int max, min, pos_max, pos_min, hab, ofi, NumLC, tam_solucion;

  int tam_problema = p.getTamanioProblema();

  Solucion solucion(tam_problema);

  int* distancias_potenciales = new int[tam_problema];
  int* flujos_potenciales = new int[tam_problema];
  int** LC = new int*[tam_problema];

  for(int i = 0; i < tam_problema; ++i) {
    LC[i] = new int[tam_problema];
  }

  for(int i = 0; i < tam_problema; ++i) {

    distancias_potenciales[i] = 0;
    flujos_potenciales[i] = 0;

    for(int j = 0; j < tam_problema; ++j) {
      distancias_potenciales[i] += p.getDistancia(i,j);
      flujos_potenciales[i] += p.getFlujo(i,j);
    }
  }

  // Beneficio de meter un oficinista en una habitacion
  for (int i = 0; i < tam_problema; ++i) {
    for(int j = 0; j < tam_problema; ++j) {
      // Se calcula el beneficio de una distancia.
      LC[i][j] = abs(distancias_potenciales[i] - flujos_potenciales[j]);
    }
  }

  NumLC = tam_problema * tam_problema;
  tam_solucion = 0;

  // Mientras la lista de candidatos no este vacia
  while (NumLC > 0 && tam_solucion < tam_problema) {

    max = INT_MIN;
    hab = -1;
    ofi = -1;

    for (int i = 0; i < tam_problema; ++i) {
      for(int j = 0; j < tam_problema; ++j) {
        if (LC[i][j] > max) {
          max = LC[i][j];
          hab = i;
          ofi = j;
        }
      }
    }

    solucion.setUnidadLocalizacion(ofi, hab);
    tam_solucion++;

    // Eliminamos los candidatos
    for (int i=0; i < tam_problema; ++i) {
      if (LC[hab][i] != -1) {
        LC[hab][i] = -1;
        NumLC--;
      }
    }

    for (int i=0; i < tam_problema; ++i) {
      if (LC[i][ofi] != -1){
         LC[i][ofi] = -1;
         NumLC--;
      }
    }

  }

  /*for(int j = 0; j < tam_problema; ++j) {
    max = INT_MIN;
    min = INT_MAX;

    for(int i = 0; i < tam_problema; ++i) {


      if(distancias_potenciales[i] > max && distancias_potenciales[i] != -1) {

        max = distancias_potenciales[i];
        pos_max = i;

      }

      if(flujos_potenciales[i] < min && flujos_potenciales[i] != -1) {

        min = flujos_potenciales[i];
        pos_min = i;

      }

    }

    solucion[pos_max] = pos_min;
    distancias_potenciales[pos_max] = -1;
    flujos_potenciales[pos_min] = -1;
  }*/

  delete [] distancias_potenciales;
  delete [] flujos_potenciales;

  for (int i = 0; i < tam_problema; ++i) {
    delete [] LC[i];
  }

  delete [] LC;

  return solucion;
}
