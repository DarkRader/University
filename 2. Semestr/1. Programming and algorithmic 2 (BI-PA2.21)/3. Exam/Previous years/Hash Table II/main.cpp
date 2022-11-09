#include <string>
#include <iostream>
 
using namespace std;
 
struct TItem
{
    TItem(string key, string val, TItem *nextHash, TItem *nextOrd, TItem *prevOrd)
        : m_Key(key), m_Val(val), m_NextHash(nextHash), m_NextOrder(nextOrd), m_PrevOrder(prevOrd) {}
 
    string m_Key, m_Val;
    TItem *m_NextHash, *m_NextOrder, *m_PrevOrder;
};
 
class CHash
{
public:
    CHash(int m) : m_Table(NULL), m_Size(m), m_FirstOrder(NULL), m_LastOrder(NULL)
    {
        m_Table = new TItem *[m];
        for (int i = 0; i < m; i++)
            m_Table[i] = NULL;
    }
    ~CHash()
    {
        for (int i = 0; i < m_Size; i++)
        {
            TItem *save, *it = m_Table[i];
            while (it)
            {
                save = it;
                it = it->m_NextHash;
                delete save;
            }
        }
        delete[] m_Table;
    }
    CHash(CHash &) = delete;
    CHash &operator=(CHash &) = delete;
 
    bool Ins(string key, string val)
    {
        TItem ** elem = &(m_Table[hashFn(key)]);
        while(*elem)
        {
            if((*elem)->m_Key == key)
                return false;
            elem = &((*elem)->m_NextHash);
        }
        TItem *new_elem = new TItem(key, val, m_Table[hashFn(key)], NULL, m_LastOrder);
        if(m_LastOrder)
            m_LastOrder->m_NextOrder = new_elem;
        m_Table[hashFn(key)] = new_elem;
        m_LastOrder = new_elem;
        if(!m_FirstOrder)
            m_FirstOrder = m_LastOrder;
    
        return true;
    }
    bool Del(string key)
    {
        TItem ** elem = &(m_Table[hashFn(key)]);
        if(!(*elem))
            return false;
        while(*elem)
        {
            if((*elem)->m_Key == key)
            {
                TItem * del = *elem;
                if(del->m_NextOrder)
                    del->m_NextOrder->m_PrevOrder = del->m_PrevOrder;
                else
                    m_LastOrder = m_LastOrder->m_PrevOrder;
                
                if(del->m_PrevOrder)
                    del->m_PrevOrder->m_NextOrder = del->m_NextOrder;
                else
                    m_FirstOrder = m_FirstOrder->m_NextOrder;
                
                delete del;
                return true;
            }
            elem = &((*elem)->m_NextHash);
        }
    
        return false;
    }
    bool IsSet(string key)
    {
        TItem *tmp = m_Table[hashFn(key)];
        while (tmp != NULL && tmp->m_Key != key)
            tmp = tmp->m_NextHash;
        if (tmp == NULL)
            return false;
        return true;
    }
    template <typename func>
    void ForEach(func f)
    {
        TItem *tmp = m_FirstOrder;
        while (tmp != NULL)
        {
            f(tmp);
            tmp = tmp->m_NextOrder;
        }
    }
 
private:
    TItem **m_Table;
    unsigned int m_Size;
    TItem *m_FirstOrder, *m_LastOrder;
    unsigned int hashFn(string &str)
    {
        std::hash<std::string> hash_fn;
        return hash_fn(str) % m_Size;
    }
};
 
int main(int argc, char **argv)
{
    CHash hashtable(100);
    hashtable.Ins("h1", "car");
    hashtable.Ins("h1", "phone");
    hashtable.Ins("h2", "field");
    hashtable.Ins("h3", "house");
    hashtable.Ins("h4", "tree");
 
    hashtable.ForEach([](TItem *it) {
        cout << it->m_Key << " - " << it->m_Val << endl;
    });
 
    return 0;
}
