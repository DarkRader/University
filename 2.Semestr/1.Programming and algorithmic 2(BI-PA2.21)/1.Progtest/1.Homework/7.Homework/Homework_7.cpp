#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <optional>
#include <variant>
#include <any>
using namespace std;
#endif /* __PROGTEST__ */

template <typename T_, typename C_ = less<typename T_::value_type>>
class CIndex
{
  public:
     CIndex(const T_ & chain, const C_ & comp = C_ ()) : m_chain(chain), m_comp(comp) {}
    ~CIndex(void) {}
    set<size_t> search (const T_ & sekv) const
    {
        set<size_t> index;
        size_t sizeChain = m_chain.size();
        size_t sizeSekv = sekv.size();
        size_t *pi = new size_t[sizeSekv];
        
        if(sizeSekv == 0) {
            for(size_t i = 0; i < sizeChain; i++)
                index.insert(i);
        } else {
        insertPi(sekv, sizeSekv, pi);
        
        algorithmKMP(sekv, index, sizeChain, sizeSekv, pi);
        }
        
        delete [] pi;
        return index;
    }
    
private:
    T_ m_chain;
    C_ m_comp;
    
    void insertPi(const T_ & sekv, size_t size, size_t * Pi) const
    {
        size_t len = 0;
        Pi[0] = 0;
        size_t t = 1;
        auto it = sekv.begin();
        auto it2 = sekv.begin();
        it++;
        while(t < size)
        {
            if(((!m_comp(*it, *it2)) && (!m_comp(*it2, *it))) == true) {
                len++;
                it2++;
                Pi[t] = len;
                t++;
                it++;
            } else {
                if(len != 0) {
                    len = Pi[len - 1];
                    it2 = next(sekv.begin(), len);
                } else {
                    Pi[t] = 0;
                    t++;
                    it++;
                }
            }
        }
    }
    
    void algorithmKMP(const T_ & Sek, set<size_t> & index, size_t sizeChain, size_t sizeSekv, size_t * pi) const
    {
        size_t i = 0, j = 0;
        auto itI = m_chain.begin();
        auto itJ = Sek.begin();
        while(i < sizeChain)
        {
            if((!(m_comp(*itJ, *itI)) && !(m_comp(*itI, *itJ))) == true) {
                itJ++;
                itI++;
                j++;
                i++;
                
                if(j == sizeSekv) {
                    index.insert(i - j);
                    j = pi[j - 1];
                    itJ = next(Sek.begin(), j);
                }
                
            } else if(i < sizeChain) {
                if(j != 0) {
                    j = pi[j - 1];
                    itJ = next(Sek.begin(), j);
                } else {
                    i++;
                    itI++;
                }
            }
        }
    }
};
  
#ifndef __PROGTEST__
class CStrComparator
{
  public:
                   CStrComparator         ( bool caseSensitive )
      : m_CaseSensitive ( caseSensitive )
    {
    }
    bool           operator ()            ( const string & a, const string & b ) const
    {
      return m_CaseSensitive ? strcasecmp ( a . c_str (), b . c_str () ) < 0 : a < b ;
    }
    bool           m_CaseSensitive;
 };

bool               upperCaseCompare       ( const char & a, const char & b )
{
  return toupper ( a ) < toupper ( b );
}

