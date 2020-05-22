CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall -O3
LFLAGS = -lm
OBJS = benchmark.o test.o fft.o util.o

all: test benchmark

test: test.o fft.o util.o
	$(CC) -o $@ $^ $(LFLAGS)

benchmark: benchmark.o fft.o util.o
	$(CC) -o $@ $^ $(LFLAGS)

fft.o: fft.c fft.h
	$(CC) -o $@ -c $(CFLAGS) $<

util.o: util.c util.h
	$(CC) -o $@ -c $(CFLAGS) $<

test.o: test.c fft.h util.h
	$(CC) -o $@ -c $(CFLAGS) $<

benchmark.o: benchmark.c fft.h util.h
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) benchmark test
