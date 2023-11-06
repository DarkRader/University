#ifndef __PROGTEST__
#include <cassert>
#include <iomanip>
#include <cstdint>
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
#include <type_traits>

#endif

using namespace std;

class CTree {
protected:
    class CNode;
public:
    CTree(void) = default;
    ~CTree(void) {
        delete m_root;
//        for (CNode* node : m_lines) {
//            delete node;
//        }
    }

    CNode * getRoot(void) const {
        return m_root;
    }

//    vector<CNode*> getLines(void) const {
//        return m_lines;
//    }

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

    char findSymbol(CNode * node, size_t ind) const {
        char symbol;
        if((node->m_L == nullptr && ind == 0) || (node->m_L && ind == node->m_L->m_subTreeSize)) {
            return node->m_key;
        } else if(node->m_L && ind < node->m_L->m_subTreeSize) {
            symbol = findSymbol(node->m_L, ind);
        } else if(node->m_R) {
            if(node->m_L) {
                symbol = findSymbol(node->m_R, ind - node->m_L->m_subTreeSize - 1);
            } else {
                symbol = findSymbol(node->m_R, ind - 1);
            }
        }
        return symbol;
    }

    char edit(CNode * node, size_t ind, char toChange) {
        char symbol;
        if((node->m_L == nullptr && ind == 0) || (node->m_L && ind == node->m_L->m_subTreeSize)) {
            symbol = node->m_key;
            node->m_key = toChange;
            return symbol;
        } else if(node->m_L && ind < node->m_L->m_subTreeSize) {
            symbol = edit(node->m_L, ind, toChange);
        } else if(node->m_R) {
            if(node->m_L) {
                symbol = edit(node->m_R, ind - node->m_L->m_subTreeSize - 1, toChange);
            } else {
                symbol = edit(node->m_R, ind - 1, toChange);
            }
        }
        return symbol;
    }

    CNode * prepInsert(char key, size_t ind, bool isInsert) {
        if(isInsert == true) {
            m_root = insert(m_root, key, ind);
        } else {
            m_root = del(m_root, key, ind);
        }
    }

    CNode * del(CNode * node, char key, size_t ind) {
        if(node == nullptr) {
            return nullptr;
        }
    }

