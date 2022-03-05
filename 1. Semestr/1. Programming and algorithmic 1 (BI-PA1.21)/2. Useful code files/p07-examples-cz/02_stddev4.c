#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Program nacita cisla ze std. vstupu. Uklada je do pole. Z hodnot pak 
 * vypocte prumer a smerodatnou odchylku.
 *
 * Toto reseni ukazuje, ze pro vypocet prumeru a smerodatne odchylky neni 
 * pole vlastne vubec potreba.
 */            
/*---------------------------------------------------------------------------*/
/** Funkce zpracuje std. vstup a vypocte prumer a smerodatnou odchylku.
 *
 * @param[out] avg vypocteny prumer
 * @param[out] dev vypoctena smerodatna odchylka
 * @return 1 pro uspech, 0 pro chybu 
 */
int statInput ( double * avg, double * dev )
{
  int nr = 0, x;
  double sum = 0, sumsq = 0;

  while ( scanf ( "%d", &x ) == 1 )
  {
    sum += x;
    sumsq += (double)x * x;
    nr ++;
  }
  if ( ! feof ( stdin ) || nr == 0 ) 
    return 0;
  *avg = sum / nr;
  *dev = sqrt ( sumsq / nr - *avg * *avg );
  return 1;
}
/*---------------------------------------------------------------------------*/
int main( int argc, char * argv [] ) 
{          
  double avg, dev;
  
  printf ( "Hodnoty:\n" );
  if ( ! statInput ( &avg, &dev ) )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }
  printf ( "Prumer: %f\n", avg ); 
  printf ( "Smerodatna odchylka: %f\n", dev );
  return 0; 
}
/*---------------------------------------------------------------------------*/
