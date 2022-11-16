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
        m_file = nullptr;
        m_lenght = 0;
        m_position = 0;
    }

    ~CCurrentVersion(void)
    {
        if (m_file)
            delete[] m_file;
        m_file = nullptr;
        m_lenght = 0;
        m_position = 0;
    }

    uint32_t  newElements (const uint8_t   * src, uint32_t len)
    {

        uint32_t step = 0;
        uint8_t *tmp = nullptr;

        if((m_position == m_lenght) || (m_position + len > m_lenght)) {
            if(m_position == m_lenght)
               m_lenght += len;
            else if(m_position + len > m_lenght)
                m_lenght = m_position + len;
            tmp = new uint8_t[m_lenght];
            for (uint32_t i = 0; i < m_position; i++) {
                tmp[i] = m_file[i];
            }
            for(uint32_t i = m_position; i < m_position + len; i++)
            {
                tmp[i] = src[step];
                step++;
            }
            delete[] m_file;
            m_file = tmp;
        } else {
            for(uint32_t i = m_position; i < m_position + len; i++)
            {
                m_file[i] = src[step];

                step++;
            }
        }

        m_position += len;

        return step;
    }

    uint8_t returnElement (uint32_t pos)
    {
        return m_file[pos];
    }

    CCurrentVersion & operator =(const CCurrentVersion &newVersion)
    {
        if(this == &newVersion)
            return *this;
        if(m_file != nullptr)
            delete [] m_file;

        m_position = newVersion.m_position;
        m_lenght = newVersion.m_lenght;

        if(newVersion.m_file)
        {
            m_file = new uint8_t[m_lenght];

            for(uint32_t i = 0; i < m_lenght; i++)
                m_file[i] = newVersion.m_file[i];
        }
        else
            m_file = nullptr;

        return *this;
    }

    uint32_t getLenght(void) const
    {        
        return m_lenght;
    }
    
    uint32_t getPosition(void) const {return m_position;}
    
    void changePos(uint32_t pos)
    {
        m_position = pos;
    }

    void changeLenght(uint32_t del)
    {
        m_lenght = del;
    }

    // Debug method
    void printM_Db (void) const
    {

        for(size_t i = 0; i < m_lenght; i++)
            cout << m_file[i] +'0'-48<< endl;

        cout << "----------------------------" << endl;
    }


private:
    uint8_t *m_file;
    uint32_t m_lenght;
    uint32_t m_position;
};

class CFile
{
public:
    CFile                         ( void )
    {
        currentLen = 0;
        curPosMem = 0;
        member = nullptr;
        m_version = nullptr;
        
        if(!m_version) {
            currentLen++;
            m_version = new CCurrentVersion[currentLen];
            member = &m_version[curPosMem];
        }
    }
    ~CFile()
    {
        if (m_version)
            delete[] m_version;
        m_version = nullptr;
        currentLen = 0;
        curPosMem = 0;
        member = nullptr;
    }
    
    CFile(const CFile & x)
    {
        m_version = nullptr;
        currentLen = 0;
        curPosMem = 0;
        member = nullptr;
        
        curPosMem = x.curPosMem;
        currentLen = x.currentLen;
        
        if(!m_version) {
            currentLen++;
            m_version = new CCurrentVersion[currentLen];
            member = &m_version[curPosMem];
        }

        for(uint32_t i = 0; i < curPosMem + 1; i++)
            m_version[i] = x.m_version[i];
    }

