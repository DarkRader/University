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
        return m_products.size();
    }
    
    CNode * getRoot(void) const {
        return m_root;
    }
    
    size_t getSizeSubTree(CNode * node) const {
        if(node != nullptr) {
            return node->m_subTreeSize;
        }
        return 0;
    }
    
    int getDepthSize(CNode * node) const {
        if(node != nullptr) {
            return node->m_depth;
        }
        return 0;
    }
    
    int maxDepth(CNode * leftNode, CNode * rightNode) {
        if(getDepthSize(leftNode) < getDepthSize(rightNode)) {
            return getDepthSize(rightNode);
        } else {
            return getDepthSize(leftNode);
        }
    }
    
    CNode * minValue(CNode * node) {
        if(node->m_L == nullptr) {
            return node;
        } else {
            return minValue(node->m_L);
        }
    }
    
    void insertOrDelProd(const Product& p, size_t amount) {
        auto it = m_products.find(p);
        if(it == m_products.end()) {
            std::pair<size_t, Product> key = {amount, p};
            m_products.insert({p, amount});
            m_root = insert(m_root, key);
        } else {
            std::pair<size_t, Product> key = {it->second, p};
            m_root = del(m_root, key);
            key = {it->second + amount, p};
            m_root = insert(m_root, key);
            it->second = it->second + amount;
        }
    }
    
    CNode * del (CNode * node, std::pair<size_t, Product> key) {
        if(node == nullptr) {
            return nullptr;
        } else if(key < node->m_key) {
            node->m_L = del(node->m_L, key);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
        } else if(key > node->m_key) {
            node->m_R = del(node->m_R, key);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
        } else if(key == node->m_key) {
            if(node->m_R == nullptr && node->m_L == nullptr) {
                delete node;
                return nullptr;
            } else if(node->m_L == nullptr) {
                auto tmp = node->m_R;
                node->m_R = nullptr;
                delete node;
                return tmp;
            } else if(node->m_R == nullptr) {
                auto tmp = node->m_L;
                node->m_L = nullptr;
                delete node;
                return tmp;
            }
            CNode * tmpNode = minValue(node->m_R);
            node->m_key = tmpNode->m_key;
            node->m_R = del(node->m_R, tmpNode->m_key);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
        }
        return node;
    }
    
    CNode * insert (CNode * node, std::pair<size_t, Product> key) {
        if(node == nullptr) {
            node = new CNode(key.second, key.first);
            node->m_depth = 1;
            node->m_subTreeSize++;
            return node;
        }
       
        if(key < node->m_key) {
            node->m_subTreeSize++;
            node->m_L = insert(node->m_L, key);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        } else if(key > node->m_key) {
            node->m_subTreeSize++;
            node->m_R = insert(node->m_R, key);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        }
        return node;
    }
    
    CNode * rotationTree(CNode * node) {
        if(2 <= getDepthSize(node->m_R) - getDepthSize(node->m_L)) {
            if(0 > getDepthSize(node->m_R->m_R) - getDepthSize(node->m_R->m_L)) {
                node->m_R = rotateRight(node->m_R);
            }
            node = rotateLeft(node);
        } else if(-2 >= getDepthSize(node->m_R) - getDepthSize(node->m_L)) {
            if(0 < getDepthSize(node->m_L->m_R) - getDepthSize(node->m_L->m_L)) {
                node->m_L = rotateLeft(node->m_L);
            }
            node = rotateRight(node);
        }
        return node;
    }
    
    CNode * rotateLeft(CNode * node) {
        CNode * rotateNode = node->m_R;
        node->m_R = rotateNode->m_L;
        rotateNode->m_L = node;
        node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
        node->m_subTreeSize = getSizeSubTree(node->m_L) + getSizeSubTree(node->m_R) + 1;
        rotateNode->m_depth = maxDepth(rotateNode->m_R, node) + 1;
        rotateNode->m_subTreeSize = getSizeSubTree(rotateNode->m_L) + getSizeSubTree(rotateNode->m_R) + 1;
        return rotateNode;
    }

    CNode * rotateRight(CNode * node) {
        CNode * rotateNode = node->m_L;
        node->m_L = rotateNode->m_R;
        rotateNode->m_R = node;
        node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
        node->m_subTreeSize = getSizeSubTree(node->m_L) + getSizeSubTree(node->m_R) + 1;
        rotateNode->m_depth = maxDepth(rotateNode->m_L, node) + 1;
        rotateNode->m_subTreeSize = getSizeSubTree(rotateNode->m_L) + getSizeSubTree(rotateNode->m_R) + 1;
        return rotateNode;
    }
    
    size_t findIndProd(const Product prod) const {
        auto it = m_products.find(prod);
        if(it == m_products.end()) {
            throw std:: out_of_range("non-existing product");
        } else {
            std::pair<size_t, Product> key = {it->second, it->first};
            return rankOfProduct(m_root, key) + 1;
        }
    }
    
    size_t rankOfProduct (CNode * node, std::pair<size_t, Product> key) const {
        if(node->m_key == key) {
            return getSizeSubTree(node->m_R);
        } else if(node->m_key < key) {
            return rankOfProduct(node->m_R, key);
        } else {
            return rankOfProduct(node->m_L, key) + getSizeSubTree(node->m_R) + 1;
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
    
    Product & productInRank (size_t rank) const {
        CNode * node = indProd(m_root, rank);
        return node->m_key.second;
    }
    
    size_t sellProd (size_t rank) const {
        CNode * node = indProd(m_root, rank);
        return node->m_key.first;
    }
    
    CNode * indProd(CNode * node, size_t rank) const {
        if(rank < getSizeSubTree(node->m_R)) {
            node = indProd(node->m_R, rank);
        } else if(rank > getSizeSubTree(node) - getSizeSubTree(node->m_L) - 1) {
            rank = rank - getSizeSubTree(node->m_R) - 1;
            node = indProd(node->m_L, rank);
        }
        return node;
    }
    
protected:
    //helping class for basic class CTree
    class CNode {
    public:
        CNode(void) {}
        ~CNode(void) {
            delete m_L;
            delete m_R;
        }
        
        CNode(Product key, size_t amount) {
            m_key = {amount, key};
        }
        
        int m_depth = 0;
        size_t m_subTreeSize = 0;
        std::pair<size_t, Product> m_key;
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
    };
    std::unordered_map<Product, size_t> m_products;
    CNode * m_root = nullptr;
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
        if(rank  > tree.getSizeTree()) {
            throw std:: out_of_range("size out of range");
        }
        return tree.productInRank(rank - 1);
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
void test3() {
    Bestsellers<int> b;
    b.sell(4, 4);
    b.sell(2, 2);
    b.sell(6, 6);
    b.sell(1, 1);
    b.sell(3, 3);
    b.sell(5, 5);
    b.sell(7, 7);


    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);

    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);


    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
}

