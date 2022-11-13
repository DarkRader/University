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

template < typename Product >
class CTree {
protected:
    class CNode;
public:
    CTree(void) = default;
    ~CTree(void) {
        delete m_root;
    }
    
    size_t getSizeTree(void) const {
        return m_root->m_subTreeSize;
    }
    
    CNode * getRoot(void) const {
        return m_root;
    }
    
    CNode * minValue(CNode * node) {
        if(node->m_L == nullptr) {
            return node;
        } else {
            return minValue(node->m_L);
        }
    }
    
    CNode * maxValue(CNode * node) {
        if(node->m_R == nullptr) {
            return node;
        } else {
            return maxValue(node->m_R);
        }
    }
    
    void insertOrDelProd(const Product& p, size_t amount) {
        auto it = m_products.find(p);
        if(it == m_products.end()) {
            std::pair<size_t, Product> key = {amount, p};
            m_products.insert({p, amount});
            m_root = insert(m_root, key);
        } else {
            std::pair<size_t, Product> key = {it->second + amount, p};
            del(m_root, key);
            m_root = insert(m_root, key);
        }
    }
    
    size_t findIndProd(const Product prod) const {
        auto it = m_products.find(prod);
        if(it == m_products.end()) {
            throw std:: out_of_range("non-existing product");
        } else {
            std::pair<size_t, Product> indProd = {it->second, it->first};
            return rankOfProduct(indProd);
        }
    }
    
    CNode * del (CNode * node, std::pair<size_t, Product> key) {
        if(node == nullptr) {
            return nullptr;
        } else if(key < node->m_key) {
            node->m_L = del(node->m_L, key);
//            if(node->m_L && node->m_L->m_father) {
//                node->m_L->m_father = node;
//            }
            node->m_subTreeSize--;
        } else if(key > node->m_key) {
            node->m_R = del(node->m_R, key);
//            if(node->m_R && node->m_R->m_father) {
//                node->m_R->m_father = node;
//            }
            node->m_subTreeSize--;
        } else if(key == node->m_key) {
            if(node->m_R == nullptr && node->m_L == nullptr) {
                return nullptr;
            } else if(node->m_L == nullptr) {
                return node->m_R;
            } else if(node->m_R == nullptr) {
                return node->m_L;
            }
            CNode * tmpNode = minValue(node->m_R);
            node->m_key = tmpNode->m_key;
            node->m_R = del(node->m_R, key);
            node->m_subTreeSize--;
        }
        return node;
    }
    
    CNode * insert (CNode * node, std::pair<size_t, Product> key) {
        if(node == nullptr) {
            node = new CNode(key.second, key.first);
            //node->m_father = father;
            node->m_subTreeSize++;
            return node;
        }
        
        if(key < node->m_key) {
            node->m_subTreeSize++;
            node->m_L = insert(node->m_L, key);
        } else if(key > node->m_key) {
            node->m_subTreeSize++;
            node->m_R = insert(node->m_R, key);
        }
        return node;
    }
    
    size_t rankOfProduct (std::pair<size_t, Product> product) const {
        auto * curPoz = m_root;
        
        size_t ind = 0;
        while(curPoz->m_key != product) {
            if(curPoz->m_key > product) {
                if(curPoz->m_R) {
                    ind = ind + curPoz->m_R->m_subTreeSize;
                }
                ind++;
                if(curPoz->m_L) {
                    curPoz = curPoz->m_L;
                }
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
    
    size_t fromToSell(size_t from, size_t to) const {
        
        size_t sum = 0;
        
        while(from <= to) {
            sum = sum + sellProd(to - 1);
            to--;
        }
        
        return sum;
    }
    
//    Product & indexProd (CNode * node, size_t rank) const {
//        if((node->m_R) && (rank < node->m_R->m_subTreeSize)) {
//            rank = indexProd(node->m_R, rank);
//        } else if(node->m_L && (rank > (node->m_subTreeSize - node->m_L->m_subTreeSize - 1))) {
//            rank = indexProd(node->m_L, rank - node->m_R->m_subTreeSize - 1);
//        } else {
//            return node;
//        }
//
//        return node->m_key.second;
//    }
    
    Product & indexProd (size_t rank) const {
        auto * curPoz = m_root;
        while(true) {
            if((curPoz->m_R) && (rank < curPoz->m_R->m_subTreeSize)) {
                curPoz = curPoz->m_R;
            } else if(curPoz->m_L && (rank > (curPoz->m_subTreeSize - curPoz->m_L->m_subTreeSize - 1))) {
                if(curPoz->m_R) {
                    rank = rank - curPoz->m_R->m_subTreeSize - 1;
                } else {
                    rank = rank - 1;
                }
                curPoz = curPoz->m_L;
            } else {
                break;
            }
        }

        return curPoz->m_key.second;
    }
    
    size_t sellProd (size_t rank) const {
        auto * curPoz = m_root;
        while(true) {
            if((curPoz->m_R) && (rank < curPoz->m_R->m_subTreeSize)) {
                curPoz = curPoz->m_R;
            } else if(curPoz->m_L && (rank > (curPoz->m_subTreeSize - curPoz->m_L->m_subTreeSize - 1))) {
                if(curPoz->m_R) {
                    rank = rank - curPoz->m_R->m_subTreeSize - 1;
                } else {
                    rank = rank - 1;
                }
                curPoz = curPoz->m_L;
            } else {
                break;
            }
        }
        
        return curPoz->m_key.first;
    }
    
    
protected:
    //helping class for basic class CTree
    class CNode {
    public:
        CNode(Product key, size_t amount) {
            m_key = {amount, key};
        }
        size_t m_subTreeSize = 0;
        std::pair<size_t, Product> m_key;
        
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
        //CNode * m_father = nullptr;
    };
    std::unordered_map<Product, size_t> m_products;
    
    CNode * m_root = nullptr;
    CNode * m_first = nullptr;
    CNode * m_last = nullptr;
};

// TODO implement
template < typename Product >
struct Bestsellers {
    CTree<Product> tree;
    
   //The total number of tracked products
    size_t products() const {
        return tree.getSizeTree();
    }

    void sell(const Product& p, size_t amount) {
        tree.insertOrDelProd(p, amount);
    }

  // The most sold product has rank 1
    size_t rank(const Product& p) const {
        return tree.findIndProd(p);
    }
    
    const Product& product(size_t rank) const {
        if(rank + 1 > tree.getSizeTree()) {
            throw std:: out_of_range("size out of range");
        }
        return tree.indexProd(rank - 1);
    }

  // How many copies of product with given rank were sold
    size_t sold(size_t rank) const {
        if(rank == 0 || tree.getSizeTree() < rank) {
            throw std:: out_of_range("rank out of range");
        }
        return tree.sellProd(rank - 1);
    }
  // The same but sum over interval of products (including from and to)
  // It must hold: sold(x) == sold(x, x)
    size_t sold(size_t from, size_t to) const {
        if(from == 0 || from > to || to > tree.getSizeTree() || from > tree.getSizeTree()) {
            throw std:: out_of_range("sold out of range");
        }
        return tree.fromToSell(from, to);
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


