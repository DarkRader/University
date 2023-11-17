#ifndef __PROGTEST__
#include <cassert>
#include <cstdarg>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <array>
#include <random>
#include <type_traits>

// We use std::set as a reference to check our implementation.
// It is not available in progtest :)
#include <set>

template < typename T >
struct Ref {
    size_t size() const { return _data.size(); }
    const T* find(const T& value) const {
        auto it = _data.find(value);
        if (it == _data.end()) return nullptr;
        return &*it;
    }
    bool insert(const T& value) { return _data.insert(value).second; }
    bool erase(const T& value) { return _data.erase(value); }

    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

private:
    std::set<T> _data;
};

#endif


namespace config {
    // Enable to check that the tree is AVL balanced.
    inline constexpr bool CHECK_DEPTH = false;

    // Disable if your implementation does not have parent pointers
    inline constexpr bool PARENT_POINTERS = false;
}

template < typename T >
struct Tree {
    class Node {
    public:
        Node(void) {}
        ~Node(void) {
            delete m_L;
            delete m_R;
        }

        Node(T key) {
            m_key = key;
        }

        int m_depth = 0;
        size_t m_subTreeSize = 0;
        T m_key;
        Node * m_L = nullptr;
        Node * m_R = nullptr;
    };
    Node * m_root = nullptr;

    size_t size() const {
        return m_root->m_subTreeSize;
    }

    size_t getSizeSubTree(Node * node) const {
        if(node != nullptr) {
            return node->m_subTreeSize;
        }
        return 0;
    }

    int getDepthSize(Node * node) const {
        if(node != nullptr) {
            return node->m_depth;
        }
        return 0;
    }

    int maxDepth(Node * leftNode, Node * rightNode) {
        if(getDepthSize(leftNode) < getDepthSize(rightNode)) {
            return getDepthSize(rightNode);
        } else {
            return getDepthSize(leftNode);
        }
    }

    Node * minValue(Node * node) {
        if(node->m_L == nullptr) {
            return node;
        } else {
            return minValue(node->m_L);
        }
    }

    const T* find(const T& value) const {
        Node * node = findValue(m_root, value);

        if(!node) {
            return nullptr;
        } else {
            return &(node->m_key);
        }
    }

    Node * findValue(Node * node, T key) const {
        if(node == nullptr) {
            return nullptr;
        }

        if(key == node->m_key) {
            return node;
        } else if(key < node->m_key) {
            return findValue(node->m_L, key);
        } else {
            return findValue(node->m_R, key);
        }
    }


    bool insert(T value) {
        bool exist = true;
        m_root = doInsert(m_root, value, exist);

        if(exist) {
            return true;
        } else {
            return false;
        }
    }

    Node * doInsert (Node * node, T key, bool &exist) {
        if(node == nullptr) {
            node = new Node(key);
            node->m_depth = 1;
            node->m_subTreeSize++;
            return node;
        }

        if(key < node->m_key) {
            node->m_L = doInsert(node->m_L, key, exist);
            if(!exist) {
                return node;
            }
            node->m_subTreeSize++;
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        } else if(key > node->m_key) {
            node->m_R = doInsert(node->m_R, key, exist);
            if(!exist) {
                return node;
            }
            node->m_subTreeSize++;
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        } else if(key == node->m_key) {
            exist = false;
            return node;
        }

        return node;
    }

    bool erase(const T& value) {
        bool exist = false;
        m_root = del(m_root, value, exist);

        if(exist) {
            return true;
        } else {
            return false;
        }
    }

    Node * del(Node * node, T key, bool &exist) {
        if(node == nullptr) {
            return nullptr;
        } else if(key < node->m_key) {
            node->m_L = del(node->m_L, key, exist);
            if(!exist) {
                return node;
            }
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
//            node = rotationTree(node);
        } else if(key > node->m_key) {
            node->m_R = del(node->m_R, key, exist);
            if(!exist) {
                return node;
            }
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
//            node = rotationTree(node);
        } else if(key == node->m_key) {
            exist = true;
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
            Node * tmpNode = minValue(node->m_R);
            node->m_key = tmpNode->m_key;
            node->m_R = del(node->m_R, tmpNode->m_key, exist);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
//            node = rotationTree(node);
        }
        return node;
    }


