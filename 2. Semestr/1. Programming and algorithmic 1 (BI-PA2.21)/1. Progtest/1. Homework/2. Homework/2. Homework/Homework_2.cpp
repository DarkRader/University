#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CVATRegister
{
  public:
//-------------------------------------------------------------------------------------------------------------
                   CVATRegister   ( void )
    {
                       
    }

                   ~CVATRegister  ( void )
    {
                       
    }
//-------------------------------------------------------------------------------------------------------------
    bool          newCompany     ( const string    & name,
                                   const string    & addr,
                                   const string    & taxID )
    {
        string lowerName = name, lowerAddr = addr;

        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
                
        vector <TCompany> :: iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
       if(index != m_Db.end() && index->lowerName == lowerName && index->lowerAddr == lowerAddr)
            return false;
        
        
        vector <TCompId> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompId(taxID), invCmp);
        
        if(ind != m_ID.end() && ind->ID == taxID)
            return false;
        
        m_Db.insert(index, TCompany{name, addr, taxID, lowerName, lowerAddr});
        m_ID.insert(ind, TCompId{taxID, name, addr});

        return true;
    }
    
//-------------------------------------------------------------------------------------------------------------
    bool          cancelCompany  ( const string    & name,
                                   const string    & addr )
    {
        string lowerName = name, lowerAddr = addr;
        
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});

        vector <TCompany> :: iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        if(index == m_Db.end())
            return false;

        if(index->lowerName != lowerName || index->lowerAddr != lowerAddr)
            return false;
        
        
        vector <TCompId> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompId(index->m_ID), invCmp);
        
        long i = (index - m_Db.begin());
        
        long j = (ind - m_ID.begin());
 
        m_Db.erase(m_Db.begin() + i);
        m_ID.erase(m_ID.begin() + j);

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    bool          cancelCompany  ( const string    & taxID )
    {
        vector <TCompId> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompId(taxID), invCmp);
        if(ind == m_ID.end())
            return false;
        if(ind->ID != taxID)
            return false;
        
        string lowerName = ind->k_name, lowerAddr = ind->k_addr;

        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
        
        vector <TCompany> :: iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        long i = (index - m_Db.begin());
        
        long j = (ind - m_ID.begin());
 
            m_Db.erase(m_Db.begin() + i);
            m_ID.erase(m_ID.begin() + j);

            return true;
    }
