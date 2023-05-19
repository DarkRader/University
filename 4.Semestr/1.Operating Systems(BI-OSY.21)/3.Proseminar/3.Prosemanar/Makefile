CC=gcc
CFLAGS=-Wall -pedantic -Wno-long-long
TARGETS=proc1 proc2 proc3 runlimit1 runlimit2

all: $(TARGETS)

proc1: proc1.c
	$(CC) $(CFLAGS) -o proc1 proc1.c
	
proc2: proc2.c
	$(CC) $(CFLAGS) -o proc2 proc2.c

proc3: proc3.c
	$(CC) $(CFLAGS) -o proc3 proc3.c

runlimit1: runlimit1.c
	$(CC) $(CFLAGS) -o runlimit1 runlimit1.c

runlimit2: runlimit2.c
	$(CC) $(CFLAGS) -o runlimit2 runlimit2.c

clean:
	rm -f $(TARGETS) core *~
	
	