/* Program nacte seznam studentu. Kazdy student ma zadane jmeno (max 49 znaku) a pocet 
 * ziskanych bodu. Program nalezne modus (nejcastejsi hodnotu poctu bodu) a vypise studenty,
 * kteri tohoto hodnoceni dosahli.
 *
 * Protoze pocet studentu na vstupu neni dopredu znamy, musi program prizpusobovat velikost pole 
 * v prubehu nacitani vstupu (natahovani pole).
 *
 * Nejcastejsich hodnot muze byt vice (vice stejne cetnych), program pracuje pouze s jednou z nich.
 *
 * Program demonstruje pouziti struktur, nacitani do pole a zmenu velikosti pole (natahovani).
 *
 * V teto verzi program pracuje spravne, pouziva efektivni algoritmy jak pro alokace, tak pro hledani modusu.
 *
 *************************************************************************************************
 * Tato verze vylepsuje algoritmus hledani nejcastejsi hodnoty. Misto puvodniho kvadratickeho reseni 
 * pole seradime a nasledne linearne projdeme. Slozitost se snizi na  n log (n)
 */
 
#include <stdio.h>
#include <stdlib.h>  /* malloc, free, qsort */
#include <string.h>  /* strncpy */

typedef struct TStudent
{
  char m_Name[50]; /* 49 znaku + ukoncujici 0 */
  int  m_Points;
} TSTUDENT; 

/*-----------------------------------------------------------------------------------------------*/
/** Funkce nacte zadana vstupni data do dynamicky alokovaneho pole.
 *  @param[out] n pocet nactenych studentu
 *  @return dynamicky alokovane pole s nactenymi studenty, NULL pro chybu
 *  @note vracene alokovane pole je potreba uvolnit pomoci free ()
 */
TSTUDENT * readStudents ( int * n )
{
  /* zatim nic nealokujeme, alokovat budeme az v okamziku, kdy to bude doopravdy potreba */
  TSTUDENT * data = NULL;
  int max = 0; /* alokovany prostor, *n <= max */
  char name[50];
  int points, res;
  
  *n = 0; /* vyuzity prostor v poli */

  /* %49s - nacte se maximalne 49 znaku jmena + ukoncujici 0
   * scanf tedy nikdy nebude psat mimo meze promenne name
   */
  while ( (res = scanf ( "%49s %d", name, &points ) ) == 2 )
  {
    /* Podarilo se nacist, je potreba ulozit. Pokud pole nema dostatecnou rezervu:
     *  - alokujeme nove vetsi pole
     *  - zkopirujeme obsah
     *  - uvolnime puvodni mensi pole
     *  - prehodime odkazy
     */
    if ( *n >= max )
    { 
      /* Je potreba pole zvetsit. Muzeme zvolit:
       * - konzervativni strategii (vzdy pole  zvetsime napr. o 100 prvku). Setrime mistem 
       *   (nevyuzito je vzdy max 99 pozic), ale pole natahujeme relativne casto. To bude 
       *   vadit hlavne u dlouhych poli
       * - agresivni pristup (pole vzdy zvetsime x krat). Setrime rezii na kopirovani, ale 
       *   muzeme plytvat pameti. Navic takto nelze zacit od velikosti max = 0
       *
       * Zvolime kombinaci obou postupu: mala pole budeme zvetsovat o 10, velka 1.5 krat. 
       * Konstanta 1.5 je spise nizka, velikost pole neporoste extremne rychle.
       */
      max += ( max < 100 ) ? 10 : max / 2;
      /* Vlastni zvetseni bloku:
       *  - pri prvni alokaci je data == NULL, podle specifikace pak realloc funguje 
       *    stejne jako malloc,
       *  - pri naslednych volanich pak realloc upravuje velikost drive alokovaneho bloku
       */ 
      data = (TSTUDENT *) realloc ( data, max * sizeof ( *data ) );
      /* Toto pouziti realloc neni uplne spravne, pokud funkce realloc selze, prepise se 
       * puvodni odkaz data na hodnotu NULL, puvodni data nebudou dostupna a nepujde je ani
       * uvolnit. Zcela spravne by bylo:
       *
       * TSTUDENT * tmp = realloc ( data, max * sizeof ( *data ) );
       * if ( ! tmp ) { free ( data ); return NULL; }
       * data = tmp;
       */
    }
     
    /* ulozime nove nacteneho studenta */
    /* bezpecne kopirovani jmena - s omezenim max delky  */
    strncpy ( data[ *n ] . m_Name, name, sizeof ( data[ *n ] . m_Name ) );
    data[ *n ] . m_Points = points;
    (*n)++; /* nefunguje *n++ (posouva ukazatel), funguje ++*n; */
  }
  
  if ( res != EOF ) 
  { /* chyba nacitani, napr. spatny format cisla */
    free ( data );
    return NULL; /* indikace chyby */
  } 
  return data; /* ok nacteno */
}
/*-----------------------------------------------------------------------------------------------*/
/** Pomocna funkce pro porovnani v qsort(). Radi hodnoty podle poctu ziskanych bodu
 * @param[in] a prvni student pro porovnani
 * @param[in] b druhy student pro porovnani
 * @return < 0 pro  a<b; 0 pro a==b; >0 pro a > b, kriteriem je pocet ziskanych bodu
 */