void test4() {
    Bestsellers<int> b;
    
    b.sell(4, 4);
    b.sell(2, 2);
    b.sell(6, 6);
    b.sell(1, 1);
    b.sell(3, 3);
    b.sell(5, 5);
    b.sell(7, 7);
    
    
    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
    
    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
    
    
    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
    
    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
    
    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
    
    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
    
    b.sell(4, 1);
    b.sell(2, 1);
    b.sell(6, 1);
    b.sell(1, 1);
    b.sell(3, 1);
    b.sell(5, 1);
    b.sell(7, 1);
    
    b.sold(1);
    b.sold(2);
    b.sold(3);
    b.sold(4);
    b.sold(5);
    b.sold(6);
    b.sold(7);
    
    b.sold(1);
    b.sold(2);
    b.sold(3);
    b.sold(4);
    b.sold(5);
    b.sold(6);
    b.sold(7);
    
    b.product(1);
    b.product(2);
    b.product(3);
    b.product(4);
    b.product(5);
    b.product(6);
    b.product(7);
    
    b.rank(4);
    b.rank(2);
    b.rank(6);
    b.rank(1);
    b.rank(3);
    b.rank(5);
    b.rank(7);
    
}

int main() {
  test1();
  test2();
  test3();
  test4();
}

#endif


