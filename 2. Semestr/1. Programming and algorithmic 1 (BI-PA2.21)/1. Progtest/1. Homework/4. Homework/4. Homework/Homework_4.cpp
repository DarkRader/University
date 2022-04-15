#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

class CCurrentVersion
{
public:
    
    CCurrentVersion(void)
    {
        currentSize = 100;
        m_file = new uint32_t[currentSize];
        m_lenght = 0;
        m_position = 0;
    }
    
    CCurrentVersion(const CCurrentVersion & member)
    {
        
        //delete [] m_file;
        
        currentSize = member.currentSize;
        m_position = member.m_position;
        m_lenght = member.m_lenght;
        
        if(member.m_file)
        {
            m_file = new uint32_t[currentSize];
            
            for(uint32_t i = 0; i < m_lenght; i++)
                m_file[i] = member.m_file[i];
        }
        else
            m_file = 0;
        
//        currentSize = x.currentSize;
//        m_position = x.m_position;
//        m_lenght = x.m_lenght;
//
//        if(x.m_file)
//        {
//            m_file = new uint32_t[currentSize];
//
//            for(uint32_t i = 0; i < m_lenght; i++)
//                m_file = &x.m_file[i];
//        }
//        else
//            m_file = 0;
    }
    
    uint32_t  newElements (const uint8_t   * src, uint32_t len)
    {
        uint32_t *tmp = nullptr;
        if(m_lenght + len > currentSize) {
            currentSize *= 2;
            tmp = new uint32_t[currentSize];
            for (uint32_t i = 0; i < m_lenght; i++) {
                tmp[i] = m_file[i];
            }
            delete[] m_file;
            m_file = tmp;
        }
        
        if(m_position == m_lenght)
            m_lenght += len;
        else if(m_position + len > m_lenght)
            m_lenght = m_position;
        
        uint32_t step = 0;
        
        for(uint32_t i = m_position; i < m_position + len; i++)
        {
            m_file[i] = src[step];
            
            step++;
        }
            
        m_position += len;
        
        return step;
    }
    
    uint32_t returnElement (uint32_t pos)
    {
        return m_file[pos];
    }
    
    void deepCopy (void)
    {
        m_file[3] = 100;
        m_file[4] = 124;
    }
    
    //void delete (
    
//    CCurrentVersion & operator =(const CCurrentVersion &newVersion)
//    {
//        if(this == &newVersion)
//            return *this;
//
//        delete [] m_file;
//
//        currentSize = newVersion.currentSize;
//        m_position = newVersion.m_position;
//        m_lenght = newVersion.m_lenght;
//
//        if(newVersion.m_file)
//        {
//            m_file = new uint32_t[currentSize];
//
//            for(uint32_t i = 0; i < m_lenght; i++)
//                m_file = &newVersion.m_file[i];
//        }
//        else
//            m_file = 0;
//
//        return *this;
//    }
    
    uint32_t getLenght(void) const {return m_lenght;}
    uint32_t getPosition(void) const {return m_position;}
    void changePos(uint32_t pos)
    {
        m_position = pos;
    }
    
    void changeLenght(uint32_t del)
    {
        m_lenght -= del;
    }
    
    void printM_Db (void) const
    {

        for(size_t i = 0; i < m_lenght; i++)
            cout << m_file[i] << endl;
        
        cout << "----------------------------" << endl;
    }
    
    
private:
    uint32_t currentSize;
    uint32_t *m_file;
    uint32_t m_lenght;
    uint32_t m_position;
};

