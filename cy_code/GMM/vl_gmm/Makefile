CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC
SHVER = 2
OS = $(shell uname)

all: vlgmm

vlgmm: vlgmm.cpp
	$(CXX) $(CFLAGS) vlgmm.cpp -o vlgmm -I ~/lib/vlfeat -L ~/lib/vlfeat/bin/glnxa64 -L /usr/lib -l vl -lstdc++
clean:
	rm -f *~ vlgmm
