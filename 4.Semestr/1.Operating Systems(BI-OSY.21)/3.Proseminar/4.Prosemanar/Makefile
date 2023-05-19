CC=gcc
CFLAGS=-Wall -pedantic -Wno-long-long
TARGETS=shm1 shm2-p1 shm2-p2  train1 train2

all: $(TARGETS)

shm1: shm1.c
	$(CC) $(CFLAGS) -o shm1 shm1.c
	
shm2-p1: shm2-p1.c
	$(CC) $(CFLAGS) -o shm2-p1 shm2-p1.c

shm2-p2: shm2-p2.c
	$(CC) $(CFLAGS) -o shm2-p2 shm2-p2.c

train1: train1.c
	$(CC) $(CFLAGS) -o train1 train1.c

train2: train2.c
	$(CC) $(CFLAGS) -o train2 train2.c -lrt -lpthread

clean:
	rm -f $(TARGETS) core *~
	
	