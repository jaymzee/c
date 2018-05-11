CC = gcc
CFLAGS = -std=c89 -Wall -pedantic-errors -march=native -mfpmath=387 -g
LFLAGS = 
mand: mand.o
	$(CC) -o mand mand.o $(LFLAGS)
mand.o: mand.c
	$(CC) $(CFLAGS) -c mand.c
clean:
	rm mand.o mand
