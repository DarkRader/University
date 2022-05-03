#ifndef __PROGTEST__
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CDataType
{
public:
    
             CDataType(void) = default;
    virtual ~CDataType(void) = default;
    
    virtual CDataType * clone() const = 0;
    
    size_t getSize(void) const;
    size_t getName(void) const { return nazv; }
    size_t getSizeStr(void) const { return size; }
    const vector<string> & getVector() const { return addItem; }
    const vector<pair<CDataType*, string>> & getVecStruct() const { return addStruct; }
    
    
    virtual CDataType & add(const string & Item)
    {
        for(size_t i = 0; i < addItem.size(); i++) {
            
            if(addItem[i] == Item)
                throw std :: invalid_argument("Duplicate enum value: " + Item);
            
        }
        
        addItem.push_back(Item);
        
        return *this;
    }
    
    virtual bool operator == (const CDataType & typ) const
    {
        return true;
        
    }

    virtual bool operator != (const CDataType & typ) const { return true; }
    
    friend ostream & operator << (ostream & os, const CDataType & exit)
    {
        exit.print(os);
        return os;
    }

protected:
    size_t nazv;
    size_t size;
    vector <string> addItem;
//    vector < pair <string, size_t> > addStruct;
    vector < pair <CDataType *, string> > addStruct;

    virtual void print(ostream & os) const = 0;
    
    
};

class CDataTypeInt : public CDataType
{
public:
    CDataTypeInt(void) {nazv = 1;}
    ~CDataTypeInt(void) {}
    
    CDataType * clone() const override
    {
        return new CDataTypeInt(*this);
    }
    
    size_t getSize(void) const { return  4; }
    size_t getName(void) const { return nazv; }
    
    bool operator == (const CDataType & typ) const override
    {
        if(nazv == typ.getName())
            return true;
        else
            return false;
    }
    
    bool operator != (const CDataType & typ) const override
    {
        if(nazv == typ.getName())
            return false;
        else
            return true;
    }
    
protected:
    void print(ostream & os) const override
    {
        os << "int" << endl;
        os << endl;
    }
    
};
class CDataTypeDouble : public CDataType
{
public:
    CDataTypeDouble(void) {nazv = 2;}
   ~CDataTypeDouble(void) {}
    
    CDataType * clone() const override
    {
        return new CDataTypeDouble(*this);
    }
   
    size_t getSize(void) const { return  8; }
    size_t getName(void) const { return nazv; }
    
    bool operator == (const CDataType & typ) const override
    {
        if(nazv == typ.getName())
            return true;
        else
            return false;
    }
    
    bool operator != (const CDataType & typ) const override
    {
        if(nazv == typ.getName())
            return false;
        else
            return true;
    }
    
protected:
    void print(ostream & os) const override
    {
        os << "double" << endl;
        os << endl;
    }
    
};

class CDataTypeEnum : public CDataType
{
public:
    CDataTypeEnum(void) {nazv = 3;}
   ~CDataTypeEnum(void) {}
    
    CDataType * clone() const override
    {
        return new CDataTypeEnum(*this);
    }
   
    size_t getSize(void) const { return  4; }
    size_t getName(void) const { return nazv; }
    
    bool operator == (const CDataType & typ) const override
    {
        if(nazv == typ.getName() && addItem.size() == typ.getVector().size()) {
            for(size_t i = 0; i < addItem.size(); i++) {
                if(addItem[i] != typ.getVector()[i])
                    return false;
            }
            return true;
        } else
            return false;
    }
    
    bool operator != (const CDataType & typ) const override
    {
        if(nazv == typ.getName() && addItem.size() == typ.getVector().size()) {
            for(size_t i = 0; i < addItem.size(); i++) {
                if(addItem[i] != typ.getVector()[i])
                    return true;
            }
            return false;
        } else
            return true;
    }
    
protected:
    void print(ostream & os) const override
    {
        os << "enum" << endl;
        os << "{" << endl;
        for(size_t i = 0; i < addItem.size() - 1; i++) {
            os << addItem[i] << "," << endl;
        }
        os << addItem[addItem.size() - 1] << endl;
        os << "}"; // << endl;
    }
    int x1;
    int x2;
};
class CDataTypeStruct : public CDataType
{
public:
    CDataTypeStruct(void) {nazv = 4; size = 0;}
   ~CDataTypeStruct(void) {}
    
    CDataType * clone() const override
    {
        return new CDataTypeStruct(*this);
    }
    