int main ( void )
{
  CIndex <string> t0 ( "abcabcabc" );
  set<size_t> r0 = t0 . search ( "a" );
  assert ( r0 == ( set<size_t> { 0, 3, 6 } ) );
  set<size_t> r1 = t0 . search ( "abc" );
  assert ( r1 == ( set<size_t> { 0, 3, 6 } ) );
  set<size_t> r2 = t0 . search ( "abcabc" );
  assert ( r2 == ( set<size_t> { 0, 3 } ) );

  CIndex <string> t1 ( "abcababc" );
  set<size_t> r3 = t1 . search ( "a" );
  assert ( r3 == ( set<size_t> { 0, 3, 5 } ) );
  set<size_t> r4 = t1 . search ( "abc" );
  assert ( r4 == ( set<size_t> { 0, 5 } ) );
  set<size_t> r5 = t1 . search ( "abcabc" );
  assert ( r5 == ( set<size_t> {  } ) );

  CIndex <string> t2 ( "kokokokoskokosokos" );
  set<size_t> r6 = t2 . search ( "kos" );
  assert ( r6 == ( set<size_t> { 6, 11, 15 } ) );
  set<size_t> r7 = t2 . search ( "kokos" );
  assert ( r7 == ( set<size_t> { 4, 9 } ) );

  CIndex <string> t3 ( "aaaaaaau aaauaaaau" );
  set<size_t> r8 = t3 . search ( "aa" );
  assert ( r8 == ( set<size_t> { 0, 1, 2, 3, 4, 5, 9, 10, 13, 14, 15 } ) );
  set<size_t> r9 = t3 . search ( "aaa" );
  assert ( r9 == ( set<size_t> { 0, 1, 2, 3, 4, 9, 13, 14 } ) );
  set<size_t> r10 = t3 . search ( "aaaa" );
  assert ( r10 == ( set<size_t> { 0, 1, 2, 3, 13 } ) );

  CIndex <string> t4 ( "automatIc authentication automotive auTOmation raut" );
  set<size_t> r11 = t4 . search ( "auto" );
  assert ( r11 == ( set<size_t> { 0, 25 } ) );
  set<size_t> r12 = t4 . search ( "aut" );
  assert ( r12 == ( set<size_t> { 0, 10, 25, 48 } ) );
  set<size_t> r13 = t4 . search ( "tic" );
  assert ( r13 == ( set<size_t> { 16 } ) );
  set<size_t> r14 = t4 . search ( "trunk" );
  assert ( r14 == ( set<size_t> {  } ) );
  set<size_t> r15 = t4 . search ( "a" );
  assert ( r15 == ( set<size_t> { 0, 5, 10, 19, 25, 36, 41, 48 } ) );
  set<size_t> r16 = t4 . search ( "" );
  assert ( r16 == ( set<size_t> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 } ) );

  CIndex <string, bool(*)(const char &, const char & )> t5 ( "automatIc authentication automotive auTOmation raut", upperCaseCompare );
  set<size_t> r17 = t5 . search ( "auto" );
  assert ( r17 == ( set<size_t> { 0, 25, 36 } ) );
  set<size_t> r18 = t5 . search ( "aut" );
  assert ( r18 == ( set<size_t> { 0, 10, 25, 36, 48 } ) );
  set<size_t> r19 = t5 . search ( "tic" );
  assert ( r19 == ( set<size_t> { 6, 16 } ) );
  set<size_t> r20 = t5 . search ( "trunk" );
  assert ( r20 == ( set<size_t> {  } ) );
  set<size_t> r21 = t5 . search ( "a" );
  assert ( r21 == ( set<size_t> { 0, 5, 10, 19, 25, 36, 41, 48 } ) );
  set<size_t> r22 = t5 . search ( "" );
  assert ( r22 == ( set<size_t> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 } ) );

  CIndex <list<string>, CStrComparator> t6 ( list<string>{ "Hello", "world", "test", "this", "foo", "TEsT", "this", "done" }, CStrComparator ( false ) );
  set<size_t> r23 = t6 . search ( list<string>{"test", "this", "foo"} );
  assert ( r23 == ( set<size_t> { 2 } ) );
  set<size_t> r24 = t6 . search ( list<string>{"test", "this"} );
  assert ( r24 == ( set<size_t> { 2 } ) );

  CIndex <list<string>, CStrComparator> t7 ( list<string>{ "Hello", "world", "test", "this", "foo", "TEsT", "this", "done" }, CStrComparator ( true ) );
  set<size_t> r25 = t7 . search ( list<string>{"test", "this", "foo"} );
  assert ( r25 == ( set<size_t> { 2 } ) );
  set<size_t> r26 = t7 . search ( list<string>{"test", "this"} );
  assert ( r26 == ( set<size_t> { 2, 5 } ) );

  return 0;
}
#endif /* __PROGTEST__ */
