CC = gcc
CFLAGS = -std=c89 -Wall -pedantic-errors -march=native -mfpmath=sse
LFLAGS = -s
mand: mand.o
	$(CC) -o mand mand.o $(LFLAGS)
mand.o: mand.c
	$(CC) $(CFLAGS) -c mand.c
clean:
	rm mand.o mand
