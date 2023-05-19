/* Program aproximuje cislo pi metodou Monte-Carlo. Cim delsi cas aproximace probiha,
 * tim je hodnota presnejsi. Po stisku Ctrl-C nebo SIGTERM je vypocet ukoncen a je zobrazena
 * dosazena hodnota aproximace.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

long long int g_Inside = 0, g_Total = 0;

void newSigInt ( int sigNum )
{
  printf ( "Approximation: %.8f\n", 4.0 * g_Inside / g_Total );
  printf ( "Samples: %lld\n", g_Total );
  exit ( 0 );
}


int main ( int argc, char * argv [] )
{
  struct sigaction act;

  memset ( &act, 0, sizeof ( act ) );
  act . sa_handler = newSigInt;
  sigaction ( SIGINT, &act, NULL );
  sigaction ( SIGTERM, &act, NULL );

  printf ( "Approximating...\n" );

  while ( 1 )
  {
    double x = 1.0 * rand () / RAND_MAX;
    double y = 1.0 * rand () / RAND_MAX;
  
    if ( x * x + y * y <= 1 ) g_Inside ++;
    g_Total ++;
  }
  return 0;
}

