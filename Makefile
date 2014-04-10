CC=g++
CFLAGS=-std=c++11 -O2 -Wall

objects=main.o naive.o platform.o

all: NTR

NTR: $(objects)
	$(CC) -o NTR $(objects) $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

main.cpp: player.h platform.h

platform.cpp: platform.h

naive.cpp: player.h naive.h

.PHONY: clean
clean:
	rm -f NTR *.o
