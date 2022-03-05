#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Program nacita cisla ze std. vstupu. Uklada je do pole. Z hodnot pak 
 * vypocte prumer a smerodatnou odchylku.
 *
 * Toto reseni pouziva dynamickou alokaci pameti, snazi se vice vyuzivat funkce
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
/** Funkce natahne pole na novou (vetsi) velikost.
 * 
 * @param[in,out] data puvodni pole / natazene pole
 * @param[in,out] max puvodni velikost / nova velikost pole
 */
void  resizeArray  ( int ** data, int * max )
{
  /* Funkce potrebuje manipulovat s hodnotou ukaatele na dynamicky alokovane pole. 
   * parametr data tedy musi byt i vystupni (aby se volajici dozvedel o adrese nove 
   * alokovaneho vetsho pole), nemuze byt pouze vstupni.
   * protoze chceme mit parametr typu int * vystupni, musime jej ve funkci deklarovat 
   * jako int ** (ridame 1 hvezdicku). 
   */
  int    * tmp, nr, i;

  /* Vylepseni: mala pole zvetsujeme "o neco". Je pravdepodobne, ze mala pole 
   * zustanou mala, tedy rezie pri zvetsovani "o neco" nebude vysoka.
   * Pokud uz je pole "velke", je pravdepodobne, ze bude "hodne velke". Zvetsovat 
   * takove pole "o neco" je rezijne nakladne (napr. pri zvetsovani o 100 prvku by 
   * se pro dosazeni velikosti 1000000 muselo realokovat 10000). Pro velka pole tedy 
   * pouzijeme strategii "nekolikrat", zde konkretne 1.5x (pro ilustraci: natahnuti na 
   * 1000000 prvku vyzaduje pouze 34 realokaci misto 10000).
   */
  nr = *max;
  if ( *max < 1000 ) 
    *max += 100;
  else
    *max += *max / 2; 

  tmp = (int*) malloc ( *max * sizeof ( *tmp ));

  /* Kopie obsahu. Puvodni velikost byla nr
   */
  for ( i = 0; i < nr; i ++ )
    tmp[i] = (*data)[i];  
  /* stare pole je jiz nepotrebne 
   */ 
  free ( *data ); 
  /* prehodime odkazy. NEBUDEME kopirovat pole zpet prvek po prvku !! 
   */ 
  *data = tmp;    
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
      resizeArray ( &data, &max );
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
