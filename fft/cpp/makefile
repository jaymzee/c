CC = gcc
CXX = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -O3
LFLAGS =
OBJS = test test-vector benchmark

all: $(OBJS)

test: test.cpp fft.hpp util.hpp
	$(CXX) -o $@ $(CFLAGS) $<

test-vector: test-vector.cpp fft-vector.hpp fft.hpp util.hpp
	$(CXX) -o $@ $(CFLAGS) $<

benchmark: benchmark.cpp fft.hpp util.hpp
	$(CXX) -o $@ $(CFLAGS) $<

clean:
	rm -f $(OBJS) *.o
