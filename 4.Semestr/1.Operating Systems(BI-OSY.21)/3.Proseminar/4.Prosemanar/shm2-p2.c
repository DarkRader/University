/* Ukazka pouziti sdilene pameti mezi dvema procesy - prvni proces vytvori sdilenou pamet,
 * ulozi do ni data. Druhy proces se k shm pripji, data zpracuje (zde odstrani
 * duplicitni hodnoty v poli), signalizuje prvni proces a ukonci se.
 *
 * Tento zdrojovy kod je "druhy" - pripojuje se k existujicimu bloku shm.
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


/* Odstraneni duplicitni prvky z pole (zachova pouze prvni vyskyt).
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
  key_t  key;
  char   pathName[100], *slash;


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

  /* Alokace shm. Pripojujeme se k existujicimu bloku, tedy zadavame klic a nenastavujeme IPC_CREAT.
   */
  g_ShmId = shmget ( key, sizeof ( *g_Data ), 0700 );
  if ( g_ShmId < 0 )
  {
    perror ( "shmget" );
    return 1;
  }
  /* Namapujeme blok sdilene pameti do adresniho prostoru.
   */
  g_Data = (TSHMDATA *) shmat ( g_ShmId, NULL, 0 );

  childMain ();

  /* Signalizujeme prvni proces. Jeho pid je ulozene ve sdilene pameti.
   */

  kill ( g_Data -> m_Pid, SIGHUP );

  /* Odmapujeme shm, ale neuvolnujeme vlastni prostredek - to udela prvni proces.
   */
  shmdt ( (void*)g_Data );

  return 0;
}
