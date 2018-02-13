#ifndef TIMMECOLLECTOR_H
#define TIMMECOLLECTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class TimeCollector {
public:
	TimeCollector(const unsigned &data, const unsigned &iterations);
	TimeCollector(const unsigned &data, const unsigned &iterations, const std::string &header);
	~TimeCollector();

	inline void addTime(const double &time);
	void writeToCsv(const std::string &file);
	void print();

private:
	void calculateMean();
	inline bool checkMeanCalculated();

	std::vector<double> times;
	double meanTimes;
	unsigned data;
	std::string header;
};

/**
@brief Constructor para crear el recolector de tiempos. Necesita el número de
datos de la ejecución.

@param data Número de datos de la ejecución.
@param iterations Número de iteraciones.
*/
TimeCollector::TimeCollector(const unsigned &data, const unsigned &iterations): meanTimes(0.0f), data(data) {
	this->times.reserve(iterations);
	this->header = "\"Data\",\"Time(sec)\"";
}

/**
@brief Constructor para crear el recolector de tiempos. Necesita el número de
datos de la ejecución y la cabecera del csv.

@param data Número de datos de la ejecución.
@param iterations Número de iteraciones.
@param header Cabecera para introducir en el csv.
*/
TimeCollector::TimeCollector(const unsigned &data, const unsigned &iterations, const std::string &header): meanTimes(0.0f), data(data) {
	this->times.reserve(iterations);
	this->header = header;
}

TimeCollector::~TimeCollector() {}

/**
@brief Método que añade un tiempo al recolector.
@param time Tiempo de la ejecución.
*/
void TimeCollector::addTime(const double &time) {
	this->times.push_back(time);
}

/**
@brief Método que calcula la media de los tiempos.
*/
void TimeCollector::calculateMean() {
	for (auto t : this->times) {
		this->meanTimes += t;
	}

	this->meanTimes /= this->times.size();
}

/**
@brief Método que comprueba si se ha calculado la media.
@return true si se ha calculado la media. false si no.
*/
bool TimeCollector::checkMeanCalculated() {
	return ((this->meanTimes > 0.0f) || (this->times.size() == 0));
}

/**
@brief Método que imprime por consola el resultado de la media de tiempos.
*/
void TimeCollector::print() {
	if ( !checkMeanCalculated() ) {
		this->calculateMean();
	}

	std::cout << this->data << "\t" << this->meanTimes << std::endl;
}

/**
@brief Método que escribe en un archivo de texto plano la media del tiempo en
formato csv.
*/
void TimeCollector::writeToCsv(const std::string &file) {
	if (!checkMeanCalculated()) {
		this->calculateMean();
	}

	std::ifstream fileExists(file);
	std::ofstream fileOutput(file, std::ofstream::out | std::ofstream::app);

	// si el archivo csv no existe, después de crearlo le añadimos la cabecera.
	if (!fileExists.good()) {
		fileOutput << this->header << std::endl;
	}

	fileExists.close();

	fileOutput << "\"" << this->data << "\",\"" << this->meanTimes << "\"" << std::endl;

	fileOutput.close();
}

#endif // TIMMECOLLECTOR_H