    CNode * insert(CNode * node, char key, size_t ind) {
        if(node == nullptr) {
            node = new CNode(key);
            node->m_depth = 1;
            node->m_subTreeSize++;
            return node;
        }

        if(ind == 0) {
            node->m_subTreeSize++;
            node->m_L = insert(node->m_L, key, ind);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        } else if (node->m_L && ind == node->m_L->m_subTreeSize) {
            node->m_subTreeSize++;
            CNode* newNode = new CNode(key);
            newNode->m_L = node->m_L;
            node->m_L = newNode;
            newNode->m_subTreeSize = newNode->m_L->m_subTreeSize + 1;
            newNode->m_depth = maxDepth(newNode->m_L, newNode->m_R) + 1;
//            newNode = rotationTree(newNode);
        } else if((node->m_L == nullptr && ind < node->m_subTreeSize) || (node->m_L && ind < node->m_L->m_subTreeSize)) {
            node->m_subTreeSize++;
            node->m_L = insert(node->m_L, key, ind);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        } else if ((node->m_R == nullptr && ind > node->m_subTreeSize - 1) || (node->m_R && ind > node->m_R->m_subTreeSize - 1)) {
            node->m_subTreeSize++;
            if(node->m_L) {
                node->m_R = insert(node->m_R, key, ind - node->m_L->m_subTreeSize - 1);
            } else {
                node->m_R = insert(node->m_R, key, ind - 1);
            }
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

protected:

    class CNode {
    public:
        CNode(void) {}
        ~CNode(void) {
            delete m_L;
            delete m_R;
        }

        CNode(char key) {
            m_key = key;
        }

        int m_depth = 0;
        size_t m_subTreeSize = 0;
        char m_key;
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
    };
//    vector<CNode*> m_lines;
    CNode * m_root = nullptr;
};

struct TextEditorBackend {
    CTree tree;
    int m_lines = 0;
    vector<size_t> vecLines;

    TextEditorBackend(const std::string& text) {
        for(size_t i = 0; i < text.size(); i++) {
            insert(i, text[i]);
        }
    }

    size_t size() const {
        return tree.getSizeSubTree(tree.getRoot());
    }

    size_t lines() const {
        return vecLines.size() + 1;
    }

    char at(size_t i) const {
        if(i < 0 || i > size()) {
            throw std:: out_of_range("out of range in at");
        }
        return tree.findSymbol(tree.getRoot(), i);
    }

    void edit(size_t i, char c) {
        if(i < 0 || i > size()) {
            throw std:: out_of_range("out of range in edit");
        }
        if(tree.edit(tree.getRoot(), i, c) == '\n') {
            for(size_t t = 0; t < vecLines.size(); t++) {
                if(vecLines[t] == i) {
                    vecLines.erase(vecLines.begin() + t);
                }
            }
        }
    }
    void insert(size_t i, char c) {
        tree.prepInsert(c, i, true);
        if(c == '\n') {
            m_lines++;
            vecLines.push_back(i);
        }
    }

    void erase(size_t i) {
    }

    size_t line_start(size_t r) const {
        if(r < 0 || r > vecLines.size()) {
            throw std:: out_of_range("out of range in line start");
        }

        if(r == 0) {
            return 0;
        } else if(vecLines.size() == r) {
            return vecLines[r - 1] + 1;
        } else {
            return vecLines[r - 1] + 1;
        }

        return 0;
    }

    size_t line_length(size_t r) const {
        if(r < 0 || r > vecLines.size()) {
            throw std:: out_of_range("out of range in line length");
        }

        if(r == 0) {
            if(vecLines.size() == 0) {
                return size();
            } else {
                return vecLines[r] + 1;
            }
        } else if(vecLines.size() == r) {
            return size() - vecLines[r - 1] - 1;
        } else {
            return vecLines[r] - vecLines[r - 1];
        }

        return 0;
    }

    size_t char_to_line(size_t i) const {
        if(i < 0 || i > size()) {
            throw std:: out_of_range("out of range in char to line");
        }

        for(size_t t = 0; t < vecLines.size(); t++) {
            if(vecLines[t] == i) {
                return t;
            }
            if(i < vecLines[t]) {
                return t;
            }
            if(vecLines.size() == t + 1 && i > vecLines[t]) {
                return t + 1;
            }
        }

        return 0;
    }
};

#ifndef __PROGTEST__

////////////////// Dark magic, ignore ////////////////////////

template < typename T >
auto quote(const T& t) { return t; }

std::string quote(const std::string& s) {
    std::string ret = "\"";
    for (char c : s) if (c != '\n') ret += c; else ret += "\\n";
    return ret + "\"";
}

#define STR_(a) #a
#define STR(a) STR_(a)

#define CHECK_(a, b, a_str, b_str) do { \
    auto _a = (a); \
    decltype(a) _b = (b); \
    if (_a != _b) { \
      std::cout << "Line " << __LINE__ << ": Assertion " \
        << a_str << " == " << b_str << " failed!" \
        << " (lhs: " << quote(_a) << ")" << std::endl; \
      fail++; \
    } else ok++; \
  } while (0)

#define CHECK(a, b) CHECK_(a, b, #a, #b)

#define CHECK_ALL(expr, ...) do { \
    std::array _arr = { __VA_ARGS__ }; \
    for (size_t _i = 0; _i < _arr.size(); _i++) \
      CHECK_((expr)(_i), _arr[_i], STR(expr) "(" << _i << ")", _arr[_i]); \
  } while (0)

#define CHECK_EX(expr, ex) do { \
    try { \
      (expr); \
      fail++; \
      std::cout << "Line " << __LINE__ << ": Expected " STR(expr) \
        " to throw " #ex " but no exception was raised." << std::endl; \
    } catch (const ex&) { ok++; \
    } catch (...) { \
      fail++; \
      std::cout << "Line " << __LINE__ << ": Expected " STR(expr) \
        " to throw " #ex " but got different exception." << std::endl; \
    } \
  } while (0)

////////////////// End of dark magic ////////////////////////


