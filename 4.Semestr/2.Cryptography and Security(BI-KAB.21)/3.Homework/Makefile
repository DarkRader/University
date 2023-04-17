CC=g++
CFLAGS=-Wall -pedantic -std=c++17
LIBS=-L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
INCLUDES=-I/opt/homebrew/opt/openssl@3/include

all: main

main: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

clean:
	rm -f main