    size_t getName(void) const { return nazv; }
    size_t getSize(void) const { return  size; }
    
    CDataTypeStruct & addField(const string & item, const CDataType & type)
    {
        for(size_t i = 0; i < addStruct.size(); i++)
        {
            if(addStruct[i].second == item)
                throw std :: invalid_argument("Duplicate field: " + item);
        }
        switch (type.getName()) {
            case 1: size += 4;
                break;
            case 2: size += 8;
                break;
            case 3: size += 4;
                break;
                
            default:
                break;
        }
        
        addStruct.push_back(make_pair(type.clone(), item));
        
        return *this;
    }

    CDataType & field(const string & item) const
    {
        auto itr = addStruct.begin();
        
        for(size_t i = 0; i < addStruct.size(); i++, itr++) {
            if(addStruct[i].second == item) {
                if(addStruct[i].first->getName() == 1) {
                    return * dynamic_cast< CDataTypeInt *>( itr->first);
                } else if (addStruct[i].first->getName() == 2) {
                    return * dynamic_cast< CDataTypeDouble *>(itr->first);
                } else if(addStruct[i].first->getName() == 3) {
                    return * dynamic_cast< CDataTypeEnum *>(itr->first);
                }
                break;
            }
                
        }
        throw std :: invalid_argument("Unknown field: " + item);
    }
    
    bool operator == (const CDataType & typ) const override
    {
        if(nazv == typ.getName() && size == typ.getSizeStr() &&
           addStruct.size() == typ.getVecStruct().size()) {
            for(size_t i = 0; i < addStruct.size(); i++) {
                if(addStruct[i].first->getName() == 3 && typ.getVecStruct()[i].first->getName() == 3) {
                    if(addStruct[i].first->getVector().size() != typ.getVecStruct()[i].first->getVector().size())
                        return false;
                    
                    for(size_t j = 0; j < addStruct[i].first->getVector().size(); j++) {
                        if(addStruct[i].first->getVector()[j] != typ.getVecStruct()[i].first->getVector()[j])
                            return false;
                    }
                    continue;
                }
                
                
                if(addStruct[i].first->getName() != typ.getVecStruct()[i].first->getName())
                    return false;
            }
            return true;
        } else
            return false;
    }
    
    bool operator != (const CDataType & typ) const override
    {
        if(nazv == typ.getName() && size == typ.getSizeStr() &&
           addStruct.size() == typ.getVecStruct().size()) {
            for(size_t i = 0; i < addStruct.size(); i++) {
                if(addStruct[i].first->getName() == 3 && typ.getVecStruct()[i].first->getName() == 3) {
                    if(addStruct[i].first->getVector().size() != typ.getVecStruct()[i].first->getVector().size())
                        return true;
                    
                    for(size_t j = 0; j < addStruct[i].first->getVector().size(); j++) {
                        if(addStruct[i].first->getVector()[j] != typ.getVecStruct()[i].first->getVector()[j])
                            return true;
                    }
                    continue;
                }
                
                
                if(addStruct[i].first->getName() != typ.getVecStruct()[i].first->getName())
                    return true;
            }
            return false;
        } else
            return true;
    }
    
protected:
//    vector < pair <CDataType *, string> > addStruct;
    void printField(ostream & os, size_t poz) {
        
    }
    
