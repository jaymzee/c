CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall
LFLAGS = -lm
OBJS =

fft: fft.o main.o
	$(CC) -o $@ $^ $(LFLAGS)

fft.o: fft.c fft.h
	$(CC) -o $@ -c $(CFLAGS) $<

main.o: main.c fft.h
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	rm -f main.o fft.o fft
