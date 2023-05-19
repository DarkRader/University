/* shm-server - server program to demonstrate shared memory. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHMSZ     27

int main()
{
  char c;
  int shmid;
  key_t key;
  char *shm, *s;

  /* Define a key. */
  key = 5679;

  /* Allocate System V shared memory segment. */
  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0700)) < 0) 
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
  printf("Server:  shm address = %p\n", shm);

  /* Write some data to shared memory segment. */ 
  s = shm;

  for (c = 'a'; c <= 'z'; c++) 
  {
    *s++ = c;
  }
  *s = 0;

  /* Wait until the other process changes the first character of shared memory segment to '*',
     indicating that it has read the data.  */
  while (*shm != '*')
    sleep(1);

  /* Dettach the segment. */
  if ( shmdt(shm) < 0 ) 
  {
    perror("shmdt");
    exit(1);
  }

  /* Deallocate the segment. */
  if ( shmctl(shmid, IPC_RMID, 0 ) < 0 ) 
  {
    perror("shmctl");
    exit(1);
  }

  return EXIT_SUCCESS;
}
