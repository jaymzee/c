CC = gcc
CFLAGS = -Wall
LDFLAGS = -lrt -lpthread
OBJS = client server

all: $(OBJS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

clean:
	rm -f $(OBJS)