class CFile
{
  public:
                             CFile                         ( void )
                             // copy cons, dtor, op=
    {}
//    CFile(const CFile & x)
//    {
//
//        delete [] member;
        
//        currentSize = member.currentSize;
//        m_position = member.m_position;
//        m_lenght = member.m_lenght;
        
//        if(x.member)
//        {
//            member = new uint32_t[currentSize];
//
//            for(uint32_t i = 0; i < m_lenght; i++)
//                m_file[i] = member.m_file[i];
//        }
//        else
//            member = 0;
    //}
//-------------------------------------------------------------------------------------------------------------
    bool                     seek                          ( uint32_t          offset )
    {
        if(offset > member->getLenght())
            return false;
        
        member->changePos(offset);

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    uint32_t                 read                          ( uint8_t         * dst,
                                                             uint32_t          bytes )
    {
        int returnPos = 0;
        
        for(uint32_t i = member->getPosition(); i < member->getLenght(); i++)
        {
            dst[returnPos] = member->returnElement(i);
            //uint32_t y = member->returnElement(i);
            returnPos++;
            bytes--;
            
            if(bytes == 0)
                break;
        }
        
//        uint32_t x1 = dst[0];
//        uint32_t x2 = dst[1];
//        uint32_t x3 = dst[2];
//        uint32_t x4 = dst[3];
//        uint32_t x5 = dst[4];
//        uint32_t x6 = dst[5];
        
        return returnPos;
    }
//-------------------------------------------------------------------------------------------------------------
    uint32_t                 write                         ( const uint8_t   * src,
                                                             uint32_t          bytes )
    {
        if(member == nullptr)
            member = new CCurrentVersion;

        uint32_t len = member->newElements(src, bytes);
        
        return len;
    }
    
    // addVersion() : newCurrentVersion = member.deepCopy();
//-------------------------------------------------------------------------------------------------------------
    void                     truncate                      ( void )
    {
        uint32_t del = member->getPosition();
        member->changeLenght(del);
    }
////-------------------------------------------------------------------------------------------------------------
    uint32_t                 fileSize                      ( void ) const
    {
        return member->getLenght();
    }
////-------------------------------------------------------------------------------------------------------------
    void                     addVersion                    ( void )
    {
        oldVersion = new CCurrentVersion(*member);
        
//        member->deepCopy();
        
        CCurrentVersion tmp = *member;
        member = oldVersion;
        oldVersion = &tmp;
//
//        uint32_t  m = member->returnElement(3);
//        uint32_t  m1 = member->returnElement(4);
//
//        uint32_t  n = oldVersion->returnElement(3);
//        uint32_t  n1 = oldVersion->returnElement(4);
        
    }
////-------------------------------------------------------------------------------------------------------------
    bool                     undoVersion                   ( void )
    {
        //CCurrentVersion tmp = *member;
        member = oldVersion;
        //oldVersion = &tmp;
        
        //delete [] oldVersion;
        


        return true;
    }
//-------------------------------------------------------------------------------------------------------------
void print (void) const
    {
        member->printM_Db();
    }
  private:
    CCurrentVersion * member = nullptr;
    CCurrentVersion * oldVersion = nullptr;
};

#ifndef __PROGTEST__
bool               writeTest                               ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          wrLen )
{
  return x . write ( data . begin (), data . size () ) == wrLen;
}
//-------------------------------------------------------------------------------------------------------------
bool               readTest                                ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          rdLen )
{
  uint8_t  tmp[100];
  uint32_t idx = 0;

  if ( x . read ( tmp, rdLen ) != data . size ())
    return false;
  for ( auto v : data )
    if ( tmp[idx++] != v )
      return false;
  return true;
}

int main ( void )
{
  CFile f0;

  assert ( writeTest ( f0, { 10, 20, 30 }, 3 ) );
    f0.print();
  assert ( f0 . fileSize () == 3 );
  assert ( writeTest ( f0, { 60, 70, 80 }, 3 ) );
    f0.print();
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 2 ));
  assert ( writeTest ( f0, { 5, 4 }, 2 ) );
    f0.print();
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 1 ));
  assert ( readTest ( f0, { 20, 5, 4, 70, 80 }, 7 ));
  assert ( f0 . seek ( 3 ));
  f0 . addVersion();
  assert ( f0 . seek ( 6 ));
    f0.print();
  assert ( writeTest ( f0, { 100, 101, 102, 103 }, 4 ) );
  f0 . addVersion();
  assert ( f0 . seek ( 5 ));
  CFile f1 ( f0 );
    f0.print();
  f0 . truncate ();
    f0.print();
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70 }, 20 ));
  assert ( f0 . undoVersion () );
  assert ( f0 . seek ( 0 ));
    f0.print();
  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80, 100, 101, 102, 103 }, 20 ));
//  assert ( f0 . undoVersion () );
//  assert ( f0 . seek ( 0 ));
//  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80 }, 20 ));
//  assert ( !f0 . seek ( 100 ));
//  assert ( writeTest ( f1, { 200, 210, 220 }, 3 ) );
//  assert ( f1 . seek ( 0 ));
//  assert ( readTest ( f1, { 10, 20, 5, 4, 70, 200, 210, 220, 102, 103 }, 20 ));
//  assert ( f1 . undoVersion () );
//  assert ( f1 . undoVersion () );
//  assert ( readTest ( f1, { 4, 70, 80 }, 20 ));
//  assert ( !f1 . undoVersion () );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
