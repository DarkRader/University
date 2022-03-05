#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*---------------------------------------------------------------------------*/
/* Eratosthenovo sito s dynamickou alokaci pole podle zadane meze.
 */
int main ( int argc, char * argv [] )
{
  char * sieve;
  int    i, j, primes = 0, primeMax, limit;

  printf ( "Zadejte  maximum:\n" );
  if ( scanf ( "%d", &primeMax ) != 1 || primeMax < 2 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }
  /*
   * alokace
   */
  sieve = (char *) malloc ( primeMax * sizeof ( *sieve ) );
  if ( ! sieve )
  {
    printf ( "Chyba alokace.\n" );
    return 1;
  }
  limit = (int) sqrt ( primeMax ); /* pripadne INT_MAX */

  for ( i = 0; i < primeMax; i ++ )
    sieve[i] = 1;

  sieve[0] = sieve[1] = 0;
  for ( i = 2; i < primeMax; i ++ )
    if ( sieve[i] )
    {
      if ( i > 2 ) 
        printf ( " " );
      printf ( "%d", i );
      primes ++;

      /* proskrtavat staci od i ^ 2. Ale i * i muze pretect rozsah int
       * proto zde kontrolujeme hodnotu i. Neni moudre porovnavat vypoctenou hodnotu
       * i * i - ta jiz mohla pretect.
       */
      if ( i <= limit )
        for ( j = i * i; j < primeMax; j += i )
          sieve[j] = 0;
    }
  printf ( "\nCelkem: %d prvocisel\n", primes );
  /*
   * uvolneni pameti
   */
  free ( sieve );
  return 0;
}
/*---------------------------------------------------------------------------*/
