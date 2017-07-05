#makefile for individual assignment 1

all: main

main: main.o
	g++ -std=c++11 main.o -o main
	
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
	
clean:
	rm *o main