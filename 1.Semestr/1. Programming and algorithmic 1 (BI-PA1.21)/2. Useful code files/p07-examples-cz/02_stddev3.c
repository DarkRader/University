#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Program nacita cisla ze std. vstupu. Uklada je do pole. Z hodnot pak 
 * vypocte prumer a smerodatnou odchylku.
 *
 * Toto reseni pouziva dynamickou alokaci pameti, snazi se vice vyuzivat funkce, 
 * ukazuje pouziti realloc
 */            
/*---------------------------------------------------------------------------*/
/** Funkce pro vypocet aritmetickeho prumeru
 *
 * @param[in] arr pole hodnot, pro ktere prumer pocitame
 * @param[in] nr pocet prvku v poli
 * @return aritmeticky prumer
 */
double average ( int * arr, int nr )
{
  double sum = 0;
  int i;

  for ( i = 0; i < nr; i ++ )
    sum += arr[i];
  return sum / nr;
} 
/*---------------------------------------------------------------------------*/
/** Funkce pro vypocet smerodatne odchylky
 *
 * @param[in] arr pole hodnot, pro ktere smerodatnou odchylku pocitame
 * @param[in] nr pocet prvku v poli
 * @return smerodatna odchylka
 */
double stdDeviation ( int * arr, int nr )
{
  double avg = 0, dev = 0;
  int i;

  for ( i = 0; i < nr; i ++ )
    avg += arr[i];
  avg /= nr;
  
  for ( i = 0; i < nr; i ++ )
    dev += (arr[i] - avg) * (arr[i] - avg);
   
  return sqrt ( dev / nr );
} 
/*---------------------------------------------------------------------------*/
/** Funkce nacte vstupni hodnoty do dynamicky alokovaneho pole. 
 *
 * @param[out] dataNr pocet prvku v nactenem poli
 * @return ukazatel na dynamicky alokovane pole, NULL pro chybu
 */
int * readInput ( int * dataNr )
{
  int * data = NULL, nr = 0, max = 0, x;

  while ( scanf ( "%d", &x ) == 1 )
  {
    if ( nr >= max )
    {
      /* nova velikost pole - vetsi o / vetsi nekolikrat podle aktualni velikosti
       */
      if ( max < 1000 ) 
        max += 100;
      else
        max += max / 2; 
      /* pro zvetseni pole lze pouzit std. funkci realloc. Ta umi stavajici pole 
       * natahnout (pokud to lze) nebo vytvori pole nove (vetsi) a obsah prekopiruje.
       * Vraci ukazatel na nove (vetsi) pole. Navic, pokud je puvodni ukazatel (prvni parametr)
       * NULL, funguje jako malloc. 
       */
      data = (int*)realloc ( data, max * sizeof ( *data ) );
    }  
    data[nr ++] = x;
  }
  if ( ! feof ( stdin ) )  
  {
    free ( data );
    return NULL;
  }  
  *dataNr = nr;
  return data;
}
/*---------------------------------------------------------------------------*/
int main( int argc, char * argv [] ) 
{          
  int * data;
  int   dataNr;

  printf ( "Hodnoty:\n" );
  data    = readInput ( &dataNr );
  if ( ! data )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  if ( dataNr > 0 )
  {
    printf ( "Prumer: %f\n", average ( data, dataNr ) ); 
    printf ( "Smerodatna odchylka: %f\n", stdDeviation ( data, dataNr ) );
  }
  free ( data ); /* nezapomeneme pole uvolnit */
  return 0; 
}
/*---------------------------------------------------------------------------*/
