CXXFLAGS = -Wall -pedantic -std=c++17

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTS = $(wildcard tests/*.test.cpp)

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./kuznear1

.PHONY: compile
compile: kuznear1

kuznear1: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@

debug/%.test: tests/%.test.cpp $(filter-out build/main.o,$(OBJECTS))
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -I src/ -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf kuznear1 build/ debug/ doc/ 2>/dev/null

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST; done

# Requirements / Dependencies
CDataSize.o: src/CDataSize.cpp src/CDataSize.h
CDataSize.o: src/CDataSize.h
CFloat.o: src/CFloat.cpp src/CFloat.h src/CDataSize.h src/CFloatBig.h \
 src/CIntegerBig.h
CFloat.o: src/CFloat.h src/CDataSize.h src/CFloatBig.h src/CIntegerBig.h
CFloatBig.o: src/CFloatBig.cpp src/CFloatBig.h src/CDataSize.h \
 src/CIntegerBig.h
CFloatBig.o: src/CFloatBig.h src/CDataSize.h src/CIntegerBig.h
CInteger.o: src/CInteger.cpp src/CInteger.h src/CDataSize.h
CInteger.o: src/CInteger.h src/CDataSize.h
CIntegerBig.o: src/CIntegerBig.cpp src/CIntegerBig.h src/CDataSize.h
CIntegerBig.o: src/CIntegerBig.h src/CDataSize.h
CParsData.o: src/CParsData.cpp src/CParsData.h src/CShuntYardAlg.h \
 src/CInteger.h src/CDataSize.h src/CFloat.h src/CFloatBig.h \
 src/CIntegerBig.h
CParsData.o: src/CParsData.h src/CShuntYardAlg.h src/CInteger.h \
 src/CDataSize.h src/CFloat.h src/CFloatBig.h src/CIntegerBig.h
CShuntYardAlg.o: src/CShuntYardAlg.cpp src/CShuntYardAlg.h src/CInteger.h \
 src/CDataSize.h src/CFloat.h src/CFloatBig.h src/CIntegerBig.h
CShuntYardAlg.o: src/CShuntYardAlg.h src/CInteger.h src/CDataSize.h \
 src/CFloat.h src/CFloatBig.h src/CIntegerBig.h
main.o: src/main.cpp src/CFloat.h src/CDataSize.h src/CFloatBig.h \
 src/CIntegerBig.h src/CInteger.h src/CParsData.h src/CShuntYardAlg.h
