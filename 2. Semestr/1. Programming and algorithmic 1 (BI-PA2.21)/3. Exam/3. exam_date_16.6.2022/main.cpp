/**
 * Implementujte metodu insert (vkládání), erase (mazání prvků
 * ze stromu a zároveň je potřeba uchovat správné pořádí podle
 * data vkládání) a vlastní destruktor, ostatní metody jsou
 * naimplentované. Kopírující konstruktor i operátor přiřazení
 * zakázán. Není povolené si přidat žádnou členskou proměnnou,
 * ale lze naimplementovat vlastní pomocné metody.
 *
 * Za správnost šablony neručím :-).
 */
 
#include <string>
#include <cassert>
 
using namespace std;
 
class CTree
{
  public:
    CTree() = default;
    ~CTree()
    {
        delete m_Root;
    }
    CTree(const CTree &src) = delete;
    bool operator=(const CTree &other) = delete;
    bool isSet(string key)
    {
      CNode * n = m_Root;
      while (n)
      {
        if (key == n->m_Key)
          return true;
        else if (key > n->m_Key)
          n = n->m_R;
        else
          n = n->m_L;
      }
      return false;
    }
    bool insert(string key)
    {
      // if list is empty
        if(!m_First)
        {
            auto * tmp = new CNode(key);
            m_First = m_Last = m_Root = tmp;
            return true;
        }

        auto ** curPoz = &m_Root;
        while((*curPoz))
        {
            //if exist key
            if((*curPoz)->m_Key == key)
                return false;
            else if((*curPoz)->m_Key > key) //left side
                curPoz = &((*curPoz)->m_L);
            else //right side
                curPoz = &((*curPoz)->m_R);
        }
        
        *curPoz = new CNode(key);
        
        m_Last->m_NextOrder = *curPoz;
        (*curPoz)->m_PrevOrder = m_Last;
        m_Last = *curPoz;
      
        return true;
    }
    bool erase(string key)
    {
      //if empty
      if(!m_First)
          return false;
       //have only root
       if(!(m_First->m_NextOrder) && m_First->m_Key == key)
       {
           m_Root = m_Last = m_First = nullptr;
           return true;
       }

        auto ** curPoz = &m_Root;
        while(*curPoz)
        {
            //if exist key
            if((*curPoz)->m_Key == key)
            {
                if((*curPoz)->m_R && (*curPoz)->m_L)
                {
                    auto * newBranch = *curPoz;
                    curPoz = &(*curPoz)->m_R;
                    
                    while((*curPoz)->m_L)
                        curPoz = &(*curPoz)->m_L;
                    
                    newBranch->m_Key = (*curPoz)->m_Key;
                }
                auto *del = *curPoz;
                
                if(del->m_R)
                    *curPoz = del->m_R;
                else
                    *curPoz = del->m_L;
                
                del->m_R = del->m_L = nullptr;
                
                if(del->m_PrevOrder)
                    del->m_PrevOrder->m_NextOrder = del->m_NextOrder;
                else
                    m_First = del->m_NextOrder;
                
                if(del->m_NextOrder)
                    del->m_NextOrder->m_PrevOrder = del->m_PrevOrder;
                else
                    m_Last = del->m_PrevOrder;
                
                delete del;

                return true;
            } else if((*curPoz)->m_Key > key) //left side
                curPoz = &(*curPoz)->m_L;
            else // right side
                curPoz = &(*curPoz)->m_R;
        }

        return false;
    }

  protected:
    class CNode
    {
      public:
        CNode(string key) : m_Key(key) {}
        string m_Key;
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
        CNode * m_PrevOrder = nullptr;
        CNode * m_NextOrder = nullptr;
    };
    CNode * m_Root = nullptr;
    CNode * m_First = nullptr;
    CNode * m_Last = nullptr;
};
 
