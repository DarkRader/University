/* shm-client - client program to demonstrate shared memory. */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHMSZ     27

int main()
{
  int shmid;
  key_t key;
  char *shm, *s;

  /* Define a key. */
  key = 5679;

  /* Get ID of System V shared memory segment. */
  if ((shmid = shmget(key, SHMSZ, 0700)) < 0) 
  {
    perror("shmget");
    exit(1);
  }

  /* Attach the memory segment to process virtual address space. */
  if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
  {
    perror("shmat");
    exit(1);
  }

  /* Print the address of shared memory segment. */
  printf("Client:  shm address = %p\n", shm);

  /* Read the data from the shared memory segment. */
  printf("Client: data =");
  for (s = shm; *s; s++)
    putchar(*s);
  putchar('\n');

  /* Change the first character of the memory segment to '*', 
     indicating you have read the data. */
  *shm = '*';

  /* Dettach the segment. */
  if ( shmdt(shm) < 0 ) 
  {
    perror("shmdt");
    exit(1);
  }

  return EXIT_SUCCESS;
}
