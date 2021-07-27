CC = gcc
OBJS = $(addprefix bin/, static/libmumpy.a shared/libmumpy.so statically-linked dynamically-linked)

.PHONY: clean

all: $(OBJS)

%.o: %.c
	$(CC) -c -fPIC -o $@ $^

bin/static/libmumpy.a: math.o vector.o
	ar rcs $@ $^

bin/shared/libmumpy.so: math.o vector.o
	$(CC) -shared -o $@ $^

bin/statically-linked: main.o bin/static/libmumpy.a
	$(CC) -o $@ -Lbin/static -static $< -lmumpy

bin/dynamically-linked: main.o bin/shared/libmumpy.so
	$(CC) -o $@ -Lbin/shared $< -lmumpy

clean:
	rm -f main.o math.o vector.o $(OBJS)
