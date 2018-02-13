/**
 * @file Problema.h
 * @brief Cabecera de la clase Problema
 */

#ifndef _PROBLEMA_H_
#define _PROBLEMA_H_

class Problema {

	public:

	  /**
     * @brief Constructor por defecto
     */
		Problema();

		/**
     * @brief Constructor de copia
     */
		Problema(const Problema &other);

		/**
     * @brief Destructor
     */
		~Problema();

    Problema&  operator=(const Problema &other);

		/**
     * @brief Funcion que carga el archivo del problema
     * @param filename archivo a leer
     */
		void cargarArchivo (const char* filename);

		/**
     * @brief Devolvemos el tamanio del problema
     */
	   int getTamanioProblema() const;

		/**
     * @brief Devolvemos la distancia entre la habitacion i y la j
     * @param i habitacion i
     * @param j habitacion i
     */
		int getDistancia(int i, int j) const;

		/**
     * @brief Devolvemos el flujo entre el oficinista i y el j
     * @param i oficinista i
     * @param j oficinista j
     */
		int getFlujo(int i, int j) const;

	private:
		int tam_problema;   // Tamanio del problema
		int **distancias;   // Matriz de distancia
		int **flujos;       // Matriz de flujos

		/**
     * @brief Copiar
     * @param other Copia los datos de un problema a otro
     */
		void copiar(const Problema &other);

		/**
     * @brief Liberar Memoria
     */
		void liberarMemoria();

		/**
     * @brief Reservar memoria
     * @param n El nuevo tamanio a reservar
     */
		void reservarMemoria(int n);
};

#endif // _PROBLEMA_H_
