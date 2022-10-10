#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
  public:
    InvalidDateException ( )
      : invalid_argument ( "invalid date or format" )
    {
    }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
  return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================
class CDate
{
public:
    CDate (const int m_year, const int m_mounth, const int m_day)
    {
        year = m_year;
        mounth = m_mounth;
        day = m_day;
        
        if(validDate(year, mounth, day)==false)
        {
             throw InvalidDateException();
            
        } else {
            convert_to_srting ();
            
            tme.tm_year = year - 1900;
            tme.tm_mon = mounth - 1;
            tme.tm_mday = day;
            tme.tm_sec = 0;
            tme.tm_min = 0;
            tme.tm_hour = 0;
            tme.tm_isdst = 0;
        }

    }
    
    CDate operator + (const int & days)
    {
        tme.tm_mday += days;
         mktime(&tme);
        
        year = tme.tm_year + 1900; mounth = tme.tm_mon + 1; day = tme.tm_mday;
        
        convert_to_srting ();
        
        return *this;
    }
    
    CDate operator - (const int & days)
    {
       tme.tm_mday -= days;
         mktime(&tme);
        
        year = tme.tm_year + 1900; mounth = tme.tm_mon + 1; day = tme.tm_mday;
        
        convert_to_srting ();
        
        return *this;
    }
    
    friend int operator - (const CDate & dt1, const CDate & dt2)
    {
        tm newDt1, newDt2;
        
        newDt1.tm_year = dt1.tme.tm_year + 1900;
        newDt1.tm_mon = dt1.tme.tm_mon;
        newDt1.tm_mday = dt1.tme.tm_mday;
        newDt1.tm_sec = 0;
        newDt1.tm_min = 0;
        newDt1.tm_hour = 0;
        newDt1.tm_isdst = 0;
        
        newDt2.tm_year = dt2.tme.tm_year + 1900;
        newDt2.tm_mon = dt2.tme.tm_mon;
        newDt2.tm_mday = dt2.tme.tm_mday;
        newDt2.tm_sec = 0;
        newDt2.tm_min = 0;
        newDt2.tm_hour = 0;
        newDt2.tm_isdst = 0;
        
        time_t x = mktime(&newDt1);
        time_t y = mktime(&newDt2);
        
        int dif = std::difftime(x, y) / (60 * 60 * 24);
        
        dif = dif + 0.5;
        
        int result = (int)dif;
        
        return result;
    }
    
    friend bool operator == (const CDate & dt1, const CDate & dt2)
    {
        
        if(dt1.year == dt2.year && dt1.mounth == dt2.mounth && dt1.day == dt2.day)
            return true;
        
        
        return false;
    }
    
    friend bool operator != (const CDate & dt1, const CDate & dt2)
    {
        if(dt1.year != dt2.year || dt1.mounth != dt2.mounth || dt1.day != dt2.day)
            return true;
        
        
        return false;
    }
    
    friend bool operator <= (const CDate & dt1, const CDate & dt2)
    {
        
        if(dt1.year < dt2.year)
            return true;
        else if(dt1.year == dt2.year) {
            if(dt1.mounth < dt2.mounth)
                return true;
            else if(dt1.mounth == dt2.mounth) {
                if(dt1.day < dt2.day) {
                    return true;
                } else if (dt1.day == dt2.day)
                    return true;
            }
        }
        
        return false;
    }
    
    friend bool operator >= (const CDate & dt1, const CDate & dt2)
    {
        
        if(dt1.year > dt2.year)
            return true;
        else if(dt1.year == dt2.year) {
            if(dt1.mounth > dt2.mounth)
                return true;
            else if(dt1.mounth == dt2.mounth) {
                if(dt1.day > dt2.day) {
                    return true;
                } else if (dt1.day == dt2.day)
                    return true;
            }
        }
        
        
        return false;
    }
    
