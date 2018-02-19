CC=g++
CFLAGS=-Wall -O3 -std=c++11 -fopenmp 

BASESRC=test/debug_matrix.cpp
BASEHDR=src/mmatrix.hpp #src/mdimension.hpp src/mmatrix.hpp src/meigen.hpp src/mining.hpp src/learning.hpp src/clustering.hpp
BASEOBJ=$(BASESRC:.cpp=.o)
BASEFLD=bin
BASEEXE=debug_data-learning

all: $(BASESRC) $(BASEEXE)

$(BASEEXE): $(BASEOBJ)
	$(CC) $(CFLAGS) $(BASEOBJ) -o $(BASEFLD)/$@

.cpp.o: $(BASEHDR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	find ./test/ -name "*.o" -delete
	find ./$(BASEFLD) -name $(BASEEXE) -delete
	find ./$(BASEFLD) -name $(BASEEXE) -delete
