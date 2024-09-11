CC=gcc
CFLAGS=-I.

DEPS = Guiao3.h Guiao2.h Guiao1.h Guiao4.h
OBJ = myTorneio.o Guiao3.o Guiao2.o Guiao1.o Guiao4.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myTorneio: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o myTorneio