CC = gcc
LDFLAGS = -lrt -lpthread
OBJS = client server

all: $(OBJS)

%: %.c
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS)
