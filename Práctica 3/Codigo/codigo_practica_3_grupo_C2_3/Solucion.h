/**
 * @file Solucion.h
 * @brief Cabecera de la clase Solucion
 */

#ifndef _SOLUCION_H_
#define _SOLUCION_H_

class Solucion {

  public:

    /**
     * @brief Constructor
     * @param tam tamaño de la solución
     */
		Solucion(unsigned tam);

		/**
		 * @brief Destructor
		 */
		 ~Solucion();

     /**
     * @brief Constructor de copias
     * @param other Instancia de la clase Solucion a copiar
     */
     Solucion(const Solucion &other);

     /**
     * @brief Operador de asignación
     * @param other Instancia de la clase Solucion a copiar
     * @return Instancia del objeto
     */
     Solucion&  operator=(const Solucion &other);

     /**
      * @brief Devolvemos el tamanio de la solucion
      */
 	   int getTamanioSolucion() const;

     /**
     * @brief Método para asignar una unidad a una localización
     * @param unidad unidad a asignar
     * @param localizacion localizacion donde asignar la unidad
     */
     void setUnidadLocalizacion(int unidad, unsigned localizacion);

     /**
     * @brief Método para obtener una unidad en una localizacion dada.
     * @param localizacion posicion de la unidad a obtener
     * @return unidad en la poscion solicitadas
     */
     int getUnidadLocalizacion(unsigned localizacion) const;

     /**
     * @brief Método para copiar un vector con una solución a la instancia
     * @param sol vector con la solucion
     * @param tam tamaño del vector
     */
     void copyVecSolucion(int *sol, int tam);


  private:
    unsigned tam_solucion;
    int *solucion;

    /**
     * @brief Copiar
     * @param other Copia los datos de una solucion a esta instancia
     */
		void copiar(const Solucion &other);

		/**
     * @brief Liberar Memoria
     */
		void liberarMemoria();

		/**
     * @brief Reservar memoria
     * @param n El nuevo tamanio a reservar
     */
		void reservarMemoria(unsigned n);
};

#endif // _SOLUCION_H_
