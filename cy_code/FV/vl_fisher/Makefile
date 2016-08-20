CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC
SHVER = 2
OS = $(shell uname)

all: vlfisher

vlfisher: fisher.cpp
	$(CXX) $(CFLAGS) fisher.cpp -o vlfisher -I ../../ -I /home/jupanito/src/vlfeat -I /usr/local/include -L /home/jupanito/src/vlfeat/bin/glnxa64 -l vl -lstdc++ -l z -l m -l opencv_highgui -l opencv_core
clean:
	rm -f *~ vlfisher
