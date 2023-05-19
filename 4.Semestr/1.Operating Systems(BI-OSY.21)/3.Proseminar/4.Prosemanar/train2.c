/* Obsazovani nadrazi - demonstrace synchronizace procesu. Nadrazi ma PLATFORM_MAX
 * koleji. Vlaky prijizdeji k nadrazi, obsazuji volne koleje. Pokud je nadrazi plne,
 * cekaji na vjezdu do nadrazi. Vlaky jsou simulovane procesy, synchronizace probiha
 * pres POSIX semafory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/mman.h>
#include <semaphore.h>

#define PLATFORM_MAX  3

typedef struct TShmData
{
  int   m_Platform[PLATFORM_MAX];
  sem_t m_Entry;
  sem_t m_Mutex;
} TSHMDATA;


TSHMDATA * g_Data   = NULL;

/* Alokace sdilene pameti a semaforu.
 */
int resAlloc ( void )
{
  int i;

  g_Data = (TSHMDATA *)mmap ( NULL, sizeof ( *g_Data ), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
  
  if ( ! g_Data )
  {
    perror ( "mmap:" );
    return 1;
  }

  /* Vsechny koleje jsou volne
   */
  for ( i = 0; i < PLATFORM_MAX; i ++ )
    g_Data -> m_Platform[i] = 0;

  /* inicializace semaforu - vjezd (PLATFORM_MAX) a mutex (1)
   * pozor - priznak pshared (druhy parametr) je nastaven na 1.
   */
  sem_init ( &g_Data -> m_Entry, 1, PLATFORM_MAX );
  sem_init ( &g_Data -> m_Mutex, 1, 1 );
  return 0;
}

/* Uvolneni prostredku.
 */
void resDone ( void )
{
  if ( ! g_Data ) 
    return;
  sem_destroy ( &g_Data -> m_Entry );
  sem_destroy ( &g_Data -> m_Mutex );
  munmap ( (void*)g_Data, sizeof  (*g_Data ) );
  g_Data = NULL;
}

/* Synchronizace - vjezd do stanice
 */
int  enterStation ( int id )
{
  int i;
  
  sem_wait ( &g_Data -> m_Entry );
  sem_wait ( &g_Data -> m_Mutex );
  for ( i = 0; i < PLATFORM_MAX; i ++ )
    if ( g_Data -> m_Platform[i] == 0 )
      break;
  g_Data -> m_Platform[i] = id;
  sem_post ( &g_Data -> m_Mutex );
  return i;
}

/* Synchronizace - opusteni stanice
 */
void leaveStation ( int plt )
{
  sem_wait ( &g_Data -> m_Mutex );
  g_Data -> m_Platform [plt] = 0;
  sem_post ( &g_Data -> m_Mutex );
  sem_post ( &g_Data -> m_Entry );
}

/* nahodna cisla v rozsahu lo az hi
 */
int Random ( int lo, int hi )
{
  return lo + (int)( (hi - lo) * 1.0 * rand () / RAND_MAX );
}

/* Funkce procesu vlaku
 */
void TrainProcess ( int  myId )
{
  int plt;

  while ( 1 )
  {
    printf ( "Train %d approaching the station\n", myId );
    plt = enterStation ( myId );
    printf ( "Train %d loading/unloading, platform %d\n", myId, plt );
    usleep ( Random ( 3000000, 5000000 ) );
    printf ( "Train %d left station\n", myId );
    leaveStation ( plt );
    usleep ( Random ( 5000000, 10000000 ) );
  }
}

/* Uklid IPC prostredku
 */
void cleanup ( void )
{
  resDone ();
}

int main ( int argc, char * argv [] )
{
  int        trains, i, st;
  pid_t      x;

  if ( argc != 2 
       || sscanf ( argv[1], "%d", &trains ) != 1 )
  {
    fprintf ( stderr, "Usage: %s <trains>\n", argv[0] );
    return 1;
  }

  /* Alokace shm a sem
   */
  if ( resAlloc() )
  {
    cleanup ();
    return 1;
  }

  /* vytvoreni synovskych procesu
   */
  for ( i = 0; i < trains; i ++ )
  {
    x = fork ();
    if ( x < 0 )
    {
      perror ( "fork:" );
      cleanup ();
      return 1;
    }
    if ( x == 0 )
    {
      TrainProcess ( i + 1 );
      exit ( 0 );
    }
  }

  /* Cekani na ukonceni
   */
  for ( i = 0; i < trains; i ++ )
    wait ( &st );

  /* uklid
   */
  cleanup ();
  return 0;
}
