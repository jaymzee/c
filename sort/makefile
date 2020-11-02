CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall
LFLAGS = -s
OBJS = quicksort insertsort selectsort mergesort-top mergesort-bot

all: $(OBJS)
clean:
	rm -f $(OBJS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $< $(LFLAGS)

