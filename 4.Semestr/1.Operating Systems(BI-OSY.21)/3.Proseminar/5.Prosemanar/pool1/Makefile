#CXX=g++
# CXX=i586-mingw32msvc-g++
CXX=i686-w64-mingw32-g++

CFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -static-libgcc -static-libstdc++

all: pool.exe

pool.exe: main.o ball.o balllist.o
	$(CXX) $(CFLAGS) -mwindows -lgdi32 -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	rm -f pool.exe core *~ *.o
	
ball.o: ball.cpp ball.h
balllist.o: balllist.cpp balllist.h ball.h
main.o: main.cpp ball.h balllist.h
