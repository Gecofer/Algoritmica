###############################################################################
# Makefile
###############################################################################

SHELL = /bin/bash # for ubuntu

###############################################################################

SRC = $(wildcard *.cpp)
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
CSV = $(EXE:=.csv)
SVG = $(EXE:=.svg)

###############################################################################

CFLAGS = -O3
CXXFLAGS =  $(CFLAGS) -std=c++11 # -std=c++1y

###############################################################################

default: $(EXE)

all: default data

clean:
	$(RM) -rfv $(EXE)

purge: clean
	$(RM) -rfv $(SVG) $(DAT) $(CSV)

data: default
	chmod +x generateData.sh
	./generateData.sh
