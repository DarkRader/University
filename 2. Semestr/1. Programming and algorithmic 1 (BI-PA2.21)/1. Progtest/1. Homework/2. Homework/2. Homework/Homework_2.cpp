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

    CVATRegister   ( void ) {}
   ~CVATRegister   ( void ) {}
//-------------------------------------------------------------------------------------------------------------
    /**
     *The newCompany method adds another company to the existing database
     *@param name represented the name of company
     *@param addr represented the address of company
     *@param taxID represented a unique company ID
     *@return true if a company was added
     *or false if a company was not added (because a company with the same name and address or a company with the same id already existed in the database)
     */
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
        
        vector <TCompany> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        
        if(ind != m_ID.end() && ind->m_ID == taxID)
            return false;
        
        m_Db.insert(index, TCompany{name, addr, taxID, lowerName, lowerAddr});
        m_ID.insert(ind, TCompany{name, addr, taxID, lowerName, lowerAddr});

        return true;
    }
    
//-------------------------------------------------------------------------------------------------------------
    /**
     *The cancelCompany methods remove a company from the database by name and address
     *@param name represented the name of company
     *@param addr represented the address of company
     *@return true if a company was successfully deleted
     * or false if a company was not deleted (because there was no company with the same identification by name and address)
     */
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
        
        vector <TCompany> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompany(index->m_ID), idCmp);
        
        long i = (index - m_Db.begin());
        long j = (ind - m_ID.begin());
 
        m_Db.erase(m_Db.begin() + i);
        m_ID.erase(m_ID.begin() + j);

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    /**
     *The cancelCompany methods remove a company from the database by company ID
     *@param taxID represented a unique company ID
     *@return true if a company was successfully deleted
     * or false if a company was not deleted (because there was no company with the same identification by company ID)
     */
    bool          cancelCompany  ( const string    & taxID )
    {
        vector <TCompany> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        if(ind == m_ID.end() || ind->m_ID != taxID)
            return false;
        
        string lowerName = ind->m_name, lowerAddr = ind->m_address;

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
    /**
     *The invoice methods adds an invoice to the company by company ID
     *@param taxID represented a unique company ID
     *@param amount represented the invoice of the company that is added to it
     *@return true if an invoice  was successfully added in a company
     * or false if an invoice was not added (because a company was not exist)
     */
    bool          invoice        ( const string    & taxID,
                                   unsigned int      amount )
    {
        vector <TCompany> :: iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        
        if(ind == m_ID.end() || ind->m_ID != taxID)
            return false;

        string lowerName = ind->m_name, lowerAddr = ind->m_address;

        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
        
        vector <TCompany> :: iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        index->m_sumInv += amount;
        
        factures.push_back(amount);

        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    /**
     *The invoice methods adds an invoice to the company by name and address
     *@param name represented the name of company
     *@param addr represented the address of company
     *@param amount represented the invoice of the company that is added to it
     *@return true if an invoice  was successfully added in a company
     * or false if an invoice was not added (because a company was not exist)
     */
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
        
        if(index == m_Db.end() || index->lowerName != lowerName || index->lowerAddr != lowerAddr)
            return false;

        index->m_sumInv += amount;
        
        factures.push_back(amount);
     
        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    /**
     *The  audit  methods searches for the amount of company invoices by name and address
     *@param name represented the name of company
     *@param addr represented the address of company
     *@param sumIncome represented the amount of the company's invoices
     *@return true if the amount of the company's invoices is successfully found
     * or false if the amount is not found (because a company was not exist)
     * @note if no invoice has been added to the company,  then sumIncome will be equal to 0
     */
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
        
        if(index == m_Db.end() || index->lowerName != lowerName || index->lowerAddr != lowerAddr)
            return false;

        sumIncome = index->m_sumInv;
            
        return true;

    }
//-------------------------------------------------------------------------------------------------------------
    /**
     *The  audit  methods searches for the amount of company invoices by company ID
     *@param taxID represented a unique company ID
     *@param sumIncome represented the amount of the company's invoices
     *@return true if the amount of the company's invoices is successfully found
     * or false if the amount is not found (because a company was not exist)
     * @note if no invoice has been added to the company,  then sumIncome will be equal to 0
     */
    bool          audit          ( const string    & taxID,
                                  unsigned int    & sumIncome ) const
    {
        vector <TCompany> :: const_iterator ind = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        
        if(ind == m_ID.end() || ind->m_ID != taxID)
            return false;
        
        string lowerName = ind->m_name, lowerAddr = ind->m_address;

        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});

        vector <TCompany> :: const_iterator index = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);

        sumIncome = index->m_sumInv;
            
        return true;
    }
