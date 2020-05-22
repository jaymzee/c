CC = gcc
CXX = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -O3
LFLAGS =
OBJS = test test-vector benchmark

all: $(OBJS)

test: test.cpp fft.h util.h
	$(CXX) -o $@ $(CFLAGS) $<

test-vector: test-vector.cpp fft.h fft-vector.h util.h
	$(CXX) -o $@ $(CFLAGS) $<

benchmark: benchmark.cpp fft.h util.h
	$(CXX) -o $@ $(CFLAGS) $<

clean:
	rm -f $(OBJS) *.o
