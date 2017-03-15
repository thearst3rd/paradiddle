# Makefile for Paradiddle Language
# by Terry Hearst

CFLAGS = -Wall -g0

paradiddle: main.o Paradiddle.o
	g++ $(CFLAGS) main.o Paradiddle.o -o paradiddle

main.o: main.cpp Paradiddle.h
	g++ $(CFLAGS) -c main.cpp

Paradiddle.o: Paradiddle.cpp Paradiddle.h
	g++ $(CFLAGS) -c Paradiddle.cpp

all: paradiddle

clean:
	rm -f *.o *.exe paradiddle
