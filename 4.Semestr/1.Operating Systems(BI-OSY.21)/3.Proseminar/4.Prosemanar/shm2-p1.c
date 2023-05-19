/* Ukazka pouziti sdilene pameti mezi dvema procesy - prvni proces vytvori sdilenou pamet,
 * ulozi do ni data. Druhy proces se k shm pripji, data zpracuje (zde odstrani
 * duplicitni hodnoty v poli), signalizuje prvni proces a ukonci se.
 *
 * Tento zdrojovy kod je "prvni" - vytvari shm.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <wait.h>
#include <string.h>
#include <strings.h>

/* Sdilena data - jsou umistena do struktury, aby bylo mozne je alokovat najednou.
 * Je lepe alokovat mene vetsich bloku nez hodne malych.
 */

#define DATA_MAX  200
typedef struct TShmData
{
  int       m_Cnt;
  int       m_Data[DATA_MAX];
  pid_t     m_Pid;
} TSHMDATA;

int        g_ShmId  = 0;
TSHMDATA * g_Data   = NULL;
int        g_Signal = 0;

/* K probuzeni prvniho procesu pouzijeme signal SIGHUP. Neni to idealni reseni,
 * ale zde pracuje uspokojive. Lepsi by samozrejme bylo pouzit semafory.
 */

void newSigHup ( int signum )
{
  g_Signal = 1;
}

void cleanup ( void )
{
  /* Odmapovani z adresniho prostoru
   */
  shmdt ( (void*)g_Data );
  /* Fyzicke uvolneni prostredku shm
   */
  shmctl ( g_ShmId, IPC_RMID, NULL );
}


int main ( int argc, char * argv [] )
{
  int    i;
  struct sigaction sa;
  key_t  key;
  char   pathName[100], * slash;


  /* Pripravime obsluhu signalu sighup.
   */
  memset ( &sa, 0, sizeof ( sa ) );
  sa . sa_handler = newSigHup;
  sigaction ( SIGHUP, &sa, NULL );

  /* Pro prirazeni klice shm pouzijeme ftok. Za jmeno ref. souboru zvolime jmeno adresare,
   * ve kterem se nachazeji (oba) spustitelne programy. Pro nase testovani je to rozumne, pro
   * produkcni nasazeni samozrejme ne.
   */
  strncpy ( pathName, argv[0], sizeof ( pathName ) );
  slash = rindex ( pathName, '/' );
 *slash = 0;

  key = ftok ( pathName, 1 );
  if ( key < 0 )
  {
    perror ( "ftok" );
    return 1;
  }

  /* Alokace shm. Jedna se o blok, ktery muze byt zpristupnen vice procesy, proto davame explicitne klic.
   * Prava jsou 0700 (vlastnik vse, ostatni zadny pristup), chceme vytvorit novy blok (IPC_CREAT) a chceme
   * mit jistotu, ze se nepripojime k jinemu jiz existujicimu bloku (IPC_EXCL)
   */
  g_ShmId = shmget ( key, sizeof ( *g_Data ), 0700 | IPC_CREAT | IPC_EXCL );
  if ( g_ShmId < 0 )
  {
    perror ( "shmget" );
    return 1;
  }
  /* Namapujeme blok sdilene pameti do adresniho prostoru.
   */
  g_Data = (TSHMDATA *) shmat ( g_ShmId, NULL, 0 );

  /* Nahodna vypln pole.
   */
  g_Data -> m_Cnt = (int)( 1.0 * rand () * DATA_MAX / RAND_MAX );
  for ( i = 0; i < g_Data -> m_Cnt; i ++ )
    g_Data -> m_Data[i] = rand () % 300;

  g_Data -> m_Pid = getpid ();

  /* prvni proces ceka na signal od druheho procesu. Cekani muze byt dlouhe.
   */
  while ( ! g_Signal )
    sleep ( 1 );

  /* Vypis
   */
  for (i = 0; i < g_Data -> m_Cnt; i ++ )
    printf ( "%d ", g_Data -> m_Data[i] );
  printf ( "\n" );

  /* Uvolneni prostredku.
   */
  cleanup ();
  return 0;
}
