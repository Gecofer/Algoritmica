CXX = clang++
CXXFLAGS = -g -O3 -std=c++11

ARCHIVOS_PRINCIPALES = Problema.cpp Solucion.cpp Problema.h Solucion.h QAP_main.cpp Greedy.h Greedy.cpp

all: QAP_main

QAP_main : $(ARCHIVOS_PRINCIPALES) QAP_main.o Greedy.o Problema.o Solucion.o
	$(CXX) $(CXXFLAGS) QAP_main.o Greedy.o Problema.o Solucion.o -o QAP_main

QAP_main.o : QAP_main.cpp Problema.h Solucion.h Greedy.h
	$(CXX) $(CXXFLAGS) -c QAP_main.cpp -o QAP_main.o

Problema.o : Problema.cpp Problema.h
	$(CXX) $(CXXFLAGS) -c Problema.cpp -o Problema.o

Greedy.o : Greedy.cpp Greedy.h Solucion.h Problema.h
	$(CXX) $(CXXFLAGS) -c Greedy.cpp -o Greedy.o

Solucion.o : Solucion.cpp Solucion.h
	$(CXX) $(CXXFLAGS) -c Solucion.cpp -o Solucion.o

clean:
	@-rm -v QAP_main QAP_main.o Greedy.o Problema.o Solucion.o
