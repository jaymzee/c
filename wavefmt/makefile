CC = gcc
CFLAGS = -std=c89 -pedantic -Wall
LFLAGS = 
all: wavdump wavwrite wavfilter
wavfilter: wavfilter.o wavefmt.o
	$(CC) -o wavfilter wavfilter.o wavefmt.o -lm $(LFLAGS)
wavwrite: wavwrite.o wavefmt.o
	$(CC) -o wavwrite wavwrite.o wavefmt.o -lm $(LFLAGS)
wavdump: wavdump.o wavefmt.o
	$(CC) -o wavdump wavdump.o wavefmt.o $(LFLAGS)
wavfilter.o: wavfilter.c wavefmt.h
	$(CC) $(CFLAGS) -c wavfilter.c
wavwrite.o: wavwrite.c wavefmt.h
	$(CC) $(CFLAGS) -c wavwrite.c
wavdump.o: wavdump.c wavefmt.h
	$(CC) $(CFLAGS) -c wavdump.c
wavefmt.o: wavefmt.c wavefmt.h
	$(CC) $(CFLAGS) -c wavefmt.c
clean:
	rm -f *.o wavdump wavwrite wavfilter