    friend bool operator < (const CDate & dt1, const CDate & dt2)
    {
        
        if(dt1.year < dt2.year)
            return true;
        else if (dt1.year == dt2.year) {
            if(dt1.mounth < dt2.mounth)
                return true;
            else if (dt1.mounth == dt2.mounth) {
                if(dt1.day < dt2.day)
                    return true;
                else
                    return false;
            }
        }
        
        
        return false;
    }
    
    friend bool operator > (const CDate & dt1, const CDate & dt2)
    {
        if(dt1.year > dt2.year)
            return true;
        else if (dt1.year == dt2.year) {
            if(dt1.mounth > dt2.mounth)
                return true;
            else if (dt1.mounth == dt2.mounth) {
                if(dt1.day > dt2.day)
                    return true;
                else
                    return false;
            }
        }
        
        
        return false;
    }
    
    CDate operator ++ (void)
    {
        *this = *this + 1;
        convert_to_srting ();
        
        return *this;
    }
    
    CDate operator -- (void)
    {
        *this = *this + (-1);
        convert_to_srting ();
        
        return *this;
    }
    
    CDate operator ++ (int)
    {
        CDate tmp(*this);
        (*this) = *this + 1;
        convert_to_srting ();
        
        return tmp;
    }
    
    CDate operator -- (int)
    {
        CDate tmp(*this);
        *this = *this + ( - 1);
        convert_to_srting ();
        
        return tmp;
    }
    
    friend ostream & operator << (ostream & os, const CDate & vystup)
    {
        return os << vystup.k_Year << "-" << vystup.k_Mounth << "-" << vystup.k_Day;
    }
    
    friend istream & operator >> (istream & is, CDate & vstup)
    {
        string newDates, newYear, newMounth, newDay;
        
        is >> newDates;
        
        for (size_t i = 0; i < 4; i++) {
            newYear += newDates[i];
        }
        
        for (size_t i = 5; i < 7; i++) {
            newMounth += newDates[i];
        }
        
        for (size_t i = 8; i < 10; i++) {
            newDay += newDates[i];
        }
        
        int y = stoi(newYear), m = stoi(newMounth), d = stoi(newDay);
        
    
        if(validDate(y, m, d)==false)
        {
            is.setstate(ios::failbit);
        } else if(newDates.size() != 10 || newDates[4] != '-' || newDates[7] != '-') {
            is.setstate(ios::failbit);
        } else {
        
        vstup.k_Year = newYear;
        vstup.year = y;
        vstup.k_Mounth = newMounth;
        vstup.mounth = m;
        vstup.k_Day = newDay;
        vstup.day = d;
        
        vstup.tme.tm_year = vstup.year - 1900;
        vstup.tme.tm_mon = vstup.mounth - 1;
        vstup.tme.tm_mday = vstup.day;
        vstup.tme.tm_sec = 0;
        vstup.tme.tm_min = 0;
        vstup.tme.tm_hour = 0;
        vstup.tme.tm_isdst = 0;
        }
        
        return is;
    }
    
private:
    int year;
    int mounth;
    int day;
    tm tme;
    string k_Year;
    string k_Mounth;
    string k_Day;
    
    static bool validDate (int & year, int & mounth, int & day)
    {
        if(year < 2000 || year > 2030 || mounth < 1 || mounth > 12 || day < 1 || day > 31)
            return false;
        
        if(year % 4 != 0 && mounth == 2 && day > 28)
            return false;
        else if(year % 4 == 0 && mounth == 2 && day > 29)
            return false;
        
        if((mounth == 4 || mounth == 6 || mounth == 9 || mounth == 11) && day > 30)
            return false;

        return true;
    }
    
    void convert_to_srting (void)
    {
                string dd = to_string(day);
                string mm = to_string(mounth);
                string yy = to_string(year);
        
                k_Year = yy;
        
                if(day < 10)
                    k_Day = '0' + dd;
                else
                    k_Day = dd;
        
                if(mounth < 10)
                    k_Mounth = '0' + mm;
                else
                    k_Mounth = mm;
    }
    
};

