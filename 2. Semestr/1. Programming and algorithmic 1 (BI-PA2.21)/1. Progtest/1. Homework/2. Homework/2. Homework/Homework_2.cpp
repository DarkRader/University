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
        //creating new variables to translate to lowercase
        string lowerName = name, lowerAddr = addr;

        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);
         
        //search for a company in the database by name and address using lower_bound
        vector <TCompany> :: iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        //checks for the existence of a company in the database, if a company with such a name and address already exists, return false
        if(itDB != m_Db.end() && itDB->lowerName == lowerName && itDB->lowerAddr == lowerAddr)
            return false;
        
        //search for a company in the database by company id using lower_bound
        vector <TCompany> :: iterator itID = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        
        //checks for the existence of a company in the database, if a company with such an ID already exists, we return false
        if(itID != m_ID.end() && itID->m_ID == taxID)
            return false;
        
        //inserting a new company when using the iterator into the vector, which will be searched by name and address
        m_Db.insert(itDB, TCompany{name, addr, taxID, lowerName, lowerAddr});
        //inserting a new company when using the iterator into the vector, which will be searched by company ID
        m_ID.insert(itID, TCompany{name, addr, taxID, lowerName, lowerAddr});

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
        //creating new variables to translate to lowercase
        string lowerName = name, lowerAddr = addr;
        
        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);

        //search for a company in the database by name and address using lower_bound
        vector <TCompany> :: iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        if(itDB == m_Db.end())
            return false;

        //we make a check, if there is no such company by name and address in the database, then we return false
        if(itDB->lowerName != lowerName || itDB->lowerAddr != lowerAddr)
            return false;
        
        //search for a company in the database by company id using lower_bound
        vector <TCompany> :: iterator itID = lower_bound(m_ID.begin(), m_ID.end(), TCompany(itDB->m_ID), idCmp);
        
        //creating variables to find out the positions from which we will delete the company
        long pozDB = (itDB - m_Db.begin());
        long pozID = (itID - m_ID.begin());
 
        //delete companies using erase from the found position
        m_Db.erase(m_Db.begin() + pozDB);
        m_ID.erase(m_ID.begin() + pozID);

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
        //search for a company in the database by company id using lower_bound
        vector <TCompany> :: iterator itID = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        
        //we make a check, if there is no such company by company ID in the database, then we return false
        if(itID == m_ID.end() || itID->m_ID != taxID)
            return false;
        
        //creating new variables to translate to lowercase
        string lowerName = itID->m_name, lowerAddr = itID->m_address;
        
        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);
        
        //search for a company in the database by name and address using lower_bound
        vector <TCompany> :: iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        //creating variables to find out the positions from which we will delete the company
        long pozDB = (itDB - m_Db.begin());
        long pozID = (itID - m_ID.begin());
 
        //delete companies using erase from the found position
        m_Db.erase(m_Db.begin() + pozDB);
        m_ID.erase(m_ID.begin() + pozID);

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
        //search for a company in the database by company id using lower_bound
        vector <TCompany> :: iterator itID = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        
        //if the company was not found, return false
        if(itID == m_ID.end() || itID->m_ID != taxID)
            return false;

        //creating new variables to translate to lowercase
        string lowerName = itID->m_name, lowerAddr = itID->m_address;
        
        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);
        
        //search for a company in the database by name and address using lower_bound
        vector <TCompany> :: iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        //adding an invoice to the total amount of company invoices
        itDB->m_sumInv += amount;
        
        //adding an invoice to a vector with invoices
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
        //creating new variables to translate to lowercase
        string lowerName = name, lowerAddr = addr;
        
        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);
        
        //search for a company in the database by name and address using lower_bound
        vector <TCompany> :: iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        //if the company was not found, return false
        if(itDB == m_Db.end() || itDB->lowerName != lowerName || itDB->lowerAddr != lowerAddr)
            return false;

        //adding an invoice to the total amount of company invoices
        itDB->m_sumInv += amount;
        
        //adding an invoice to a vector with invoices
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
        //creating new variables to translate to lowercase
        string lowerName = name, lowerAddr = addr;
        
        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);
        
        //search for a company in the database by name and address using lower_bound
        vector <TCompany> ::const_iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);
        
        //if the company was not found, return false
        if(itDB == m_Db.end() || itDB->lowerName != lowerName || itDB->lowerAddr != lowerAddr)
            return false;

        //we assign the total amount of the company's invoices to the variable sumIncome
        sumIncome = itDB->m_sumInv;
            
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
        //search for a company in the database by company id using lower_bound
        vector <TCompany> :: const_iterator itID = lower_bound(m_ID.begin(), m_ID.end(), TCompany(taxID), idCmp);
        
        //if the company was not found, return false
        if(itID == m_ID.end() || itID->m_ID != taxID)
            return false;
        
        //creating new variables to translate to lowercase
        string lowerName = itID->m_name, lowerAddr = itID->m_address;
 
        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);

        //search for a company in the database by name and address using lower_bound
        vector <TCompany> :: const_iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);

        //we assign the total amount of the company's invoices to the variable sumIncome
        sumIncome = itDB->m_sumInv;
            
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
        //checking for the presence of companies in the database
        if(m_Db.size() == 0)
            return false;

        //assign the name and address of the found company to the variables
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
        //creating new variables to translate to lowercase
        string lowerName = name, lowerAddr = addr;
        
        //function for converting variables to lowercase
        lowerCase(lowerName, lowerAddr);
        
        //search for a company in the database by name and address using lower_bound
        vector <TCompany> ::const_iterator itDB = lower_bound(m_Db.begin(), m_Db.end(), TCompany(lowerName, lowerAddr), lowerCmp);

        //if the company was not found, return false
        if(itDB->lowerName != lowerName || itDB->lowerAddr != lowerAddr)
            return false;
        
        //creating variable to find out the position of the company the name and address we received
        long unsigned int pozDB = (itDB - m_Db.begin());
    
        //we check if there is the following company in our database whose name and address we want to assign
        if(pozDB + 1 == m_Db.size())
            return false;

        //we assign the name and address of the following company
        name = m_Db[pozDB + 1].m_name;
        addr = m_Db[pozDB + 1].m_address;
        
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
        //a variable that will indicate the number of invoices in vector
        int count = 0;
        //we will create a new array of invoices, which we will sort
        int *tmpDB = new int[factures.size()];
        //the result we will return
        int result;

        //copy the values from the invoices vector to a new allocated int array
        for(size_t i = 0; i < factures.size(); i++) {
            tmpDB[i] = factures[i];
            count++;
        }
        
        //the cycle in which the invoices are sorted
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

        //if there are no invoices in the vector, return 0
        if(count == 0) {
            delete [] tmpDB;
            return 0;
        }

        //if there is only one invoice in the vector, return it
        if(count == 1) {
            result = tmpDB[0];
            delete [] tmpDB;
            return result;
        }

        //if the number of invoices is odd
        if(count % 2 != 0) {
            //returning the median of the array
            count = (count / 2);
            result = tmpDB[count];
            delete[] tmpDB;
            return result;
            //if there is an even number of invoices, see which invoice of the two central ones is bigger and return it
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
    //m_Db presented a database in which the search takes place by name and address
    //m_ID presented a database in which the search takes place by company ID
    vector <TCompany> m_Db, m_ID;
    
    // the vector where all the recorded invoices are kept is mainly used for the medianInvoice method
    vector <int> factures;
//-------------------------------------------------------------------------------------------------------------
    //function for translating name and address to lowercase
    static void lowerCase(string & lowerName, string & lowerAddr)
    {
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                  [](unsigned char c){return tolower(c);});

        transform(lowerAddr.begin(), lowerAddr.end(), lowerAddr.begin(),
                  [](unsigned char c){return tolower(c);});
    }
    
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
