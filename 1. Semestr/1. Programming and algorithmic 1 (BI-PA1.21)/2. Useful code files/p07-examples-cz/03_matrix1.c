#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/
/** Uvolneni pameti alokovane pro matici. Protoze vlastni dynamicky alokovana pole
 * neposkytuji informaci o sve velikosti, musime predat druhy parametr - pocet
 * radek matice.
 *
 * @param[in] mat matce cisel
 * @param[in] r pocet radek matice
 *
 */
void freeMatrix ( int ** mat, int r )
{
  int       i;

  for ( i = 0; i < r; i ++ )
    free ( mat[i] );
  free ( mat );
}
/*---------------------------------------------------------------------------*/
/** Alokace 2D matice. Dynamicky alokuje potrebny pocet radek a pole odkazu na radky.
 * Pokud alokace selze (neni dostatek pameti), vraci NULL
 *
 * @param[in] r pocet radek
 * @param[in] c pocet sloupcu
 * @return alokovana matice, nebo NULL pro chybu
 */
int ** allocMatrix ( int r, int c )
{
  int ** res;
  int    i;

  res = (int **) malloc ( sizeof ( *res ) * r );
  if ( ! res ) return ( NULL );
  
  for ( i = 0; i < r; i ++ )
  {
    res[i] = (int *) malloc ( sizeof ( *res[i] ) * c );
    if ( ! res[i] )
    {
      /* Alokace nektere radky se nezdarila (dosla pamet). Pozor - predesle,
       * jiz alokovane radky je potreba uvolnit. Zavolame freeMatrix,
       * kde pocet radek matice bude nastaven na i (ty radky jiz drive alokovane)
       */
      freeMatrix ( res, i );
      return ( NULL );
    }
  }
  return ( res );
}
/*---------------------------------------------------------------------------*/
/** Zobrazeni obsahu matice
 *
 * @param[in] mat matice
 * @param[in] r pocet radek
 * @param[in] c pocet sloupcu
 */
void printMatrix ( int ** mat, int r, int c )
{
  int       i, j;

  for ( i = 0; i < r; i ++ )
  {
    for ( j = 0; j < c; j ++ )
    {
      if ( j ) 
        printf ( " " ); /* mezera nebude pred prvnim prvkem na radce */
      printf ( "%d", mat[i][j] );
    }
    printf ( "\n" );
  }
}
/*---------------------------------------------------------------------------*/
/** Nacteni matice ze std. vstupu. Matice je dynamicky alokovana podle volby uzivatele
 * a jsou do ni ze std vstupu prectene hodnoty.
 *
 * @param[out] r pocet radek vytvorene matice
 * @param[out] c pocet sloupcu matice
 * @return alokovana a vyplnena matice, nebo NULL pokud nacitani selze
 */
int ** readMatrix ( int * r, int * c )
{
  int ** res;
  int    i, j;

  printf ( "Zadejte pocet radek a sloupcu:\n" );
  /* scanf zde NEMA r a c s referenci(&r, &c). r a c jiz jsou ukazatele,
   * nejedna se o cisla.
   */
  if ( scanf ( "%d %d", r, c ) != 2 || *r <= 0 || *c <= 0 ) return ( NULL );

  res = allocMatrix ( *r, *c );
  if ( ! res ) return ( NULL );

  printf ( "Zadejte prvky matice:\n" );
  for ( i = 0; i < *r; i ++ )
    for ( j = 0; j < *c; j ++ )
    {
      if ( scanf ( "%d", &res[i][j] ) != 1 )
      {
        freeMatrix ( res, *r );
        return ( NULL );
      }
    }
  return res;
}
/*---------------------------------------------------------------------------*/
/** Porovna dve radky matice. 
 *
 * @param[in] r1 radka matice #1
 * @param[in] r2 radka matice #2
 * @param[in] c pocet prvku na radce 
 * @return 1, pokud jsou radky shodne, 0 pokud jsou odlisne
 */
int equalRows ( int * r1, int *r2, int c )
{
  while ( c -- )
    if ( *r1 ++ != *r2 ++ )
      return 0;
  return 1;
}
/*---------------------------------------------------------------------------*/
/** Vyhledani, zda jsou v matici duplicitni radky. Funkce porovna vsechny dvojice 
 * radek v matici. 
 *
 * @param[in] mat testovana matice
 * @param[in] r pocet radek matice
 * @param[in] c pocet sloupcu matice
 * @return pokud je v matici alespon jeden duplicitni radek, vraci funkce 1. Pokud
 *  matice obsahuje pouze unikatni radky, vraci 0.
 */
int hasDupRows ( int ** mat, int r, int c )
{
  int i, j;
  
  /* Porovnava radku i=0 s radkami j = 1,
   * 2, 3, .. r-1. Pak radku i = 1 s radkami j = 2, 3, 4, ... r-1. Celkem provede
   * (n^2-n)/2 porovnani radek.             
   */
  for ( i = 0; i < r; i ++ )
    for ( j = i + 1; j < r; j ++ )
      if ( equalRows ( mat[i], mat[j], c ) )
        return 1;

  return 0;
}
/*---------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
{
  int ** mat;
  int    rows, cols;

  mat = readMatrix ( &rows, &cols );
  if ( ! mat )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  printMatrix  ( mat, rows, cols );
  
  if ( hasDupRows ( mat, rows, cols ) )
    printf ( "V matici jsou duplicitni radky.\n" );
  else
    printf ( "V matici nejsou duplicitni radky.\n" );

  freeMatrix  ( mat, rows );
  return 0;
}
/*---------------------------------------------------------------------------*/