#ifndef __PROGTEST__
int main ( void )
{
  ostringstream oss;
  istringstream iss;
  
  CDate a ( 2000, 1, 2 );
  CDate b ( 2010, 2, 3 );
  CDate c ( 2004, 2, 10 );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2000-01-02" );
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2010-02-03" );
  oss . str ("");
  oss << c;
  assert ( oss . str () == "2004-02-10" );
  a = a + 1500;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2004-02-10" );
  b = b - 2000;
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2004-08-13" );
  assert ( b - a == 185 );
  assert ( ( b == a ) == false );
  assert ( ( b != a ) == true );
  assert ( ( b <= a ) == false );
  assert ( ( b < a ) == false );
  assert ( ( b >= a ) == true );
  assert ( ( b > a ) == true );
  assert ( ( c == a ) == true );
  assert ( ( c != a ) == false );
  assert ( ( c <= a ) == true );
  assert ( ( c < a ) == false );
  assert ( ( c >= a ) == true );
  assert ( ( c > a ) == false );
  a = ++c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-11" );
  a = --c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-10" );
  a = c++;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-11" );
  a = c--;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-10" );
  iss . clear ();
  iss . str ( "2015-09-03" );
  assert ( ( iss >> a ) );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-09-03" );
  a = a + 70;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-11-12" );

  CDate d ( 2000, 1, 1 );
  try
  {
    CDate e ( 2000, 32, 1 );
    assert ( "No exception thrown!" == nullptr );
  }
  catch ( ... )
  {
  }
  iss . clear ();
  iss . str ( "2000-12-33" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-11-31" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-02-29" );
  assert ( ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
  iss . clear ();
  iss . str ( "2001-02-29" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );

  //-----------------------------------------------------------------------------
  // bonus test examples
  //-----------------------------------------------------------------------------
//  CDate f ( 2000, 5, 12 );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  oss . str ("");
//  oss << date_format ( "%Y/%m/%d" ) << f;
//  assert ( oss . str () == "2000/05/12" );
//  oss . str ("");
//  oss << date_format ( "%d.%m.%Y" ) << f;
//  assert ( oss . str () == "12.05.2000" );
//  oss . str ("");
//  oss << date_format ( "%m/%d/%Y" ) << f;
//  assert ( oss . str () == "05/12/2000" );
//  oss . str ("");
//  oss << date_format ( "%Y%m%d" ) << f;
//  assert ( oss . str () == "20000512" );
//  oss . str ("");
//  oss << date_format ( "hello kitty" ) << f;
//  assert ( oss . str () == "hello kitty" );
//  oss . str ("");
//  oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
//  assert ( oss . str () == "121212121212050505200020002000%%%%%" );
//  oss . str ("");
//  oss << date_format ( "%Y-%m-%d" ) << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-01-1" );
//  assert ( ! ( iss >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-1-01" );
//  assert ( ! ( iss >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-001-01" );
//  assert ( ! ( iss >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-01-02" );
//  assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2001-01-02" );
//  iss . clear ();
//  iss . str ( "05.06.2003" );
//  assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2003-06-05" );
//  iss . clear ();
//  iss . str ( "07/08/2004" );
//  assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2004-07-08" );
//  iss . clear ();
//  iss . str ( "2002*03*04" );
//  assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2002-03-04" );
//  iss . clear ();
//  iss . str ( "C++09format10PA22006rulez" );
//  assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2006-09-10" );
//  iss . clear ();
//  iss . str ( "%12%13%2010%" );
//  assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2010-12-13" );
//
//  CDate g ( 2000, 6, 8 );
//  iss . clear ();
//  iss . str ( "2001-11-33" );
//  assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "29.02.2003" );
//  assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "14/02/2004" );
//  assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "2002-03" );
//  assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "hello kitty" );
//  assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "2005-07-12-07" );
//  assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "20000101" );
//  assert ( ( iss >> date_format ( "%Y%m%d" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-01-01" );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