    void print(ostream & os) const override
    {
        os << "struct" << endl;
        os << "{" << endl;
        for(size_t i = 0; i < addStruct.size(); i++) {
            //std :: cout <<
            if(addStruct[i].first->getName() == 1)
                os << "int" << " " << addStruct[i].second << ";" << endl;
            else if (addStruct[i].first->getName() == 2)
                os << "double" << " " << addStruct[i].second << ";" << endl;
            else if(addStruct[i].first->getName() == 3) {
                os << "enum" << endl;
                os << "{" << endl;
                for(size_t j = 0; j < addStruct[i].first->getVector().size() - 1; j++) {
                    os << addStruct[i].first->getVector()[j] << "," << endl;
                }
                os << addStruct[i].first->getVector()[addStruct[i].first->getVector().size() - 1] << endl;
                os << "}" << " " << addStruct[i].second << ";" << endl;
            }
        }
        os << "}";
    }
    int x1;
    int x2;
};
#ifndef __PROGTEST__
static bool        whitespaceMatch                         ( const string    & a,
                                                             const string    & b )
{
    string newA = const_cast<string &>(a);
    string newB = const_cast<string &>(b);
    
    newA.erase(remove(newA.begin(), newA.end(), ' '), newA.end());
    newB.erase(remove(newB.begin(), newB.end(), ' '), newB.end());
    
    
  return newA == newB;
}
template <typename T_>
static bool        whitespaceMatch                         ( const T_        & x,
                                                             const string    & ref )
{
  ostringstream oss;
  oss << x;
  return whitespaceMatch ( oss . str (), ref );
}
int main ( void )
{
    
  CDataTypeStruct  a = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () .
                          add ( "NEW" ) .
                          add ( "FIXED" ) .
                          add ( "BROKEN" ) .
                          add ( "DEAD" ) ).
                        addField ( "m_Ratio", CDataTypeDouble () );

  CDataTypeStruct b = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () .
                          add ( "NEW" ) .
                          add ( "FIXED" ) .
                          add ( "BROKEN" ) .
                          add ( "READY" ) ).
                        addField ( "m_Ratio", CDataTypeDouble () );

  CDataTypeStruct c =  CDataTypeStruct () .
                        addField ( "m_First", CDataTypeInt () ) .
                        addField ( "m_Second", CDataTypeEnum () .
                          add ( "NEW" ) .
                          add ( "FIXED" ) .
                          add ( "BROKEN" ) .
                          add ( "DEAD" ) ).
                        addField ( "m_Third", CDataTypeDouble () );

  CDataTypeStruct  d = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () .
                          add ( "NEW" ) .
                          add ( "FIXED" ) .
                          add ( "BROKEN" ) .
                          add ( "DEAD" ) ).
                        addField ( "m_Ratio", CDataTypeInt () );
  assert ( whitespaceMatch ( a, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "}") );

  assert ( whitespaceMatch ( b, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "}") );

  assert ( whitespaceMatch ( c, "struct\n"
    "{\n"
    "  int m_First;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Second;\n"
    "  double m_Third;\n"
    "}") );

  assert ( whitespaceMatch ( d, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  int m_Ratio;\n"
    "}") );

  assert ( a != b );
  assert ( a == c );
  assert ( a != d );
  assert ( a . field ( "m_Status" ) == CDataTypeEnum () . add ( "NEW" ) . add ( "FIXED" ) . add ( "BROKEN" ) . add ( "DEAD" ) );
  assert ( a . field ( "m_Status" ) != CDataTypeEnum () . add ( "NEW" ) . add ( "BROKEN" ) . add ( "FIXED" ) . add ( "DEAD" ) );
  assert ( a != CDataTypeInt() );
  assert ( whitespaceMatch ( a . field ( "m_Status" ), "enum\n"
    "{\n"
    "  NEW,\n"
    "  FIXED,\n"
    "  BROKEN,\n"
    "  DEAD\n"
    "}") );

  CDataTypeStruct aOld = a;
  b . addField ( "m_Other", CDataTypeDouble ());

  a . addField ( "m_Sum", CDataTypeInt ());

  assert ( a != aOld );
  assert ( a != c );
  assert ( aOld == c );
  assert ( whitespaceMatch ( a, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "  int m_Sum;\n"
    "}") );

  assert ( whitespaceMatch ( b, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "  double m_Other;\n"
    "}") );

  c . addField ( "m_Another", a . field ( "m_Status" ));

  assert ( whitespaceMatch ( c, "struct\n"
    "{\n"
    "  int m_First;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Second;\n"
    "  double m_Third;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Another;\n"
    "}") );

  d . addField ( "m_Another", a . field ( "m_Ratio" ));

  assert ( whitespaceMatch ( d, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  int m_Ratio;\n"
    "  double m_Another;\n"
    "}") );

  assert ( a . getSize () == 20 );
  assert ( b . getSize () == 24 );
  try
  {
    a . addField ( "m_Status", CDataTypeInt () );
    assert ( "addField: missing exception!" == nullptr );
  }
  catch ( const invalid_argument & e )
  {
    assert ( e . what () == "Duplicate field: m_Status"sv );
  }

  try
  {
    cout << a . field ( "m_Fail" ) << endl;
    assert ( "field: missing exception!" == nullptr );
  }
  catch ( const invalid_argument & e )
  {
    assert ( e . what () == "Unknown field: m_Fail"sv );
  }

  try
  {
    CDataTypeEnum en;
    en . add ( "FIRST" ) .
         add ( "SECOND" ) .
         add ( "FIRST" );
    assert ( "add: missing exception!" == nullptr );
  }
  catch ( const invalid_argument & e )
  {
    assert ( e . what () == "Duplicate enum value: FIRST"sv );
  }
    
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

