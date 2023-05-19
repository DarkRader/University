/* Ukazka pouziti sdilene pameti mezi rodicem a synem - rodicovsky proces vytvori sdilenou pamet,
 * ulozi do ni data na vytvori synovsky proces. Synovsky proces data zpracuje (zde odstrani
 * duplicitni hodnoty v poli) a ukonci se.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

/* Sdilena data - jsou umistena do struktury, aby bylo mozne je alokovat najednou.
 * Je lepe alokovat mene vetsich bloku nez hodne malych.
 */

#define DATA_MAX  200
typedef struct TShmData
{
  int       m_Cnt;
  int       m_Data[DATA_MAX];
} TSHMDATA;

int        g_ShmId  = 0;
TSHMDATA * g_Data   = NULL;

void cleanup ( void )
{
  /* Odmapovani z adresniho prostoru
   */
  shmdt ( (void*)g_Data );
  /* Fyzicke uvolneni prostredku shm
   */
  shmctl ( g_ShmId, IPC_RMID, NULL );
}

/* Synovsky proces. Odstrani duplicitni prvky z pole (zachova pouze prvni vyskyt).
 */
void childMain ( void )
{
  int unique = 0, i, j, duplicate;

  for ( i = 0; i < g_Data -> m_Cnt; i ++ )
  {
    duplicate = 0;
    for ( j = 0 ; j < unique; j ++ )
      if ( g_Data -> m_Data[i] == g_Data -> m_Data[j] )
      {
        duplicate = 1;
        break;
      }
    if ( ! duplicate )
      g_Data -> m_Data[unique ++] = g_Data -> m_Data[i];
  }
  g_Data -> m_Cnt = unique;
}

int main ( int argc, char * argv [] )
{
  pid_t  x;
  int    i, st;

  /* Alokace shm. Jedna se anonymni blok, proto je klic IPC_PRIVATE.
   * prava jsou 0700 (vlastnik vse, ostatni zadny pristup), chceme vytvorit novy blok (IPC_CREAT)
   */
  g_ShmId = shmget ( IPC_PRIVATE, sizeof ( *g_Data ), 0700 | IPC_CREAT );
  if ( g_ShmId < 0 )
  {
    perror ( "shmget" );
    return 1;
  }
  /* Namapujeme blok sdilene pameti do adresniho prostoru. Mapovani probehne jeste pred
   * fork (), tedy synovsky proces ziska stejny pametovy obraz (vcetne namapovaneho bloku
   * sdilene pameti).
   */
  g_Data = (TSHMDATA *) shmat ( g_ShmId, NULL, 0 );

  /* Nahodna vypln pole.
   */
  g_Data -> m_Cnt = (int)( 1.0 * rand () * DATA_MAX / RAND_MAX );
  for ( i = 0; i < g_Data -> m_Cnt; i ++ )
    g_Data -> m_Data[i] = rand () % 300;

  x = fork ();
  if ( x < 0 )
  { /* chyba
     */
    cleanup ();
    return 1;
  }

  if ( x == 0 )
  {
    /* Synovsky proces
     */
    childMain ();
    /* Odmapovat pamet, ale vlastni prostredek bude rusit rodic.
     */
    shmdt ( (void*)g_Data );
    /* Ukonceni synovskeho procesu.
     */
    exit ( 0 );
  }

  /* Rodic ceka na synovsky proces
   */
  waitpid ( x, &st, 0 );

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
