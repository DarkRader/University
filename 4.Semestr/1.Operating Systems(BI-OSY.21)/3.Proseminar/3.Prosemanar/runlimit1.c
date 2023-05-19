/* Program ukazuje, jak se necha omezit max. doba behu jineho programu. Podobna technika
 * je pouzita v Progtestu pri spousteni testovanych programu.
 *
 * Zde uvedene reseni je nespravne - obsahuje race condition.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <wait.h>

/* Komunikace mezi signal handlerem a zbytkem programu
 */
 
int g_RecvSignal = 0;

/* Rodic dostane SIGCHLD pokud dobehne nejaky z jeho synu. Muze tim zareagovat (napr. volat wait)
 * Nase obsluha zde nastavi priznak: synovsky proces skoncil (g_RecvSignal).
 */
void               newSigChild                             ( int sig )
{
  g_RecvSignal = 1;
}


/* Cekani na synovsky proces:
 *   Nelze volat rovnou wait/waitpid. Pokud by se synovsky proces zacyklil, budeme cekat stale.
 *   Zavolame sleep(). POkud synovsky proces skonci, vyvola se signal SIGCHLD a cekani ve sleep ()
 *   se ukonci (tzv. interrupted system call). To se zde hodi - necekame vzdy plnou delku, ale jen
 *   nezbytne nutnou dobu.
 *
 *  ZDE je race condition. Pokud prijde SIGCHLD jeste pred tim nez zavolame sleep(), signal neprijde
 *   a vzdy cekame plnou dobu.
 */
int waitSignalTimeout ( int timeout )
{
  sleep ( timeout );
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
  x = fork ();
  if ( x < 0 )
  {
    fprintf ( stderr, "fork error\n" );
    return 1;
  }
  if ( x == 0 )
  {
    /* child */
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

  if ( WIFEXITED ( status ) )
    printf ( "Child process finished, code %d\n", WEXITSTATUS ( status ) );
  if ( WIFSIGNALED ( status ) )
    printf ( "Child process signaled, signal %d\n", WTERMSIG ( status ) );

  return 0;
}
