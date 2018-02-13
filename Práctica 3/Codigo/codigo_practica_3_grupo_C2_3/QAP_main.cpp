#include <iostream>
#include "Problema.h"
#include "Solucion.h"
#include "Greedy.h"

using namespace std;

int main(int argc, char **argv) {

	if (argc < 1) {
		cout << "Debe introducir un fichero de datos" << endl;
		exit(0);
	}

	Problema p;

	p.cargarArchivo(argv[1]);
  Solucion s = greedyQAP(p);

  for (int i=0; i<s.getTamanioSolucion(); ++i) {
    cout << "Habitacion " << i + 1 << " corresponde al Oficinista " << s.getUnidadLocalizacion(i) + 1 << endl;
  }

	return 0;
}