std::string text(const TextEditorBackend& t) {
    std::string ret;
    for (size_t i = 0; i < t.size(); i++) ret.push_back(t.at(i));
    return ret;
}

void test1(int& ok, int& fail) {
    TextEditorBackend s("123\n456\n789");
    CHECK(s.size(), 11);
    CHECK(text(s), "123\n456\n789");
    CHECK(s.lines(), 3);
    CHECK_ALL(s.char_to_line, 0,0,0,0, 1,1,1,1, 2,2,2);
    CHECK_ALL(s.line_start, 0, 4, 8);
    CHECK_ALL(s.line_length, 4, 4, 3);
}

void test2(int& ok, int& fail) {
    TextEditorBackend t("123\n456\n789\n");
    CHECK(t.size(), 12);
    CHECK(text(t), "123\n456\n789\n");
    CHECK(t.lines(), 4);
    CHECK_ALL(t.char_to_line, 0,0,0,0, 1,1,1,1, 2,2,2,2);
    CHECK_ALL(t.line_start, 0, 4, 8, 12);
    CHECK_ALL(t.line_length, 4, 4, 4, 0);
}

void test3(int& ok, int& fail) {
    TextEditorBackend t("asdfasdfasdf");

    CHECK(t.size(), 12);
    CHECK(text(t), "asdfasdfasdf");
    CHECK(t.lines(), 1);
    CHECK_ALL(t.char_to_line, 0,0,0,0, 0,0,0,0, 0,0,0,0);
    CHECK(t.line_start(0), 0);
    CHECK(t.line_length(0), 12);

    t.insert(0, '\n');
    CHECK(t.size(), 13);
    CHECK(text(t), "\nasdfasdfasdf");
    CHECK(t.lines(), 2);
    CHECK_ALL(t.line_start, 0, 1);

    t.insert(4, '\n');
    CHECK(t.size(), 14);
    CHECK(text(t), "\nasd\nfasdfasdf");
    CHECK(t.lines(), 3);
    CHECK_ALL(t.line_start, 0, 1, 5);

    t.insert(t.size(), '\n');
    CHECK(t.size(), 15);
    CHECK(text(t), "\nasd\nfasdfasdf\n");
    CHECK(t.lines(), 4);
    CHECK_ALL(t.line_start, 0, 1, 5, 15);

    t.edit(t.size() - 1, 'H');
    CHECK(t.size(), 15);
    CHECK(text(t), "\nasd\nfasdfasdfH");
    CHECK(t.lines(), 3);
    CHECK_ALL(t.line_start, 0, 1, 5);

    t.erase(8);
    CHECK(t.size(), 14);
    CHECK(text(t), "\nasd\nfasfasdfH");
    CHECK(t.lines(), 3);
    CHECK_ALL(t.line_start, 0, 1, 5);

    t.erase(4);
    CHECK(t.size(), 13);
    CHECK(text(t), "\nasdfasfasdfH");
    CHECK(t.lines(), 2);
    CHECK_ALL(t.line_start, 0, 1);
}

void test_ex(int& ok, int& fail) {
    TextEditorBackend t("123\n456\n789\n");
    CHECK_EX(t.at(12), std::out_of_range);

    CHECK_EX(t.insert(13, 'a'), std::out_of_range);
    CHECK_EX(t.edit(12, 'x'), std::out_of_range);
    CHECK_EX(t.erase(12), std::out_of_range);

    CHECK_EX(t.line_start(4), std::out_of_range);
    CHECK_EX(t.line_start(40), std::out_of_range);
    CHECK_EX(t.line_length(4), std::out_of_range);
    CHECK_EX(t.line_length(6), std::out_of_range);
    CHECK_EX(t.char_to_line(12), std::out_of_range);
    CHECK_EX(t.char_to_line(25), std::out_of_range);
}

int main() {
    int ok = 0, fail = 0;
    if (!fail) test1(ok, fail);
    if (!fail) test2(ok, fail);
    if (!fail) test3(ok, fail);
    if (!fail) test_ex(ok, fail);

    if (!fail) std::cout << "Passed all " << ok << " tests!" << std::endl;
    else std::cout << "Failed " << fail << " of " << (ok + fail) << " tests." << std::endl;
}

#endif


