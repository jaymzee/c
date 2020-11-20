CC = g++
CFLAGS =
LFLAGS =
pf: perfect-forwarding.o snitch.o
	$(CC) -o pf $^ $(LFLAGS)

perfect-forwarding.o: perfect-forwarding.cpp
	$(CC) -c $(CFLAGS) -fno-elide-constructors $^

snitch.o: ../snitch/snitch.cpp
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf pf *.o
