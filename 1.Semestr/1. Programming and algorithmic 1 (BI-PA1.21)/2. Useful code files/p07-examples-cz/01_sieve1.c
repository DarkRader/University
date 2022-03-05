#include <stdio.h>

#define PRIME_MAX   10000

/*---------------------------------------------------------------------------*/
/* Eratosthenovo sito - pro fixni horni mez.
 */
int main ( int argc, char * argv [] )
{
  char   sieve[PRIME_MAX];
  int    i, j, primes = 0;

  for ( i = 0; i < PRIME_MAX; i ++ )
   sieve[i] = 1;
  
  /* 0 a 1 nejsou prvocisla
   */
  sieve[0] = sieve[1] = 0;
  for ( i = 2; i < PRIME_MAX; i ++ )
    if ( sieve[i] )
    {
      /* cislo i nebylo skrtnute, je tedy prvocislem 
       */
      if ( i > 2 ) 
        printf ( " " );
      printf ( "%d", i );
      primes ++;
      /* Vyskrtame nasobky i, pocinaje hodnotou 2 * i 
       */
      for ( j = 2 * i; j < PRIME_MAX; j += i )
        sieve[j] = 0;
    }
  printf ( "\nV intervalu <1,%d> je celkem %d prvocisel\n", PRIME_MAX-1, primes );
  return 0;
}
/*---------------------------------------------------------------------------*/
