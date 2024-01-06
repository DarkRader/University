#ifndef __PROGTEST__
#include <cassert>
#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <memory>
#include <array>
#include <random>

// We use std::vector as a reference to check our implementation.
// It is not available in progtest :)
#include <vector>

template < typename T >
struct Ref {
    size_t size() const { return _data.size(); }

    const T& operator [] (size_t index) const { return _data.at(index); }
    T& operator [] (size_t index) { return _data.at(index); }

    void insert(size_t index, T value) {
        if (index > _data.size()) throw std::out_of_range("oops");
        _data.insert(_data.begin() + index, std::move(value));
    }

    T erase(size_t index) {
        T ret = std::move(_data.at(index));
        _data.erase(_data.begin() + index);
        return ret;
    }

    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

private:
    std::vector<T> _data;
};

#endif


namespace config {
    inline constexpr bool PARENT_POINTERS = false;
    inline constexpr bool CHECK_DEPTH = true;
}

template < typename T >
struct Array {
public:
    // Nested class for tree nodes
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

    Array() = default;
    ~Array() {
        delete m_root;
    }

    // Check if the tree is empty
    bool empty() const {
        if(m_root) {
            return false;
        } else {
            return true;
        }
    }

    // Get the size of the tree (number of elements)
    size_t size() const {
        return m_root->m_subTreeSize;
    }

    // Access an element at a given index using the [] operator
    const T& operator [] (size_t index) const {
        return findSymbol(m_root, index);
    }

    // Access an element at a given index using the [] operator
    T& operator [] (size_t index) {
        return findSymbol(m_root, index);
    }

    // Recursive helper function to find an element by index
    T &findSymbol(Node * node, size_t ind) const {
        if(node == nullptr || ind >= node->m_subTreeSize) {
            throw std:: out_of_range("out of range in at");
        }

        if(node->m_L != nullptr) {
            size_t leftSize = node->m_L->m_subTreeSize;
            if(ind == leftSize) {
                return node->m_key;
            } else if(ind < leftSize) {
                return findSymbol(node->m_L, ind);
            } else {
                return findSymbol(node->m_R, ind - leftSize - 1);
            }
        } else {
            if(ind == 0) {
                return node->m_key;
            } else {
                return findSymbol(node->m_R, ind - 1);
            }
        }
    }

    // Get the size of a subtree rooted at a given node
    size_t getSizeSubTree(Node * node) const {
        if(node != nullptr) {
            return node->m_subTreeSize;
        }
        return 0;
    }

    // Get the depth of a subtree rooted at a given node
    int getDepthSize(Node * node) const {
        if(node != nullptr) {
            return node->m_depth;
        }
        return 0;
    }

    // Get the maximum depth between two subtrees
    int maxDepth(Node * leftNode, Node * rightNode) {
        if(getDepthSize(leftNode) < getDepthSize(rightNode)) {
            return getDepthSize(rightNode);
        } else {
            return getDepthSize(leftNode);
        }
    }

    // Find the minimum value node in a given subtree
    Node * minValue(Node * node) {
        if(node->m_L == nullptr) {
            return node;
        } else {
            return minValue(node->m_L);
        }
    }

    // Insert a new element at a given index
    void insert(size_t index, T value) {
        m_root = insertNode(m_root, value, index);
    }

    // Recursive helper function to insert a new element into the tree
    Node * insertNode(Node * node, T key, size_t ind) {
        if(node == nullptr) {
            node = new Node(key);
            node->m_depth = 1;
            node->m_subTreeSize++;
            return node;
        }

        size_t leftIndex;
        if(!node->m_L) {
            leftIndex = 0;
        } else {
            leftIndex = node->m_L->m_subTreeSize;
        }

        if(ind <= leftIndex) {
            node->m_subTreeSize++;
            node->m_L = insertNode(node->m_L, key, ind);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        } else {
            node->m_subTreeSize++;
            if(node->m_L) {
                node->m_R = insertNode(node->m_R, key, ind - leftIndex - 1);
            } else {
                node->m_R = insertNode(node->m_R, key, ind - 1);
            }
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        }

        return node;
    }


    // Remove an element at a given index
    T erase(size_t index) {
        T delVar;
        m_root = del(m_root,index, delVar);
        return delVar;
    }

    // Recursive helper function to remove an element from the tree
    Node * del(Node * node, size_t ind, T &delVar) {
        if(node == nullptr) {
            return nullptr;
        } else if((ind == 0 && !node->m_L) || (node->m_L && ind == node->m_L->m_subTreeSize)) {
            if(node->m_L == nullptr && node->m_R == nullptr) {
                delVar = node->m_key;
                delete node;
                return nullptr;
            } else if(node->m_L == nullptr) {
                auto tmp = node->m_R;
                node->m_R = nullptr;
                delVar = node->m_key;
                delete node;
                return tmp;
            } else if(node->m_R == nullptr) {
                auto tmp = node->m_L;
                node->m_L = nullptr;
                delVar = node->m_key;
                delete node;
                return tmp;
            }
            Node * tmpNode = minValue(node->m_R);
            T tmpDelVar =  node->m_key;
            node->m_key = tmpNode->m_key;
            node->m_R = del(node->m_R, 0, delVar);
            delVar = tmpDelVar;
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
            node = rotationTree(node);
        } else if((node->m_L == nullptr && ind < node->m_subTreeSize - 1) || (node->m_L && ind < node->m_L->m_subTreeSize)) {
            node->m_L = del(node->m_L, ind, delVar);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
            node = rotationTree(node);
        } else {
            if(node->m_L) {
                node->m_R = del(node->m_R, ind - node->m_L->m_subTreeSize - 1, delVar);
            } else {
                node->m_R = del(node->m_R, ind - 1, delVar);
            }
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
            node = rotationTree(node);
        }
        return node;
    }