    Node * rotationTree(Node * node) {
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

    Node * rotateLeft(Node * node) {
        Node * rotateNode = node->m_R;
        node->m_R = rotateNode->m_L;
        rotateNode->m_L = node;
        node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
        node->m_subTreeSize = getSizeSubTree(node->m_L) + getSizeSubTree(node->m_R) + 1;
        rotateNode->m_depth = maxDepth(rotateNode->m_R, node) + 1;
        rotateNode->m_subTreeSize = getSizeSubTree(rotateNode->m_L) + getSizeSubTree(rotateNode->m_R) + 1;
        return rotateNode;
    }

    Node * rotateRight(Node * node) {
        Node * rotateNode = node->m_L;
        node->m_L = rotateNode->m_R;
        rotateNode->m_R = node;
        node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
        node->m_subTreeSize = getSizeSubTree(node->m_L) + getSizeSubTree(node->m_R) + 1;
        rotateNode->m_depth = maxDepth(rotateNode->m_L, node) + 1;
        rotateNode->m_subTreeSize = getSizeSubTree(rotateNode->m_L) + getSizeSubTree(rotateNode->m_R) + 1;
        return rotateNode;
    }

    // Needed to test the structure of the tree.
    // Replace Node with the real type of your nodes
    // and implementations with the ones matching
    // your attributes.
    struct TesterInterface {
        static const Node *root(const Tree *t) { return t->m_root; }
        static const Node *parent(const Node *n) { return nullptr; }
        static const Node *right(const Node *n) { return n->m_R; }
        static const Node *left(const Node *n) { return n->m_L; }
        static const T& value(const Node *n) { return n->m_key; }
    };
};


#ifndef __PROGTEST__

struct TestFailed : std::runtime_error {
    using std::runtime_error::runtime_error;
};

std::string fmt(const char *f, ...) {
    va_list args1;
    va_list args2;
    va_start(args1, f);
    va_copy(args2, args1);

    std::string buf(vsnprintf(nullptr, 0, f, args1), '\0');
    va_end(args1);

    vsnprintf(buf.data(), buf.size() + 1, f, args2);
    va_end(args2);

    return buf;
}

template < typename T >
struct Tester {
    Tester() = default;

    void size() const {
        size_t r = ref.size();
        size_t t = tested.size();
        if (r != t) throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
    }

    void find(const T& x) const {
        auto r = ref.find(x);
        auto t = tested.find(x);
        bool found_r = r != nullptr;
        bool found_t = t != nullptr;

        if (found_r != found_t) _throw("Find mismatch", found_r);
        if (found_r && *t != x) throw TestFailed("Find: found different value");
    }

    void insert(const T& x, bool check_tree_ = false) {
        auto succ_r = ref.insert(x);
        auto succ_t = tested.insert(x);
        if (succ_r != succ_t) _throw("Insert mismatch", succ_r);
        size();
        if (check_tree_) check_tree();
    }

    void erase(const T& x, bool check_tree_ = false) {
        bool succ_r = ref.erase(x);
        auto succ_t = tested.erase(x);
        if (succ_r != succ_t) _throw("Erase mismatch", succ_r);
        size();
        if (check_tree_) check_tree();
    }

    struct NodeCheckResult {
        const T* min = nullptr;
        const T* max = nullptr;
        int depth = -1;
        size_t size = 0;
    };

    void check_tree() const {
        using TI = typename Tree<T>::TesterInterface;
        auto ref_it = ref.begin();
        bool check_value_failed = false;
        auto check_value = [&](const T& v) {
            if (check_value_failed) return;
            check_value_failed = (ref_it == ref.end() || *ref_it != v);
            if (!check_value_failed) ++ref_it;
        };

        auto r = check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);
        size_t t_size = tested.size();

