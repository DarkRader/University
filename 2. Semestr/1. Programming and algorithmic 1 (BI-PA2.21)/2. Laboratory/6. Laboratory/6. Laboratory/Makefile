CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -pedantic
LDFLAGS =

all: compile

compile: test

valgrind: test
	valgrind ./test

run: test
	./test

test: test.o CTaskScheduler.o CTask.o
	$(CXX) $^ -o test $(LDFLAGS)

test.o: test.cpp CTaskScheduler.hpp CTask.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

CTaskScheduler.o: CTaskScheduler.cpp CTaskScheduler.hpp CTask.hpp
	$(CXX) $(CXXFLAGS) -c CTaskScheduler.cpp -o CTaskScheduler.o

CTask.o: CTask.cpp CTask.hpp
	$(CXX) $(CXXFLAGS) -c CTask.cpp -o CTask.o

clean:
	-rm -f *.o
	-rm -f test