//-------------------------------------------------------------------------------------------------------------
    /**
     *The firstCompany method finds the first firm in the database
     *@note companies should already be sorted by name and address, if companies have the same names, then sorting takes place by address
     *@param name represented the name of company
     *@param addr represented the address of company
     *@return true if the method wrote out the first company in the database
     * or false if the list of companies is empty
     */
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
    /**
     *The nextCompany method works similarly like firstCompany method, it finds the next company that follows the company specified by the parameters in the list
     *@note companies should already be sorted by name and address, if companies have the same names, then sorting takes place by address
     *@param name represented the name of company
     *@param addr represented the address of company
     *@return true if there is other company listed after name and addr
     * or false if there is no other company listed after name and addr
     */
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
    /**
     *The medianInvoice method searches for the median value of an invoice
     *@note All successfully processed invoices entered by invoice are counted into the calculated median. Thus, invoices that could not be assigned (the invoice call failed) are not counted, but all invoices registered so far are counted, that is, when a company is deleted, its invoices are not removed from the calculation of the median. If an even number of invoices is specified in the system, the higher of the two middle values is taken
     *@return the found median, if the method has not found a median (for example, invoices have not been added), returns 0
     */
    unsigned int  medianInvoice  ( void ) const
    {
        int count = 0;
        int *tmpDB = new int[factures.size()];
        int result;

        for(size_t i = 0; i < factures.size(); i++) {
            tmpDB[i] = factures[i];
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
            result = tmpDB[0];
            delete [] tmpDB;
            return result;
        }

        if(count % 2 != 0) {
            count = (count / 2);
            result = tmpDB[count];
            delete[] tmpDB;
            return result;
            } else {
                if((tmpDB[count / 2]) > tmpDB[count / 2 - 1]) {
                    result = tmpDB[count / 2 ];
                    delete[] tmpDB;
                    return result;
                }
                else {
                    result = tmpDB[count / 2 - 1];;
                    delete[] tmpDB;
                    return result;
                }
            }
        return 0;
    }
//-------------------------------------------------------------------------------------------------------------
  private:
    /**
     *The TCompany struct is used to keep all the necessary parameters in the company's database
     *param m_name represented the original name of company
     *param m_address represented the original adress of company
     *param m_ID represented a unique company ID
     *param lowerName represented a company name in lowercase
     *param lowerAddr represented a company address in lowercase
     *param m_inv represented the amount of invoices in the company
     */
    struct TCompany
    {
        string m_name;
        string m_address;
        string m_ID;
        string lowerName;
        string lowerAddr;
        int m_sumInv;
        TCompany(void) : m_name(""), m_address(""), m_ID(""), lowerName(""), lowerAddr(""), m_sumInv(0) {}
        TCompany(string name, string address) : m_ID(""), lowerName(name), lowerAddr(address) {}
        TCompany(string id) : m_name(""), m_address(""), m_ID(id) {}
        TCompany(string name, string address, string ID, string lowerName, string lowerAddr, int invoce = 0)
        {
            m_name = name;
            m_address = address;
            m_ID = ID;
            this->lowerName = lowerName;
            this->lowerAddr = lowerAddr;
            m_sumInv = invoce;
        }
    };
//-------------------------------------------------------------------------------------------------------------
    // a vector of the structure data type is used to keep duplicated data of the same database for the case
    // when need to search for a company in the database by name and address or by id
    vector <TCompany> m_Db, m_ID;
    
    // the vector where all the recorded invoices are kept is mainly used for the medianInvoice method
    vector <int> factures;
//-------------------------------------------------------------------------------------------------------------
    //comparator used for comparison by name, if the names are the same, then by address
    static bool lowerCmp (const TCompany & a, const TCompany & b)
    {
        if(a.lowerName == b.lowerName) {
            return a.lowerAddr < b.lowerAddr;
        }
        return a.lowerName < b.lowerName;
    }
//-------------------------------------------------------------------------------------------------------------
    //comparator used for comparison by company id
    static bool idCmp (const TCompany & a, const TCompany & b)
    {
        return a.m_ID < b.m_ID;
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
