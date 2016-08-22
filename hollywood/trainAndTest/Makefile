CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC
SHVER = 2
OS = $(shell uname)

all: trainAndTest

lib: svm.o
	SHARED_LIB_FLAG="-shared -Wl,-soname,libsvm.so.$(SHVER)";
	$(CXX) $${SHARED_LIB_FLAG} svm.o -o libsvm.so.$(SHVER)

trainAndTest: train_hu.cpp svm.o
	$(CXX) $(CFLAGS) train_hu.cpp svm.o -o train_hu -lm -lstdc++ -I ../ 

svm.o: svm.cpp svm.h
	$(CXX) $(CFLAGS) -c svm.cpp
clean:
	rm -f *~ svm.o trainAndTest libsvm.so.$(SHVER)
