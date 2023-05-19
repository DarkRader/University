/* Program ukazuje, jak se necha omezit max. doba behu jineho programu. Podobna technika
 * je pouzita v Progtestu pri spousteni testovanych programu.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <wait.h>

/* Komunikace mezi signal handlerem a zbytkem programu
 */
 
int g_Wakeup [2];
int g_RecvSignal = 0;

/* Rodic dostane SIGCHLD pokud dobehne nejaky z jeho synu. Muze tim zareagovat (napr. volat wait)
 * Nase obsluha zde zapise jeden bajt do roury g_Wakeup, aby vzbudila hlavni program. Zaroven nastavi
 * priznak: synovsky proces skoncil (g_RecvSignal).
 */
void               newSigChild                             ( int sig )
{
  char dummy = 0;
  g_RecvSignal = 1;
  write ( g_Wakeup[1], &dummy, 1 );
}


/* Cekani na synovsky proces:
 *   Nelze volat rovnou wait/waitpid. Pokud by se synovsky proces zacyklil, budeme cekat stale.
 *   Volani sleep(timeout) by slo pouzit, ale ma spatnou reakcni dobu (trpi race-condition):
 *     pokud cekame ve sleep() a prijde signal SIGCHLD, dojde k probuzeni. To by bylo dobre,
 *     protoze bychom necekali celou dobu (cely timeut). Ale pokud by signalu SIGCHLD probehl
 *     jeste pred volanim sleep(), neprerusil by jej a sleep by zbytecne trvalo dlouho (race condition).
 *   Proto se ceka dokud nebudou k dispozici data na zadane roure. Data do roury posle signal handler.
 *     cekani na dostupnost dat lze omezit, race condition zde nenastava.
 */
int waitSignalTimeout ( int timeout )
{
  struct timeval tv;
  fd_set         rd;
  
  tv . tv_sec = timeout;
  tv . tv_usec = 0;
  FD_ZERO ( &rd );
  FD_SET ( g_Wakeup[0], &rd );
  /*  cekame dokud bud nejsou data ke cteni na file descriptoru roury, nebo dokud nevyprsi timeout.
   */
  select ( g_Wakeup[0] + 1, &rd, NULL, NULL, &tv );
  return g_RecvSignal;
}

int main ( int argc, char * argv [] )
{
  pid_t   x;
  int     status, timeout;
  struct sigaction act;
  

  if ( argc < 3 
       || sscanf ( argv[1], "%d", &timeout ) != 1 )
  {
    printf ( "Usage: %s <timeout> <prog> [arg, arg, ...arg]\n", argv[0] );
    return 1;
  }


  /* Vlastni signal SIGCHLD
   */
  memset ( &act, 0, sizeof ( act ) );
  act . sa_handler = newSigChild;
  sigaction ( SIGCHLD, &act, NULL );

  /* Komunikace/synchronizace.
   */
  pipe ( g_Wakeup );

  x = fork ();
  if ( x < 0 )
  {
    fprintf ( stderr, "fork error\n" );
    return 1;
  }
  if ( x == 0 )
  {
    /* child */
    close ( g_Wakeup[0] );
    close ( g_Wakeup[1] );
    execvp ( argv[2], argv + 2 );
    exit ( 1 ); /* exec failed - e.g. file does not exist */
  }

  /*  cekame na regulerni dobehnuti
   */
  if ( ! waitSignalTimeout ( timeout ) )
  {
    /* Musime proces ukoncit. Nejprve pomoci SIGTERM...
     */
    printf ( "Sending SIGTERM\n" );
    kill ( x, SIGTERM );
    while ( ! waitSignalTimeout ( 1 ) )
    {
      /* Kdyz to nejde po dobrem ...
       */
      printf ( "Sending SIGKILL\n" );
      kill ( x, SIGKILL );
    }
  }

  /* Proces skoncil (dobrovolne, signalem). Lze volat wait.
   */
  waitpid ( x, &status, 0 );
  close ( g_Wakeup[0] );
  close ( g_Wakeup[1] );

  if ( WIFEXITED ( status ) )
    printf ( "Child process finished, code %d\n", WEXITSTATUS ( status ) );
  if ( WIFSIGNALED ( status ) )
    printf ( "Child process signaled, signal %d\n", WTERMSIG ( status ) );

  return 0;
}
