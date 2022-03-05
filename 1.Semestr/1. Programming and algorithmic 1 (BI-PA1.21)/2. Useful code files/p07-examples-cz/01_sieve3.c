#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*---------------------------------------------------------------------------*/
/* upravena verze. Pro ulozeni priznaku se vyuziva bitu, ne celych bajtu.
 * adresace bitu je v rezii programatora.
 */
int main ( int argc, char * argv [] )
{
  unsigned char * sieve;
  int             i, j, primes = 0, primeMax, limit, size;

  printf ( "Zadejte maximum:\n" );
  if ( scanf ( "%d", &primeMax ) != 1 || primeMax < 2 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  /*  alokace prostoru - 1/8 maxima. +7 zpusobi zaokrouhleni nahoru
   */
  size = ( primeMax + 7 ) / 8 ;

  sieve = (unsigned char *) malloc ( size * sizeof ( *sieve ) );
  if ( ! sieve )
  {
    printf ( "Chyba alokace.\n" );
    return 1;
  }
  limit = (int) sqrt ( primeMax );

  memset ( sieve, 0xff, size );
  sieve[0] &= ~3;

  for ( i = 2; i < primeMax; i ++ )
    if ( sieve[i >> 3] & (1 << (i & 7)) )
    {
      /* zapis je ekvivalentni: sieve[i / 8] & (1 << (i % 8)) )
       */
      if ( i > 2 ) 
        printf ( " " );
      printf ( "%d", i );
      primes ++;

      if ( i <= limit )
        for ( j = i * i; j < primeMax; j += i )
          sieve[j >> 3 ] &= ~ ( 1 << ( j & 7 ) );
    }
  printf ( "\nCelkem: %d prvocisel\n", primes );
  free ( sieve );
  return 0;
}
/*---------------------------------------------------------------------------*/
