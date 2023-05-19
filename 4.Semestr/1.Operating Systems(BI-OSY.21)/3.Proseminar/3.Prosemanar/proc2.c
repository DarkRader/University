/* Program simuluje "dlouhy narocny vypocet" - zde nekonecnou smycku. Zaroven nastavuje
 * signal handlery tak ze signaly na ukonceni ignoruje. Musi byt odstranen signalem SIGKILL
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


void newSigInt ( int sigNum )
{
  printf ( "Ignoring signal %d\n", sigNum );
}


int main ( int argc, char * argv [] )
{
  struct sigaction act;

  memset ( &act, 0, sizeof ( act ) );
  act . sa_handler = newSigInt;
  sigaction ( SIGINT, &act, NULL );
  sigaction ( SIGTERM, &act, NULL );

  printf ( "Computing...\n" );
  while ( 1 )
  {
  }
  return 0;
}
