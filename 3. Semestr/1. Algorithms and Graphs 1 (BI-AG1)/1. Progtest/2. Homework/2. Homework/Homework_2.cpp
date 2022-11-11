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

//how to implement indexing
//how to find key through amount

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
        return m_root->m_subTreeSize;
    }
    
    std::pair<size_t, std::string> getProdKey(const std::string prod) const {
        auto it = m_products.find(prod);
        std::pair<size_t, std::string> indProd = {it->second, it->first};
        return indProd;
    }
    
    bool insert (std::string product, size_t amount) {
        
        if(!m_first) {
            auto * tmp = new CNode(product, amount);
            m_first = m_last = m_root = m_min = m_max = tmp;
            tmp->m_subTreeSize++;
            m_products.insert({product, amount});
            return true;
        }

        auto ** curPoz = &m_root;
        auto ** prevPoz = curPoz;
        std::pair<size_t, std::string> curProd = {amount, product};

        while(*curPoz) {
            if((*curPoz)->m_key == curProd) {
                return false;
            } else if((*curPoz)->m_key > curProd) { //go in left son
                prevPoz = curPoz;
                curPoz = &((*curPoz)->m_L);
            } else {                                //go in right son
                prevPoz = curPoz;
                curPoz = &((*curPoz)->m_R);
            }
        }

        *curPoz = new CNode(product, amount);
        m_products.insert({product, amount});

        (*curPoz)->m_father = *prevPoz;
        m_last->m_nextProd = *curPoz;
        (*curPoz)->m_prevProd = m_last;
        m_last = *curPoz;
        (*curPoz)->m_subTreeSize++;
        updateSubTreeSize();
        
        return true;
    }
    
    void updateSubTreeSize() {
        auto ** curPoz = &m_last;
        
        while((*curPoz)->m_father) {
            (*curPoz) = (*curPoz)->m_father;
            (*curPoz)->m_subTreeSize++;
        }
    }
    
    size_t rankOfProduct (std::pair<size_t, std::string> product) const {
        auto * curPoz = m_root;
        
        size_t ind = 0;
        while(curPoz->m_key != product) {
            if(curPoz->m_key > product) {
                if(curPoz->m_R) {
                    ind = curPoz->m_R->m_subTreeSize;
                }
                ind++;
                curPoz = curPoz->m_L;
            } else if(curPoz->m_key < product) {
                if(curPoz->m_R) {
                    curPoz = curPoz->m_R;
                }
            }
        }
        
        if(curPoz->m_R) {
            return curPoz->m_R->m_subTreeSize + ind + 1;
        } else {
            return ind + 1;
        }
    }
    
    
protected:
    //helping class for basic class CTree
    class CNode {
    public:
        CNode(std::string key, size_t amount) {
            m_key = {amount, key};
        }
        size_t m_subTreeSize = 0;
        std::pair<size_t, std::string> m_key;
        
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
        CNode * m_father = nullptr;
        CNode * m_nextProd = nullptr;
        CNode * m_prevProd = nullptr;
    };
    std::unordered_map<std::string, size_t> m_products;
    
    CNode * m_root = nullptr;
    CNode * m_first = nullptr;
    CNode * m_last = nullptr;
    CNode * m_max = nullptr;
    CNode * m_min = nullptr;
    
};

// TODO implement
template < typename Product >
struct Bestsellers {
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
        std::pair<size_t, std::string> prod = tree.getProdKey(p);
        return tree.rankOfProduct(prod);
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


