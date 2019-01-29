CC = gcc
CFLAGS = -std=c89 -pedantic -Wall
LFLAGS = 
wavdump: wavdump.o wavefmt.o
	$(CC) -o wavdump wavdump.o wavefmt.o $(LFLAGS)
wavdump.o: wavdump.c wavefmt.h
	$(CC) $(CFLAGS) -c wavdump.c
wavefmt.o: wavefmt.c wavefmt.h
	$(CC) $(CFLAGS) -c wavefmt.c
clean:
	rm *.o
	rm wavdump
