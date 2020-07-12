CC = gcc
CFLAGS = -O2 -pedantic-errors -Wall
LFLAGS = -lm

bbrot: bbrot.o
	$(CC) -o $@ $^ $(LFLAGS)

bbrot.o : bbrot.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f bbrot.o bbrot
