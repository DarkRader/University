CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -pedantic
LDFLAGS =

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJS = $(SOURCES:.cpp=.o)

all: compile

compile: test

valgrind: test
	valgrind ./test

run: test
	./test

test: $(OBJS)
	$(CXX) $^ -o test $(LDFLAGS)

%.o: %cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	-rm -f *.o
	-rm -f test
	-rm -f Makefile.d

Makefile.d: $(SOURCES) $(HEADERS)
	g++ -MM $(SOURCES) > Makefile.d

include Makefile.d
