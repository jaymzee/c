CC = gcc
CXX = g++
CFLAGS = -O2 -std=c89 -pedantic -Wall
CXXFLAGS = -O2 -std=c++11 -pedantic -Wall
LFLAGS = -s
OBJSBASIC = wavdump wavwrite
OBJSFLTRC = wavcanfilt wavreverb wavflanger
OBJSFLTRCPP = wavCanFilt wavReverb wavFlanger
OBJS = $(OBJSBASIC) $(OBJSFLTRC) $(OBJSFLTRCPP)

all: $(OBJS)

wavCanFilt: wavCanFilt.o wavefmt.o CanonicalFilter.o
	$(CXX) -o $@ $^ $(LFLAGS)
wavReverb: wavReverb.o wavefmt.o CircularFilter.o
	$(CXX) -o $@ $^ $(LFLAGS)
wavFlanger: wavFlanger.o wavefmt.o Delay.o
	$(CXX) -o $@ $^ -lm $(LFLAGS)

wavCanFilt.o: wavCanFilt.cpp wavefmt.h CanonicalFilter.h
	$(CXX) $(CXXFLAGS) -c $<
wavReverb.o: wavReverb.cpp wavefmt.h CircularFilter.h
	$(CXX) $(CXXFLAGS) -c $<
wavFlanger.o: wavFlanger.cpp wavefmt.h Delay.h
	$(CXX) $(CXXFLAGS) -c $<

CanonicalFilter.o: CanonicalFilter.cpp CanonicalFilter.h
	$(CXX) $(CXXFLAGS) -c $<
CircularFilter.o: CircularFilter.cpp CircularFilter.h
	$(CXX) $(CXXFLAGS) -c $<
Delay.o: Delay.cpp Delay.h
	$(CXX) $(CXXFLAGS) -c $<

wavflanger: wavflanger.o wavefmt.o fracdelay.o
	$(CC) -o $@ $^ -lm $(LFLAGS)
wavcanfilt: wavcanfilt.o wavefmt.o canfilt.o
	$(CC) -o $@ $^ $(LFLAGS)
wavreverb: wavreverb.o wavefmt.o circfilt.o
	$(CC) -o $@ $^ $(LFLAGS)

wavflanger.o: wavflanger.c wavefmt.h fracdelay.h
	$(CC) $(CFLAGS) -c $<
wavcanfilt.o: wavcanfilt.c wavefmt.h canfilt.h
	$(CC) $(CFLAGS) -c $<
wavreverb.o: wavreverb.c wavefmt.h circfilt.h
	$(CC) $(CFLAGS) -c $<

fracdelay.o: fracdelay.c fracdelay.h
	$(CC) $(CFLAGS) -c $<
canfilt.o: canfilt.c canfilt.h
	$(CC) $(CFLAGS) -c $<
circfilt.o: circfilt.c circfilt.h
	$(CC) $(CFLAGS) -c $<

wavwrite: wavwrite.o wavefmt.o
	$(CC) -o $@ $^ -lm $(LFLAGS)
wavdump: wavdump.o wavefmt.o
	$(CC) -o $@ $^ $(LFLAGS)

wavwrite.o: wavwrite.c wavefmt.h
	$(CC) $(CFLAGS) -c $<
wavdump.o: wavdump.c wavefmt.h
	$(CC) $(CFLAGS) -c $<

wavefmt.o: wavefmt.c wavefmt.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(OBJS)
