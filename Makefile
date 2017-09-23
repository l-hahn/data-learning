CC=g++
CFLAGS=-Wall -O3 -std=c++11 -ftree-vectorize -ffast-math -march=native -fopt-info-loop-optimized=y.Log # -g -fno-omit-frame-pointer -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -Wl,--no-as-needed -lprofiler -ltcmalloc -Wl,--as-needed #-parallel -xHost #-prof-gen -prof-dir=./  -funroll-loops -ftree-vectorize -ftree-vectorizer-verbose=1 

BASESRC=src/main.cpp src/mdimension.cpp
BASEHDR=src/mdimension.hpp src/mmatrix.hpp
BASEOBJ=$(BASESRC:.cpp=.o)
BASEEXE=dimreduction

all: $(BASESRC) $(BASEEXE)

$(BASEEXE): $(BASEOBJ)
	$(CC) $(CFLAGS) $(BASEOBJ) -o $@

.cpp.o: $(BASEHDR)
		$(CC) -c $(CFLAGS) $< -o $@

clean:
	find ./src/ -name "*.o" -delete
	find ./ -name $(BASEEXE) -delete
	find ./ -name $(BASEEXE) -delete