//-------------------------------------------------------------------------------------------------------------
    bool          invoice        ( const string    & taxID,
                                   unsigned int      amount )
    {
        vector <TCompId> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompId(taxID), invCmp);
        
        if(ind == m_ID.end())
            return false;

        if(ind->ID != taxID) {

            return false;
        }

        string lowerName = ind->k_name, lowerAddr = ind->k_addr;

        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
        
        vector <TCompany> :: iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        index->m_inv += amount;
        
        faktura.push_back(amount);

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    bool          invoice        ( const string    & name,
                                   const string    & addr,
                                   unsigned int      amount )
    {
        string lowerName = name, lowerAddr = addr;
        
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
        
        vector <TCompany> :: iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        if(index == m_Db.end())
            return false;

        if(index->lowerName != lowerName || index->lowerAddr != lowerAddr) {

            return false;
        }

        index->m_inv += amount;
        
        faktura.push_back(amount);
            
     
        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    bool          audit          ( const string    & name,
                                   const string    & addr,
                                  unsigned int    & sumIncome ) const
    {
        string lowerName = name, lowerAddr = addr;
        
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
        
        vector <TCompany> ::const_iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        if(index == m_Db.end())
            return false;

        if(index->lowerName != lowerName || index->lowerAddr != lowerAddr) {

            return false;
        }

        sumIncome = index->m_inv;
            
        
        return true;

    }
//-------------------------------------------------------------------------------------------------------------
    bool          audit          ( const string    & taxID,
                                  unsigned int    & sumIncome ) const
    {
        vector <TCompId> :: const_iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompId(taxID), invCmp);
        
        if(ind == m_ID.end())
            return false;

        if(ind->ID != taxID) {

            return false;
        }
        
        string lowerName = ind->k_name, lowerAddr = ind->k_addr;

        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});

        vector <TCompany> :: const_iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);

        sumIncome = index->m_inv;
            
        
        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    bool          firstCompany   ( string          & name,
                                  string          & addr ) const
    {
        if(m_Db.size() == 0)
            return false;

        name = m_Db[0].m_name;
        addr = m_Db[0].m_address;

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    bool          nextCompany    ( string          & name,
                                  string          & addr ) const
    {
        string lowerName = name, lowerAddr = addr;

        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
        
        vector <TCompany> ::const_iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);

        if(index->lowerName != lowerName || index->lowerAddr != lowerAddr)
            return false;
        
        long unsigned int ind = (index - m_Db.begin());
        
        if(ind + 1 == m_Db.size())
            return false;

        name = m_Db[ind + 1].m_name;
        addr = m_Db[ind + 1].m_address;
        
        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    unsigned int  medianInvoice  ( void ) const
    {
        int count = 0;


        int *tmpDB = new int[faktura.size()];

        int result;

        for(size_t i = 0; i < faktura.size(); i++) {
            tmpDB[i] = faktura[i];
            count++;
        }


            int i, key, j;
            for (i = 1; i < count; i++)
            {
                key = tmpDB[i];
                j = i - 1;


                while (j >= 0 && tmpDB[j] > key)
                {
                    tmpDB[j + 1] = tmpDB[j];
                    j = j - 1;
                }
                tmpDB[j + 1] = key;
            }

        if(count == 0) {
            delete [] tmpDB;
            return 0;
        }

        if(count == 1) {
            //cout << m_Db[0 + step].m_inv << " " << m_Db[0 + step].m_ID << endl;
            result = tmpDB[0];
            delete [] tmpDB;
            return result;
        }

        if(count % 2 != 0) {
            count = (count / 2);
            //cout << m_Db[count + step].m_inv << endl;
            result = tmpDB[count];
            delete[] tmpDB;
            return result;
            } else {
                if((tmpDB[count / 2]) > tmpDB[count / 2 - 1]) {
                    //cout << m_Db[count / 2 + step].m_inv << endl;
                    result = tmpDB[count / 2 ];
                    delete[] tmpDB;
                    return result;
                }
                else {
                    //cout << m_Db[count / 2 - 1 + step].m_inv << endl;
                    result = tmpDB[count / 2 - 1];;
                    delete[] tmpDB;
                    return result;
                }

            }

        return 0;
    }
    
    void printM_Db (void) const
    {
        cout << setfill ('-') << setw(50) << "" << endl;

        for(size_t i = 0; i < m_Db.size(); i++)
            cout << m_Db[i].m_name << " " << m_Db[i].m_address << " " << m_Db[i].m_ID << " " << m_Db[i].m_inv << " " << m_ID[i].ID << endl;
    }

  private:
//-------------------------------------------------------------------------------------------------------------
    struct TCompany
    {
        string m_name;
        string m_address;
        string m_ID;
        string lowerName;
        string lowerAddr;
        int m_inv;
        TCompany(void) : m_name(""), m_address(""), m_ID(""), lowerName(""), lowerAddr(""), m_inv(0) {}
        TCompany(string name, string address) : m_ID(""), lowerName(name), lowerAddr(address)
        {}
        TCompany(string name, string address, string ID, string lowerName, string lowerAddr, int inv = 0)
        {
            m_name = name;
            m_address = address;
            m_ID = ID;
            this->lowerName = lowerName;
            this->lowerAddr = lowerAddr;
            m_inv = inv;
        }
    };
    
    
    struct TCompId
    {
        string ID;
        string k_name;
        string k_addr;
        TCompId(void) : ID(""), k_name(""), k_addr("") {}
        TCompId(string id) : ID(id), k_name(""), k_addr("")
        {}
        TCompId(string ID, string name, string addr)
        {
            this->ID = ID;
            k_name = name;
            k_addr = addr;
        }

    };
//-------------------------------------------------------------------------------------------------------------
    vector <TCompany> m_Db;

    vector <TCompId> m_ID;

    vector <int> faktura;
    
//-------------------------------------------------------------------------------------------------------------
static bool lowerCmp (const TCompany & a, const TCompany & b)
{
    if(a.lowerName == b.lowerName) {
    //if(isLower(a.m_name, a.m_name) == true) {
        return a.lowerAddr < b.lowerAddr;
    }

    return a.lowerName < b.lowerName;
}
//-------------------------------------------------------------------------------------------------------------
static bool invCmp (const TCompId & a, const TCompId & b)
{
    return a.ID < b.ID;
}
//-------------------------------------------------------------------------------------------------------------
};


#ifndef __PROGTEST__
int               main           ( void )
{
  string name, addr;
  unsigned int sumIncome;

  CVATRegister b1;
  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
  assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . invoice ( "666/666", 2000 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "666/666/666", 3000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 4000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
  assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . cancelCompany ( "666/666" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . invoice ( "123456", 100 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 300 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 230 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 830 ) );
  assert ( b1 . medianInvoice () == 830 );
  assert ( b1 . invoice ( "123456", 1830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 3200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  assert ( ! b1 . firstCompany ( name, addr ) );

  CVATRegister b2;
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  assert ( b2 . medianInvoice () == 0 );
  assert ( b2 . invoice ( "ABCDEF", 1000 ) );
  assert ( b2 . medianInvoice () == 1000 );
  assert ( b2 . invoice ( "abcdef", 2000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( b2 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . invoice ( "1234567", 100 ) );
  assert ( ! b2 . invoice ( "ACE", "Kolejni", 100 ) );
  assert ( ! b2 . invoice ( "ACME", "Thakurova", 100 ) );
  assert ( ! b2 . audit ( "1234567", sumIncome ) );
  assert ( ! b2 . audit ( "ACE", "Kolejni", sumIncome ) );
  assert ( ! b2 . audit ( "ACME", "Thakurova", sumIncome ) );
  assert ( ! b2 . cancelCompany ( "1234567" ) );
  assert ( ! b2 . cancelCompany ( "ACE", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Thakurova" ) );
  assert ( b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . cancelCompany ( "ACME", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Kolejni" ) );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