        if (t_size != r.size) throw TestFailed(
                    fmt("Check tree: size() reports %zu but expected %zu.", t_size, r.size));

        if (check_value_failed) throw TestFailed(
                    "Check tree: element mismatch");

        size();
    }

    template < typename Node, typename F >
    NodeCheckResult check_node(const Node* n, const Node* p, F& check_value) const {
        if (!n) return {};

        using TI = typename Tree<T>::TesterInterface;
        if constexpr(config::PARENT_POINTERS) {
            if (TI::parent(n) != p) throw TestFailed("Parent mismatch.");
        }

        auto l = check_node(TI::left(n), n, check_value);
        check_value(TI::value(n));
        auto r = check_node(TI::right(n), n, check_value);

        if (l.max && !(*l.max < TI::value(n)))
            throw TestFailed("Max of left subtree is too big.");
        if (r.min && !(TI::value(n) < *r.min))
            throw TestFailed("Min of right subtree is too small.");

        if (config::CHECK_DEPTH && abs(l.depth - r.depth) > 1) throw TestFailed(fmt(
                    "Tree is not avl balanced: left depth %i and right depth %i.",
                    l.depth, r.depth
            ));

        return {
                l.min ? l.min : &TI::value(n),
                r.max ? r.max : &TI::value(n),
                std::max(l.depth, r.depth) + 1, 1 + l.size + r.size
        };
    }

    static void _throw(const char *msg, bool s) {
        throw TestFailed(fmt("%s: ref %s.", msg, s ? "succeeded" : "failed"));
    }

    Tree<T> tested;
    Ref<T> ref;
};


void test_insert() {
    Tester<int> t;

    for (int i = 0; i < 10; i++) t.insert(i, true);
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
    for (int i = -10; i < 20; i++) t.find(i);
}

void test_erase() {
    Tester<int> t;

    for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = 3; i < 22; i += 2) t.erase(i, true);
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = 0; i < 10; i++) t.insert((1 + i * 13) % 17 - 8, true);
    for (int i = -10; i < 20; i++) t.find(i);

    for (int i = -4; i < 10; i++) t.erase(i, true);
    for (int i = -10; i < 20; i++) t.find(i);
}

enum RandomTestFlags : unsigned {
    SEQ = 1, NO_ERASE = 2, CHECK_TREE = 4
};

void test_random(size_t size, unsigned flags = 0) {
    Tester<size_t> t;
    std::mt19937 my_rand(24707 + size);

    bool seq = flags & SEQ;
    bool erase = !(flags & NO_ERASE);
    bool check_tree = flags & CHECK_TREE;

    for (size_t i = 0; i < size; i++)
        t.insert(seq ? 2*i : my_rand() % (3*size), check_tree);

    t.check_tree();

    for (size_t i = 0; i < 3*size + 1; i++) t.find(i);

    for (size_t i = 0; i < 30*size; i++) switch (my_rand() % 5) {
            case 1: t.insert(my_rand() % (3*size), check_tree);
                break;
            case 2: if (erase) t.erase(my_rand() % (3*size), check_tree);
                break;
            default:
                t.find(my_rand() % (3*size));
        }

    t.check_tree();
}

int main() {
    try {
        std::cout << "Insert test..." << std::endl;
        test_insert();

        std::cout << "Erase test..." << std::endl;
        test_erase();

        std::cout << "Tiny random test..." << std::endl;
        test_random(20, CHECK_TREE);

        std::cout << "Small random test..." << std::endl;
        test_random(200, CHECK_TREE);

        std::cout << "Big random test..." << std::endl;
        test_random(50'000);

        std::cout << "Big sequential test..." << std::endl;
        test_random(50'000, SEQ);

        std::cout << "All tests passed." << std::endl;
    } catch (const TestFailed& e) {
        std::cout << "Test failed: " << e.what() << std::endl;
    }
}

#endif


