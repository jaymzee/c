CC = gcc
CXX = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -O3
LFLAGS =
OBJS =

all: test benchmark

test: test.cpp fft.h util.h
	$(CXX) -o $@ $(CFLAGS) $<

benchmark: benchmark.cpp fft.h util.h
	$(CXX) -o $@ $(CFLAGS) $<

clean:
	rm -f $(OBJS) benchmark test
