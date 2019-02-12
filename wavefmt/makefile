CC = gcc
CFLAGS = -O2 -std=c89 -pedantic -Wall
LFLAGS = -s
all: wavdump wavwrite wavreverb wavcanfilt
wavcanfilt: wavcanfilt.o wavefmt.o canfilt.o
	$(CC) -o $@ $^ $(LFLAGS)
wavreverb: wavreverb.o wavefmt.o circfilt.o
	$(CC) -o $@ $^ $(LFLAGS)
wavwrite: wavwrite.o wavefmt.o
	$(CC) -o $@ $^ -lm $(LFLAGS)
wavdump: wavdump.o wavefmt.o
	$(CC) -o $@ $^ $(LFLAGS)
wavcanfilt.o: wavcanfilt.c wavefmt.h canfilt.h
	$(CC) $(CFLAGS) -c $<
wavreverb.o: wavreverb.c wavefmt.h circfilt.h
	$(CC) $(CFLAGS) -c $<
canfilt.o: canfilt.c canfilt.h
	$(CC) $(CFLAGS) -c $<
circfilt.o: circfilt.c circfilt.h
	$(CC) $(CFLAGS) -c $<
wavwrite.o: wavwrite.c wavefmt.h
	$(CC) $(CFLAGS) -c $<
wavdump.o: wavdump.c wavefmt.h
	$(CC) $(CFLAGS) -c $<
wavefmt.o: wavefmt.c wavefmt.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o wavdump wavwrite wavcanfilt wavreverb