    // Perform a rotation on a node to maintain balance
    Node * rotationTree(Node * node) {
        if (node == nullptr) {
            return nullptr;
        }

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

    // Rotate a node to the left
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

    // Rotate a node to the right
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

    // Structure for testing the Array class
    struct TesterInterface {
        static const Node *root(const Array *t) { return t->m_root; }
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

    size_t size() const {
        bool te = tested.empty();
        size_t r = ref.size();
        size_t t = tested.size();
        if (te != !t) throw TestFailed(fmt("Size: size %zu but empty is %s.",
                                           t, te ? "true" : "false"));
        if (r != t) throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
        return r;
    }

    const T& operator [] (size_t index) const {
        const T& r = ref[index];
        const T& t = tested[index];
        if (r != t) throw TestFailed("Op [] const mismatch.");
        return t;
    }

    void assign(size_t index, T x) {
        ref[index] = x;
        tested[index] = std::move(x);
        operator[](index);
    }

    void insert(size_t i, T x, bool check_tree_ = false) {
        ref.insert(i, x);
        tested.insert(i, std::move(x));
        size();
        if (check_tree_) check_tree();
    }

    T erase(size_t i, bool check_tree_ = false) {
        T r = ref.erase(i);
        T t = tested.erase(i);
        if (r != t) TestFailed(fmt("Erase mismatch at %zu.", i));
        size();
        if (check_tree_) check_tree();
        return t;
    }

    void check_tree() const {
        using TI = typename Array<T>::TesterInterface;
        auto ref_it = ref.begin();
        bool check_value_failed = false;
        auto check_value = [&](const T& v) {
            if (check_value_failed) return;
            check_value_failed = (ref_it == ref.end() || *ref_it != v);
            if (!check_value_failed) ++ref_it;
        };

        size();

        check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);

        if (check_value_failed) throw TestFailed(
                    "Check tree: element mismatch");
    }

    template < typename Node, typename F >
    int check_node(const Node* n, const Node* p, F& check_value) const {
        if (!n) return -1;

        using TI = typename Array<T>::TesterInterface;
        if constexpr(config::PARENT_POINTERS) {
            if (TI::parent(n) != p) throw TestFailed("Parent mismatch.");
        }

        auto l_depth = check_node(TI::left(n), n, check_value);
        check_value(TI::value(n));
        auto r_depth = check_node(TI::right(n), n, check_value);

        if (config::CHECK_DEPTH && abs(l_depth - r_depth) > 1) throw TestFailed(fmt(
                    "Tree is not avl balanced: left depth %i and right depth %i.",
                    l_depth, r_depth
            ));

        return std::max(l_depth, r_depth) + 1;
    }

    Array<T> tested;
    Ref<T> ref;
};


void test_insert() {
    Tester<int> t;

    for (int i = 0; i < 10; i++) t.insert(i, i, true);
    for (int i = 0; i < 10; i++) t.insert(i, -i, true);
    for (size_t i = 0; i < t.size(); i++) t[i];

    for (int i = 0; i < 5; i++) t.insert(15, (1 + i * 7) % 17, true);
    for (int i = 0; i < 10; i++) t.assign(2*i, 3*t[2*i]);
    for (size_t i = 0; i < t.size(); i++) t[i];
}

void test_erase() {
    Tester<int> t;

    for (int i = 0; i < 10; i++) t.insert(i, i, true);
    for (int i = 0; i < 10; i++) t.insert(i, -i, true);

    for (size_t i = 3; i < t.size(); i += 2) t.erase(i, true);
    for (size_t i = 0; i < t.size(); i++) t[i];

    for (int i = 0; i < 5; i++) t.insert(3, (1 + i * 7) % 17, true);
    for (size_t i = 1; i < t.size(); i += 3) t.erase(i, true);

    for (int i = 0; i < 20; i++) t.insert(3, 100 + i, true);

    for (int i = 0; i < 5; i++) t.erase(t.size() - 1, true);
    for (int i = 0; i < 5; i++) t.erase(0, true);

    for (int i = 0; i < 4; i++) t.insert(i, i, true);
    for (size_t i = 0; i < t.size(); i++) t[i];
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

    for (size_t i = 0; i < size; i++) {
        size_t pos = seq ? 0 : my_rand() % (i + 1);
        t.insert(pos, my_rand() % (3*size), check_tree);
    }

    t.check_tree();

    for (size_t i = 0; i < t.size(); i++) t[i];

    for (size_t i = 0; i < 30*size; i++) switch (my_rand() % 7) {
            case 1: {
                if (!erase && i % 3 == 0) break;
                size_t pos = seq ? 0 : my_rand() % (t.size() + 1);
                t.insert(pos, my_rand() % 1'000'000, check_tree);
                break;
            }
            case 2:
                if (erase) t.erase(my_rand() % t.size(), check_tree);
                break;
            case 3:
                t.assign(my_rand() % t.size(), 155 + i);
                break;
            default:
                t[my_rand() % t.size()];
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

        std::cout << "Bigger random test..." << std::endl;
        test_random(5'000);

        std::cout << "Bigger sequential test..." << std::endl;
        test_random(5'000, SEQ);

        std::cout << "All tests passed." << std::endl;
    } catch (const TestFailed& e) {
        std::cout << "Test failed: " << e.what() << std::endl;
    }
}

#endif


