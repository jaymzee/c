CC = gcc
CFLAGS = -std=c89 -pedantic -Wall
LFLAGS = 
all: wavdump wavwrite
wavdump: wavdump.o wavefmt.o
	$(CC) -o wavdump wavdump.o wavefmt.o $(LFLAGS)
wavwrite: wavwrite.o wavefmt.o
	$(CC) -o wavwrite wavwrite.o wavefmt.o -lm $(LFLAGS)
wavwrite.o: wavwrite.c wavefmt.h
	$(CC) $(CFLAGS) -c wavwrite.c
wavdump.o: wavdump.c wavefmt.h
	$(CC) $(CFLAGS) -c wavdump.c
wavefmt.o: wavefmt.c wavefmt.h
	$(CC) $(CFLAGS) -c wavefmt.c
clean:
	rm -f *.o wavdump wavwrite