    CFile & operator =(const CFile &newFile)
    {
        if(this == &newFile)
            return *this;
        if(m_version != nullptr)
        {
            delete[] m_version;
        }

        currentLen = newFile.currentLen;
        curPosMem = newFile.curPosMem;

        if(newFile.m_version)
        {
            m_version = new CCurrentVersion[currentLen];

            for(uint32_t i = 0; i < currentLen; i++)
                m_version[i] = newFile.m_version[i];
            
            member = &m_version[curPosMem];
        }
        else
            m_version = nullptr;

        return *this;
    }

//-------------------------------------------------------------------------------------------------------------
    bool                     seek                          ( uint32_t          offset )
    {
        if(!m_version) {
            currentLen++;
            m_version = new CCurrentVersion[currentLen];
            member = &m_version[curPosMem];
        }

        if(offset > member->getLenght())
            return false;

        member->changePos(offset);

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    uint32_t                 read                          ( uint8_t         * dst,
                                                             uint32_t          bytes )
    {
        if(!m_version) {
            currentLen++;
            m_version = new CCurrentVersion[currentLen];
            member = &m_version[curPosMem];
        }
        
        uint32_t tmp = member->getPosition();
        uint32_t returnBytes = 0;

        for(uint32_t i = 0; i < bytes && tmp < member->getLenght(); i++)
        {
            dst[i] = member->returnElement(tmp++);
            returnBytes++;
        }
        
        member->changePos(tmp);
        
        return returnBytes;
    }
//-------------------------------------------------------------------------------------------------------------
    uint32_t                 write                         ( const uint8_t   * src,
                                                             uint32_t          bytes )
    {
        if(!m_version) {
            currentLen++;
            m_version = new CCurrentVersion[currentLen];
            member = &m_version[curPosMem];
        }

        uint32_t len = member->newElements(src, bytes);

        return len;
    }

//-------------------------------------------------------------------------------------------------------------
    void                     truncate                      ( void )
    {
        if(!m_version) {
            currentLen++;
            m_version = new CCurrentVersion[currentLen];
            member = &m_version[curPosMem];
        }

        uint32_t del = member->getPosition();
        member->changeLenght(del);
    }
////-------------------------------------------------------------------------------------------------------------
    uint32_t                 fileSize                      ( void ) const
    {
        if(!m_version) {
            return 0;
        }
        return member->getLenght();
    }
////-------------------------------------------------------------------------------------------------------------
    void                     addVersion                    ( void )
    {
        if(!m_version) {
            currentLen++;
            m_version = new CCurrentVersion[currentLen];
            member = &m_version[curPosMem];
        }

            CCurrentVersion *tmp = nullptr;
            currentLen = currentLen + 1;
            tmp = new CCurrentVersion[currentLen];
            for (uint32_t i = 0; i < curPosMem + 1; i++)
                tmp[i] = m_version[i];
            delete [] m_version;
            m_version = tmp;

        m_version[curPosMem + 1] = m_version[curPosMem];

        curPosMem++;
        member = &m_version[curPosMem];
    }
////-------------------------------------------------------------------------------------------------------------
    bool                     undoVersion                   ( void )
    {
        if(!m_version) {
            return false;
        }

        if(curPosMem == 0)
            return false;

        member = &m_version[curPosMem - 1];
        curPosMem--;

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
void print (void) const
    {
        member->printM_Db();
    }
private:
    uint32_t currentLen;
    uint32_t curPosMem;
    CCurrentVersion * member;
    CCurrentVersion *m_version;
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
    assert ( f0 . fileSize () == 3 );
    assert ( writeTest ( f0, { 60, 70, 80 }, 3 ) );
    assert ( f0 . fileSize () == 6 );
    assert ( f0 . seek ( 2 ));
    assert ( writeTest ( f0, { 5, 4 }, 2 ) );
    assert ( f0 . fileSize () == 6 );
    assert ( f0 . seek ( 1 ));
    assert ( readTest ( f0, { 20, 5, 4, 70, 80 }, 7 ));
    assert ( f0 . seek ( 3 ));
    f0 . addVersion();
    assert ( f0 . seek ( 6 ));
    assert ( writeTest ( f0, { 100, 101, 102, 103 }, 4 ) );
    f0 . addVersion();
    assert ( f0 . seek ( 5 ));
    CFile f1 ( f0 );
    f0 . truncate ();
    assert ( f0 . seek ( 0 ));
    assert ( readTest ( f0, { 10, 20, 5, 4, 70 }, 20 ));
    assert ( f0 . undoVersion () );
    assert ( f0 . seek ( 0 ));
    assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80, 100, 101, 102, 103 }, 20 ));
    assert ( f0 . undoVersion () );
    assert ( f0 . seek ( 0 ));
    assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80 }, 20 ));
    assert ( !f0 . seek ( 100 ));
    assert ( writeTest ( f1, { 200, 210, 220 }, 3 ) );
    assert ( f1 . seek ( 0 ));
    assert ( readTest ( f1, { 10, 20, 5, 4, 70, 200, 210, 220, 102, 103 }, 20 ));
    assert ( f1 . undoVersion () );
    assert ( f1 . undoVersion () );
    assert ( readTest ( f1, { 4, 70, 80 }, 20 ));
    assert ( !f1 . undoVersion () );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

