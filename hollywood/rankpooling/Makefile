CXX ?= g++
CC ?= gcc
CFLAGS = -Wall -Wconversion -O3 -fPIC -lstdc++ -I ../
LIBS = blas/blas.a
SHVER = 3
OS = $(shell uname)
#LIBS = -lblas

all: getDarwin

lib: linear.o tron.o blas/blas.a
	SHARED_LIB_FLAG="-shared -Wl,-soname,liblinear.so.$(SHVER)"; 
	$(CXX) $${SHARED_LIB_FLAG} linear.o tron.o blas/blas.a -o liblinear.so.$(SHVER)

getDarwin: tron.o linear.o getDarwin.cpp blas/blas.a
	$(CXX) $(CFLAGS) -o getDarwin getDarwin.cpp tron.o linear.o $(LIBS)

tron.o: tron.cpp tron.h
	$(CXX) $(CFLAGS) -c -o tron.o tron.cpp

linear.o: linear.cpp linear.h
	$(CXX) $(CFLAGS) -c -o linear.o linear.cpp

blas/blas.a: blas/*.c blas/*.h
	make -C blas OPTFLAGS='$(CFLAGS)' CC='$(CC)';

clean:
	make -C blas clean
	rm -f *~ tron.o linear.o getDarwin liblinear.so.$(SHVER)
