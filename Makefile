CC=g++
CFLAGS=-Wall -O3 -std=c++11 # -ftree-vectorize -ffast-math -march=native -fopt-info-loop-optimized=y.Log # -g -fno-omit-frame-pointer -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -Wl,--no-as-needed -lprofiler -ltcmalloc -Wl,--as-needed #-parallel -xHost #-prof-gen -prof-dir=./  -funroll-loops -ftree-vectorize -ftree-vectorizer-verbose=1 

BASESRC=src/debug.cpp
BASEHDR=lib/mdimension.hpp lib/mmatrix.hpp lib/meigen.hpp lib/mining.hpp lib/learning.hpp lib/clustering.hpp
BASEOBJ=$(BASESRC:.cpp=.o)
BASEFLD=bin
BASEEXE=debug_data-learning

all: $(BASESRC) $(BASEEXE)

$(BASEEXE): $(BASEOBJ)
	$(CC) $(CFLAGS) $(BASEOBJ) -o $(BASEFLD)/$@

.cpp.o: $(BASEHDR)
		$(CC) -c $(CFLAGS) $< -o $@

clean:
	find ./src/ -name "*.o" -delete
	find ./$(BASEFLD) -name $(BASEEXE) -delete
	find ./$(BASEFLD) -name $(BASEEXE) -delete
