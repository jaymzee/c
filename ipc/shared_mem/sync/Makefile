CC = gcc
CFLAGS = -Wall
LDFLAGS = -lrt -lpthread
OBJS = client logger

all: $(OBJS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

clean:
	rm -f $(OBJS)
