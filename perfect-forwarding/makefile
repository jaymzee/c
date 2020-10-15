pf: perfect-forwarding.o Snitch.o
	g++ -o pf perfect-forwarding.o Snitch.o

perfect-forwarding.o: perfect-forwarding.cpp
	g++ -c -fno-elide-constructors perfect-forwarding.cpp

Snitch.o: ../snitch/Snitch.cpp
	g++ -c ../snitch/Snitch.cpp

clean:
	rm -rf pf perfect-forwarding.o Snitch.o
