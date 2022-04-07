CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -pedantic
LDFLAGS =

all: compile

compile: test

valgrind: test
	valgrind ./test

run: test
	./test

test: test.o CItem.o CNamedItem.o CSafeItem.o CCommonExplosive.o CDangerousExplosive.o CWarehouse.o
	$(CXX) $^ -o test $(LDFLAGS)

test.o: test.cpp CEnvironment.h CNamedItem.h CItem.h CSafeItem.h CCommonExplosive.h CDangerousExplosive.h CWarehouse.h
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

CItem.o: CItem.cpp CItem.h CEnvironment.h
	$(CXX) $(CXXFLAGS) -c CItem.cpp -o CItem.o
	
CNamedItem.o: CNamedItem.cpp CNamedItem.h CEnvironment.h
	$(CXX) $(CXXFLAGS) -c CNamedItem.cpp -o CNamedItem.o

CSafeItem.o: CSafeItem.cpp CSafeItem.h CNamedItem.h CItem.h CEnvironment.h
	$(CXX) $(CXXFLAGS) -c CSafeItem.cpp -o CSafeItem.o

CCommonExplosive.o: CCommonExplosive.cpp CCommonExplosive.h CNamedItem.h CItem.h CSafeItem.h CEnvironment.h
	$(CXX) $(CXXFLAGS) -c CCommonExplosive.cpp -o CCommonExplosive.o

CDangerousExplosive.o: CDangerousExplosive.cpp CDangerousExplosive.h CNamedItem.h CItem.h CSafeItem.h CEnvironment.h
	$(CXX) $(CXXFLAGS) -c CDangerousExplosive.cpp -o CDangerousExplosive.o

CWarehouse.o: CWarehouse.cpp CWarehouse.h CItem.h CSafeItem.h CEnvironment.h CNamedItem.h
	$(CXX) $(CXXFLAGS) -c CWarehouse.cpp -o CWarehouse.o

clean:
	-rm -f *.o
	-rm -f test
