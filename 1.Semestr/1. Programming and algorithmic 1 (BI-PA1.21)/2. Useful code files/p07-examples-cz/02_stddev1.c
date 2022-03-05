#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Program nacita cisla ze std. vstupu. Uklada je do pole. Z hodnot pak 
 * vypocte prumer a smerodatnou odchylku.
 *
 * Toto reseni pouziva dynamickou alokaci pameti, neni prilis hezke 
 * z poheldu cleneni do funkci.
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
int main( int argc, char * argv [] ) 
{          
  int * data;
  int   dataNr, dataMax, x;
  
  /* data bude nase dynamicky alokovane pole
   * dataNr bude pocet prvku v tomto poli vyplnenych
   * dataMax bude alokovana velikost (pocet prvku). Musime 
   * dodrzet dataNr <= dataMax
   *
   * na poctaku je pole prazdne
   */ 
  data    = NULL;
  dataNr  = 0;
  dataMax = 0;
  printf ( "Hodnoty:\n" );
  while ( scanf ( "%d", &x ) == 1 )
  {
    if ( dataNr >= dataMax )
    {
      /* cela kapacita pole je jiz vyplnena prvky (na pocatku je kapacita 0, 
       * tedy take "zaplneno"), musime pole rozsirit.
       */
      int    * tmp, i;
      /* Pole zvetsime o 100 prvku, ty zatim budou nevyuzite. 
       * Pokud bychom pole zvetsovali pouze po 1 prvku, meli bychom na 
       * "natahovani" pole obrovskou rezii.
       */
      dataMax += 100;
      tmp = (int*) malloc ( dataMax * sizeof ( *tmp ));
    
      /* Kopie obsahu. 
       */
      for ( i = 0; i < dataNr; i ++ )
        tmp[i] = data[i];
      /* stare pole je jiz nepotrebne 
       */ 
      free ( data ); 
      /* prehodime odkazy. NEBUDEME kopirovat pole zpet prvek po prvku !! 
       */ 
      data = tmp;    
    }
    data[dataNr ++] = x;
  }
  if ( ! feof ( stdin ) )
  {
    printf ( "Nespravny vstup.\n" );
    free ( data ); /* !! uvolnit pamet */
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
