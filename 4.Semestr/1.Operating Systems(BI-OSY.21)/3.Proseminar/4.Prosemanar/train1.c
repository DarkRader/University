/* Obsazovani nadrazi - demonstrace synchronizace procesu. Nadrazi ma PLATFORM_MAX
 * koleji. Vlaky prijizdeji k nadrazi, obsazuji volne koleje. Pokud je nadrazi plne,
 * cekaji na vjezdu do nadrazi. Vlaky jsou simulovane procesy, synchronizace probiha
 * pres System V IPC rozhrani.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <wait.h>
#include <string.h>


#define PLATFORM_MAX  3
/* pojmenovani semaforu v poli
 */
#define SEM_ENTRY     0
#define SEM_MUTEX     1

typedef struct TShmData
{
  int m_Platform[PLATFORM_MAX];
} TSHMDATA;

/* ID alokovanych prostredku
 */
int        g_ShmId  = -1;
int        g_SemId  = -1;
TSHMDATA * g_Data   = NULL;

/* Alokace shm. Alokujeme jako IPC_PRIVATE. Sdilena pamet bude pole
 * obsazeni koleji na nadrazi.
 */
int shmAlloc ( void )
{
  int i;
  
  g_ShmId = shmget ( IPC_PRIVATE, sizeof ( *g_Data ), 0700 | IPC_CREAT );
  if ( g_ShmId < 0 )
  {
    perror ( "shmget:" );
    return 1;
  }
  g_Data = (TSHMDATA *) shmat ( g_ShmId, NULL, 0 );

  /* Vsechny koleje jsou volne
   */
  for ( i = 0; i < PLATFORM_MAX; i ++ )
    g_Data -> m_Platform[i] = 0;
  return 0;
}

/* Uvolneni shm.
 */
void shmDone ( void )
{
  if ( g_ShmId == -1 ) 
    return;
  shmdt ( (void*)g_Data );
  shmctl ( g_ShmId, IPC_RMID, NULL );
  g_ShmId = -1;
}

/* Alokace semaforu. Semafory jsou IPC_PRIVATE. Alokujeme
 * celkem 2 semafory - vjezd do nadrazi a mutex pro pristup
 * ke sdilene pameti.
 */
int semAlloc ( void )
{
  unsigned short int initArray[2] = { PLATFORM_MAX, 1 };
  union semun 
  {
    int             val;
    struct semid_ds *buf;
    unsigned short  *array;
  } arg;
  arg . array = initArray;

  g_SemId = semget ( IPC_PRIVATE, 2, 0700 | IPC_CREAT );
  if ( g_SemId < 0 )
  {
    perror ( "semget:" );
    return 1;
  }
  /* Vychozi nastaveni hodnot semaforu.
   */
  semctl ( g_SemId, 2, SETALL, arg );
  return 0;
}

/* Uvolneni semaforu.
 */
void semDone ( void )
{
  if ( g_SemId != -1 )
    semctl ( g_SemId, 0, IPC_RMID, NULL );
  g_SemId = -1;
}

/* Cekani na semaforu.
 */
void semWait ( int idx )
{
  struct sembuf op;

  op . sem_num = idx;
  op . sem_op  = -1;
  op . sem_flg = SEM_UNDO;
  semop ( g_SemId, &op, 1 );
}

/* Zvetsovani semaforu.
 */
void semPost ( int idx )
{
  struct sembuf op;

  op . sem_num = idx;
  op . sem_op  = +1;
  op . sem_flg = SEM_UNDO;
  semop ( g_SemId, &op, 1 );
}

/* Synchronizace - vjezd do stanice
 */
int  enterStation ( int id )
{
  int i;
  semWait ( SEM_ENTRY );
  semWait ( SEM_MUTEX );
  for ( i = 0; i < PLATFORM_MAX; i ++ )
    if ( g_Data -> m_Platform[i] == 0 )
      break;
  g_Data-> m_Platform[i] = id;
  semPost ( SEM_MUTEX );
  return i;
}

/* Synchronizace - opusteni stanice
 */
void leaveStation ( int plt )
{
  semWait ( SEM_MUTEX );
  g_Data -> m_Platform [plt] = 0;
  semPost ( SEM_MUTEX );
  semPost ( SEM_ENTRY );
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
  shmDone ();
  semDone ();
}

/* Signal handler. Simulace bezi stale, musi se ukoncit stiskem Ctrl-C.
 * Ale pri nasilnem ukonceni nebudou uvolnene IPC prostredy. Proto
 * nastavime novy signal handler pro signaly INT a TERM. V obsuze signalu
 * prostredy uvolnime.
 */
void newSigTerm ( int signum )
{
  cleanup ();
  exit ( 0 );
}

int main ( int argc, char * argv [] )
{
  int        trains, i, st;
  pid_t      x;
  struct sigaction sa;

  if ( argc != 2 || sscanf ( argv[1], "%d", &trains ) != 1 )
  {
    fprintf ( stderr, "Usage: %s <trains>\n", argv[0] );
    return 1;
  }

  /* Alokace shm a sem
   */
  if ( shmAlloc() )
  {
    cleanup ();
    return 1;
  }
  if ( semAlloc () )
  {
    cleanup ();
    return 1;
  }

  /* Obsluha signalu
   */
  memset ( &sa, 0, sizeof ( sa ) );
  sa . sa_handler = newSigTerm;
  sigaction ( SIGINT, &sa, NULL );
  sigaction ( SIGTERM, &sa, NULL );

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

  /* tento kod nebude za normalnich okolnosti dosazitelny
   */
  cleanup ();
  return 0;
}
