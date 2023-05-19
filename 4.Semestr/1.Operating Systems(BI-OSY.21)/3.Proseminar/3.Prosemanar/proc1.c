/* fork - exec ukazka. Program spusti prikaz sleep 30 bud 5x sekvencne za sebou,
 * nebo 5x paralelne.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

pid_t runCommand ( )
{
  pid_t  x;

  x = fork ();
  if ( x < 0 )
  {
    fprintf ( stderr, "fork() error\n" );
    return x;
  }

  if ( x == 0 )
  {
    /* child process */
    execlp ( "sleep", "sleep", "30", (char*) NULL );
    exit ( 1 ); /* if reached, exec failed */
  }
  return x;
}


int main ( int argc, char * argv [] )
{
  pid_t   seq;
  pid_t   par[5];
  int     i, dummy;

 /* sekvencni provadeni synovskych procesu. Odpovida shell zapisu:
  * > sleep 30; sleep 30; sleep 30; sleep 30; sleep 30
  */
  for ( i = 0; i < 5; i ++ )
  {
    printf ( "sleep 30\n" );
    seq = runCommand ();
    waitpid ( seq, &dummy, 0 );
  }
  printf ( "done\n" );

 /* paralelni provadeni synovskych procesu. Odpovida shell zapisu:
  * > sleep 30 &
  * > sleep 30 &
  * > sleep 30 &
  * > sleep 30 &
  * > sleep 30 &
  * > wait
  */
  for ( i = 0; i < 5; i ++ )
  {
    printf ( "sleep 30\n" );
    par[i] = runCommand ();
  }
  for ( i = 0; i < 5; i ++ )
    waitpid ( par[i], &dummy,  0 );
  printf ( "done\n" );

  return 0;
}

