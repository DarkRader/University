CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -pedantic
LDFLAGS =

all: compile

compile: test

valgrind: test
	valgrind ./test

run: test
	./test

test: test.o CExam.o CList.o CTeacher.o SStudent.o
	$(CXX) $^ -o test $(LDFLAGS)

test.o: test.cpp CExam.hpp CList.hpp CTeacher.hpp SStudent.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

CExam.o: CExam.cpp CExam.hpp CList.hpp CTeacher.hpp SStudent.hpp
	$(CXX) $(CXXFLAGS) -c CExam.cpp -o CExam.o

CList.o: CList.cpp CList.hpp SStudent.hpp
	$(CXX) $(CXXFLAGS) -c CList.cpp -o CList.o

CTeacher.o: CTeacher.cpp CTeacher.hpp
	$(CXX) $(CXXFLAGS) -c CTeacher.cpp -o CTeacher.o

SStudent.o: SStudent.cpp SStudent.hpp
	$(CXX) $(CXXFLAGS) -c SStudent.cpp -o SStudent.o

clean:
	-rm -f *.o
	-rm -f test
