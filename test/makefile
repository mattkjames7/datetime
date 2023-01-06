# CFLAGS for CC
CFLAGS=-g -O3 -Wextra -fPIC -I../include
CXXFLAGS=-g -O3 -std=c++17 -Wextra -fPIC -I../include
LDFLAGS=-lm -Wl,-rpath='$$ORIGIN/../lib' -L ../lib -ldatetime


# Compiler
CC=gcc $(CFLAGS)
CXX=g++ $(CXXFLAGS)

all:
	$(CC) -o testc testc.c $(LDFLAGS)
	$(CXX) -o testcc testcc.cc $(LDFLAGS)
	./testc
	./testcc

clean:
	-rm -v testc
	-rm -v testcc