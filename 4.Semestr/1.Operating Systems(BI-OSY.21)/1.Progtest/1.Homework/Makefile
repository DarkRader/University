#MAKEFILE FOR LINUX
CXX=g++
LD=g++
AR=ar
CXXFLAGS=-std=c++17 -Wall -pedantic -fsanitize=thread
SHELL:=/bin/bash
MACHINE=$(shell uname -m)-$(shell echo $$OSTYPE)

all: test

deps:
	g++ -MM *.cpp > Makefile.d

test: solution.o sample_tester.o
	$(LD) $(CXXFLAGS) -o $@ $^ -L./$(MACHINE) -lprogtest_solver -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -g

lib: progtest_solver.o
	mkdir -p $(MACHINE)
	$(AR) cfr $(MACHINE)/libprogtest_solver.a $^

clean:
	rm -f *.o test *~ core sample.tgz Makefile.d

pack: clean
	rm -f sample.tgz
	tar zcf sample.tgz --exclude progtest_solver.cpp --exclude Makefile.mingw *


-include Makefile.d


#MAKEFILE FOR MAC-OS WITH M1
#CXX=/opt/homebrew/Cellar/gcc/12.2.0/bin/aarch64-apple-darwin22-g++-12
#LD=/opt/homebrew/Cellar/gcc/12.2.0/bin/aarch64-apple-darwin22-g++-12
#AR=ar
#CXXFLAGS=-std=c++17 -Wall -pedantic -g
#SHELL:=/bin/bash
#MACHINE=$(shell uname -m)-$(shell echo $$OSTYPE)
#
#all: test
#
#deps:
#	g++ -MM *.cpp > Makefile.d
#
#test: solution.o sample_tester.o
#	$(LD) $(CXXFLAGS) -o $@ $^ -L./$(MACHINE) -lprogtest_solver -lpthread
#
#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $< -g
#
#lib: progtest_solver.o
#	mkdir -p $(MACHINE)
#	$(AR) cfr $(MACHINE)/libprogtest_solver.a $^
#
#clean:
#	rm -f *.o test *~ core sample.tgz Makefile.d
#
#pack: clean
#	rm -f sample.tgz
#	tar zcf sample.tgz --exclude progtest_solver.cpp --exclude Makefile.mingw *
#
#
#-include Makefile.d