int studentCmp ( const TSTUDENT * a, const TSTUDENT * b )
{
  return ( b -> m_Points < a -> m_Points ) - ( a -> m_Points < b -> m_Points );
}
/*-----------------------------------------------------------------------------------------------*/
/** Funkce nalezne modus poctu bodu v predanem poli studentu. Pokud existuje vice moznosti (vice 
 *   hodnot se stejnou cetnosti), funkce pouzije prvni takovou hodnotu.
 *  @param[in,out] data pole s vyplnenymi studenty
 *  @param[in] n pocet studentu v predanem poli
 *  @return nalezeny modus 
 *  @note vylepsena implementace, ktera seradi predane pole 
 */
int findModus ( TSTUDENT * data, int n )
{
  int modus, cnt, maxCnt, i;

  /* stejne hodnoty bodu budou "u sebe" */
  qsort ( data, n, sizeof (*data), (int (*)(const void *, const void *)) studentCmp );

  
  modus  = data[0] . m_Points;
  cnt    = 1; /* delka sekvence stejnych bodu */
  maxCnt = 1;
  
  for ( i = 2; i < n; i ++ )
    if ( data[i] . m_Points == data[i - 1] . m_Points ) /* shoda s predeslym - sekvence stejnych bodu pokracuje */
      cnt ++;
    else
    { /* zmena - byla predesla sekvnce nejdelsi */
      if ( cnt > maxCnt )
      {
        maxCnt = cnt;
        modus = data[i-1] . m_Points;
      }
      cnt = 1; 
    }  
  
  /* pokud byla posledni sekvence na konci pole nejdelsi */
  if ( cnt > maxCnt )
    modus = data[n-1] . m_Points;
  
  return modus;    
}
/*-----------------------------------------------------------------------------------------------*/
/** Funkce zobrazi studenty, kteri dosahli prave zadanehopoctu bodu.
 * @param[in] data pole se studenty
 * @param[in] n pocet studentu v poli
 * @param[in] modus filtr na pocet bodu (zobrazi studenty s timto poctem bodu
 * @note funcke nic nevrasci, pouze zobrazuje na stdout
 */
void printStudents ( TSTUDENT * data, int n, int modus )
{
  int i;
  
  for ( i = 0; i < n; i ++ )
    if ( data[i] . m_Points == modus )
      printf ( "%s\n", data[i] . m_Name );
} 
/*-----------------------------------------------------------------------------------------------*/
int main ( void )
{
  int n, modus;
  TSTUDENT * data; 
 
  printf ( "Vysledky:\n" );
  data = readStudents ( &n );
  if ( ! data )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }
  modus = findModus ( data, n );
  printf ( "Modus: %d\n", modus );
  printStudents ( data, n, modus );
  free ( data );
  return 0; 
}
