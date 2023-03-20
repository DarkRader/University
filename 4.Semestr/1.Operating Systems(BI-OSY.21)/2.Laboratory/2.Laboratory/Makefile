CC        = gcc
CFLAGS    = -Wall -pedantic -ansi 
LIBS      = -lpthread  
CXX       = g++
CXXFLAGS  = -Wall -pedantic

TARGETS   = prodcons_cv_01 condvar_pt_01 condvar_01 task_01 task_02 task_03

all: $(TARGETS)

prodcons_cv_01: prodcons_cv_01.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

condvar_pt_01: condvar_pt_01.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

condvar_01: condvar_01.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)
	
task_01: task_01.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)
	
task_02: task_02.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)
	
task_03: task_03.cpp
	$(CXX) -std=c++11 $(CXXFLAGS) -o $@ $< $(LIBS)

clean:
	\rm -f $(TARGETS) *~ core

