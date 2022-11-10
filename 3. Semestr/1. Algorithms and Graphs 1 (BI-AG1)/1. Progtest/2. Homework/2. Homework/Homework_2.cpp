#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>

#endif

//implement BVSShow
//implement BVSMin +
//implement BVSMax +
//implement BVSPred +
//implement BVSSuc +
//implement BVSFind
//implement BVSInsert +
//implement BVSDelete

//template<class T>
//template < typename Product >
class CTree {
public:
    CTree(void) = default;
    ~CTree(void) {
        delete m_root;
    }
    
    size_t getSizeTree(void) const {
        return m_treeSize;
    }
    
    bool insert (std::string product, size_t amount) {
        
        if(!m_first) {
            auto * tmp = new CNode(product, amount);
            m_first = m_last = m_root = m_min = m_max = tmp;
            tmp->m_index = 0;
            m_treeSize++;
            return true;
        }
        
        auto ** curPoz = &m_root;
        
        while(*curPoz) {
            if((*curPoz)->m_key == product) {
                return false;
            } else if((*curPoz)->m_amount > amount) {//insert in left son
                curPoz = &((*curPoz)->m_L);
            } else {
                curPoz = &((*curPoz)->m_R);
            }
        }
        
        *curPoz = new CNode(product, amount);
        
        if((*curPoz)->m_amount > m_max->m_amount) {
            m_max = *curPoz;
        } else if ((*curPoz)->m_amount < m_min->m_amount) {
            m_min = *curPoz;
        }
        
        m_last->m_son = *curPoz;
        (*curPoz)->m_father = m_last;
        m_last = *curPoz;
        
        m_treeSize++;
        
        changeIndex();
        
        return true;
    }
    
    void changeIndex () {
        auto ** curPoz = &m_last;
        
        
    }
    
    size_t rankOfProduct (std::string product) {
        
        
        return 0;
    }
    
protected:
    //helping class for basic class CTree
    class CNode {
    public:
        CNode(std::string key, size_t amount) : m_key(key), m_amount(amount) {}
        std::string m_key;
        size_t m_amount;
        size_t m_index;
        
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
        CNode * m_father = nullptr;
        CNode * m_son = nullptr;
    };
    CNode * m_root = nullptr;
    CNode * m_first = nullptr;
    CNode * m_last = nullptr;
    CNode * m_max = nullptr;
    CNode * m_min = nullptr;
    size_t m_treeSize = 0;
    //std::unordered_set<std::pair<size_t, std::string>> m_products;
    
};

// TODO implement
template < typename Product >
struct Bestsellers {
    //std::unordered_map<std::string, size_t> listProducts;
    CTree tree;
    
   //The total number of tracked products
    size_t products() const {
        return tree.getSizeTree();
    }

    void sell(const Product& p, size_t amount) {
        tree.insert(p, amount);
    }

  // The most sold product has rank 1
    size_t rank(const Product& p) const {
        return 829;
    }
    
    const Product& product(size_t rank) const {
        
        return product(2142);
    }

  // How many copies of product with given rank were sold
    size_t sold(size_t rank) const {
        
        return 42142;
    }
  // The same but sum over interval of products (including from and to)
  // It must hold: sold(x) == sold(x, x)
    size_t sold(size_t from, size_t to) const {
        
        return 21421;
    }

  // Bonus only, ignore if you are not interested in bonus
  // The smallest (resp. largest) rank with sold(rank) == sold(r)
  size_t first_same(size_t r) const { return 0; }
  size_t last_same(size_t r) const { return 0; }
};

#ifndef __PROGTEST__

void test1() {
  Bestsellers<std::string> T;
  T.sell("coke", 32);
  T.sell("bread", 1);
  assert(T.products() == 2);
  T.sell("ham", 2);
  T.sell("mushrooms", 12);

  assert(T.products() == 4);
  assert(T.rank("ham") == 3);
  assert(T.rank("coke") == 1);
  assert(T.sold(1, 3) == 46);
  assert(T.product(2) == "mushrooms");

  T.sell("ham", 11);
  assert(T.products() == 4);
  assert(T.product(2) == "ham");
  assert(T.sold(2) == 13);
  assert(T.sold(2, 2) == 13);
  assert(T.sold(1, 2) == 45);
}

void test2() {
# define CATCH(expr) \
  try { expr; assert(0); } catch (const std::out_of_range&) { assert(1); };

  Bestsellers<std::string> T;
  T.sell("coke", 32);
  T.sell("bread", 1);

  CATCH(T.rank("ham"));
  CATCH(T.product(3));
  CATCH(T.sold(0));
  CATCH(T.sold(9));
  CATCH(T.sold(0, 1));
  CATCH(T.sold(3, 2));
  CATCH(T.sold(1, 9));

#undef CATCH
}

int main() {
  test1();
  test2();
}

#endif