class CTester : public CTree
{
  public:
    CTester () = default;
    void test()
    {
      CTester t0;
      assert(t0.insert("PA1")==true);
      assert(t0.m_First->m_Key=="PA1" && t0.m_First->m_NextOrder == nullptr);
      assert(t0.isSet("PA1")==true);
      assert(t0.insert("UOS")==true);
      assert(t0.insert("PA2")==true);
      assert(t0.isSet("PA2")==true);
      assert(t0.isSet("PA3")==false);

      assert(t0.insert("PA2")==false);
      assert(t0.insert("CAO")==true);
      assert(t0.insert("LIN")==true);
      assert(t0.insert("AAG")==true);
      assert(t0.insert("AG1")==true);
      assert(t0.insert("ZDM")==true);

      assert(t0.m_First->m_Key == "PA1"
             && t0.m_First->m_NextOrder->m_Key == "UOS"
             && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "CAO"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AAG"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "ZDM");

      assert(t0.m_Last->m_Key == "ZDM"
             && t0.m_Last->m_PrevOrder->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "AAG"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "LIN"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "CAO"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");

      assert(t0.erase("")==false);

      assert(t0.erase("ZDM")==true);
      assert(t0.m_First->m_Key == "PA1"
             && t0.m_First->m_NextOrder->m_Key == "UOS"
             && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "CAO"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AAG"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_Key == "AAG"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "LIN"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "CAO"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
      assert(t0.isSet("ZDM")==false);

      assert(t0.erase("AAG")==true);
      assert(t0.m_First->m_Key == "PA1"
             && t0.m_First->m_NextOrder->m_Key == "UOS"
             && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "CAO"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_Key == "LIN"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "CAO"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
      assert(t0.isSet("AAG")==false);

      assert(t0.erase("CAO")==true);
      assert(t0.m_First->m_Key == "PA1"
             && t0.m_First->m_NextOrder->m_Key == "UOS"
             && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_Key == "LIN"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
      assert(t0.isSet("CAO")==false);

      assert(t0.erase("UOS")==true);
      assert(t0.m_First->m_Key == "PA1"
             && t0.m_First->m_NextOrder->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "LIN"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_Key == "LIN"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
      assert(t0.isSet("UOS")==false);

      assert(t0.erase("UOS")==false);
      assert(t0.m_First->m_Key == "PA1"
             && t0.m_First->m_NextOrder->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "LIN"
             && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_Key == "LIN"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
      assert(t0.isSet("UOS")==false);

      assert(t0.erase("LIN")==true);
      assert(t0.m_First->m_Key == "PA1"
             && t0.m_First->m_NextOrder->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_Key == "PA2"
             && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
      assert(t0.isSet("LIN")==false);

      assert(t0.erase("PA1")==true);
      assert(t0.m_First->m_Key == "PA2"
             && t0.m_First->m_NextOrder->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1"
             && t0.m_Last->m_PrevOrder->m_Key == "PA2");
      assert(t0.isSet("PA1")==false);

      assert(t0.erase("PA2")==true);
      assert(t0.m_First->m_Key == "AG1");
      assert(t0.m_Last->m_Key == "AG1");
      assert(t0.isSet("PA2")==false);

      assert(t0.erase("AG1")==true);
      assert(t0.m_First == t0.m_Last);
      assert(t0.isSet("AG1")==false);
        
      assert ( t0 . erase ( "PA2" ) == false );
         
    assert ( t0 . insert ( "PA1" ) == true );
    assert ( t0 . insert ( "UOS" ) == true );
    assert ( t0 . insert ( "PA2" ) == true );
    assert ( t0 . insert ( "PA2" ) == false );
    assert ( t0 . insert ( "CAO" ) == true );
    assert ( t0 . insert ( "LIN" ) == true );
    assert ( t0 . insert ( "AAG" ) == true );
    assert ( t0 . insert ( "AG1" ) == true );
    assert ( t0 . insert ( "ZDM" ) == true );
    assert ( t0 . insert ( "FOO" ) == true );

    assert ( t0 . erase ( "CAO" ) == true );
    assert ( t0 . erase ( "CANNOT_ERASED" ) == false );
    assert ( t0 . erase ( "PA1" ) == true );
    assert ( t0 . erase ( "CAO" ) == false );
    assert ( t0 . erase ( "LIN" ) == true );
    assert ( t0 . erase ( "AAG" ) == true );
    assert ( t0 . erase ( "AG1" ) == true );
    assert ( t0 . erase ( "FOO" ) == true );
    assert ( t0 . erase ( "PA2" ) == true );
    assert ( t0 . erase ( "ZDM" ) == true );
    assert ( t0 . erase ( "UOS" ) == true );

    assert ( t0 . insert ( "PA1" ) == true );
    assert ( t0 . insert ( "UOS" ) == true );
    assert ( t0 . insert ( "PA2" ) == true );
    assert ( t0 . insert ( "PA2" ) == false );
    assert ( t0 . insert ( "CAO" ) == true );
    assert ( t0 . insert ( "LIN" ) == true );
    assert ( t0 . insert ( "AAG" ) == true );
    assert ( t0 . insert ( "AG1" ) == true );
    assert ( t0 . insert ( "ZDM" ) == true );

    assert ( t0 . erase ( "UOS" ) == true );
    assert ( t0 . erase ( "PA2" ) == true );
    assert ( t0 . erase ( "ZDM" ) == true );
    assert ( t0 . erase ( "PA1" ) == true );
    assert ( t0 . erase ( "AAG" ) == true );
    assert ( t0 . erase ( "AG1" ) == true );
    assert ( t0 . erase ( "LIN" ) == true );
    assert ( t0 . erase ( "CAO" ) == true );

    assert ( t0 . insert ( "PA1" ) == true );
    assert ( t0 . insert ( "CAO" ) == true );
    assert ( t0 . insert ( "UOS" ) == true );
    assert ( t0 . insert ( "PA2" ) == true );
    assert ( t0 . insert ( "PA2" ) == false );
    assert ( t0 . insert ( "LIN" ) == true );
    assert ( t0 . insert ( "AAG" ) == true );
    assert ( t0 . insert ( "AG1" ) == true );
    assert ( t0 . insert ( "ZDM" ) == true );

    assert ( t0 . erase ( "PA1" ) == true );
    assert ( t0 . erase ( "ZDM" ) == true );
    assert ( t0 . erase ( "UOS" ) == true );
    assert ( t0 . erase ( "PA2" ) == true );
    assert ( t0 . erase ( "AG1" ) == true );
    assert ( t0 . erase ( "CAO" ) == true );
    assert ( t0 . erase ( "AAG" ) == true );
    assert ( t0 . erase ( "LIN" ) == true );


    assert ( t0 . insert ( "20" ) == true );
    assert ( t0 . insert ( "10" ) == true );
    assert ( t0 . insert ( "5" ) == true );
    assert ( t0 . insert ( "15" ) == true );
    assert ( t0 . insert ( "17" ) == true );
    assert ( t0 . insert ( "13" ) == true );
    assert ( t0 . insert ( "14" ) == true );
    assert ( t0 . insert ( "11" ) == true );
    assert ( t0 . insert ( "12" ) == true );
    assert ( t0 . insert ( "3" ) == true );
    assert ( t0 . insert ( "7" ) == true );
    assert ( t0 . insert ( "25" ) == true );

    assert ( t0 . erase ( "10" ) == true );
    assert ( t0 . erase ( "25" ) == true );
    assert ( t0 . erase ( "20" ) == true );
    assert ( t0 . erase ( "17" ) == true );
    }
};
 
int main ( )
{
  CTester t;
  t.test();
 
  return EXIT_SUCCESS;
}
