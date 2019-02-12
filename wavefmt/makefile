CC = gcc
CFLAGS = -std=c89 -pedantic -Wall
LFLAGS = 
all: wavdump wavwrite wavreverb wavcanfilt
wavcanfilt: wavcanfilt.o wavefmt.o canfilt.o
	$(CC) -o wavcanfilt wavcanfilt.o wavefmt.o canfilt.o $(LFLAGS)
wavreverb: wavreverb.o wavefmt.o circfilt.o
	$(CC) -o wavreverb wavreverb.o wavefmt.o circfilt.o $(LFLAGS)
wavwrite: wavwrite.o wavefmt.o
	$(CC) -o wavwrite wavwrite.o wavefmt.o -lm $(LFLAGS)
wavdump: wavdump.o wavefmt.o
	$(CC) -o wavdump wavdump.o wavefmt.o $(LFLAGS)
wavcanfilt.o: wavcanfilt.c wavefmt.h canfilt.h
	$(CC) $(CFLAGS) -c wavcanfilt.c
wavreverb.o: wavreverb.c wavefmt.h circfilt.h
	$(CC) $(CFLAGS) -c wavreverb.c
canfilt.o: canfilt.c canfilt.h
	$(CC) $(CFLAGS) -c canfilt.c
circfilt.o: circfilt.c circfilt.h
	$(CC) $(CFLAGS) -c circfilt.c
wavwrite.o: wavwrite.c wavefmt.h
	$(CC) $(CFLAGS) -c wavwrite.c
wavdump.o: wavdump.c wavefmt.h
	$(CC) $(CFLAGS) -c wavdump.c
wavefmt.o: wavefmt.c wavefmt.h
	$(CC) $(CFLAGS) -c wavefmt.c
clean:
	rm -f *.o wavdump wavwrite wavcanfilt wavreverb
