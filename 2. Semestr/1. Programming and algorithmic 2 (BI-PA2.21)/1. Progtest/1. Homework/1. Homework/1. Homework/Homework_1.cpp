#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

bool decompressFile ( const char * inFileName, const char * outFileName )
{
  // todo
  return false;
}

bool compressFile ( const char * inFileName, const char * outFileName )
{
  // keep this dummy implementation (no bonus) or implement the compression (bonus)
  return false;
}
#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1, const char * fileName2 )
{
  // todo
  return false;
}

int main ( void )
{
  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test0.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test0.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test1.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test1.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test2.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test2.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test3.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test3.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test4.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test4.orig", "tempfile" ) );

  assert ( ! decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/test5.huf", "tempfile" ) );


  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra0.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra0.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra1.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra1.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra2.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra2.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra3.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra3.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra4.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra4.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra5.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra5.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra6.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra6.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra7.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra7.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra8.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra8.orig", "tempfile" ) );

  assert ( decompressFile ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra9.huf", "tempfile" ) );
  assert ( identicalFiles ( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/1. Homework/1. Homework/1. Homework/tests/extra9.orig", "tempfile" ) );

  return 0;
}
#endif /* __PROGTEST__ */
