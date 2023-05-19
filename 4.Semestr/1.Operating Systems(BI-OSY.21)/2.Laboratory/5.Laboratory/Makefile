CC        = gcc
CFLAGS    = -Wall -pedantic 
LIBS      = -lpthread -lrt  
CXX       = g++
CXXFLAGS  = -Wall -pedantic

TARGETS   = server client thread_alternation_POSIX process_alternation_POSIX

all: $(TARGETS)

server: server.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

client: client.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

thread_alternation_POSIX: thread_alternation_POSIX.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

process_alternation_POSIX: process_alternation_POSIX.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	\rm -f $(TARGETS) *~ core
