#ifndef __PROGTEST__
#include <iomanip>
#include <iostream>
#include <memory>
#include <bitset>

#endif

using namespace std;

class CTree {
protected:
    class CNode;
public:
    CTree() = default;
    ~CTree() {
        delete m_root;
    }

    CNode * getRoot() const {
        return m_root;
    }

    // Get the size of the SubTree (number of elements)
    static size_t getSizeSubTree(CNode * node) {
        if(node != nullptr) {
            return node->m_subTreeSize;
        }
        return 0;
    }

    static size_t getLeftIndex(CNode * node) {
        if(!node) {
            return 0;
        } else {
            return node->m_subTreeSize;
        }
    }

    static size_t getLeftLines(CNode * node) {
        if(!node) {
            return 0;
        } else {
            return node->m_newLines;
        }
    }

    static size_t getNewLinesTree(CNode * node) {
        size_t newLines = 0;
        if (node->m_L) {
            newLines += node->m_L->m_newLines;
        }
        if (node->m_key == '\n') {
            newLines++;
        }
        if (node->m_R) {
            newLines += node->m_R->m_newLines;
        }
        return newLines;
    }

    static void incLines(CNode * node, char sym) {
        if(sym == '\n') {
            node->m_newLines++;
        }
    }

    // Get the depth of a subtree rooted at a given node
    static int getDepthSize(CNode * node) {
        if(node != nullptr) {
            return node->m_depth;
        }
        return 0;
    }

    // Get the maximum depth between two subtrees
    static int maxDepth(CNode * leftNode, CNode * rightNode) {
        if(getDepthSize(leftNode) < getDepthSize(rightNode)) {
            return getDepthSize(rightNode);
        } else {
            return getDepthSize(leftNode);
        }
    }

    // Find the minimum value node in a given subtree
    CNode * minValue(CNode * node) {
        if(node->m_L == nullptr) {
            return node;
        } else {
            return minValue(node->m_L);
        }
    }

    static size_t charToLine(CNode* node, size_t i, size_t newLines) {
        if(!node) {
            return 0;
        }

        size_t leftIndex = getLeftIndex(node->m_L);

        if(i < leftIndex) {
            return charToLine(node->m_L, i, newLines);
        } else if(i > leftIndex) {
            if(node->m_key == '\n') {
                if(node->m_L) {
                    newLines += node->m_L->m_newLines + 1;
                } else {
                    newLines++;
                }
            } else {
                if(node->m_L) {
                    newLines += node->m_L->m_newLines;
                }
            }
            return charToLine(node->m_R, i - leftIndex - 1, newLines);
        } else {
            if(node->m_L) {
                newLines += node->m_L->m_newLines;
            }
            return newLines;
        }
    }

    size_t lineStart(CNode* node, size_t r, size_t position) const {
        if (!node) {
            return position;
        }

        size_t leftIndex = getLeftIndex(node->m_L);
        size_t leftLines = getLeftLines(node->m_L);

        if(r < leftLines) {
            return lineStart(node->m_L, r, position);
        } else if(r > leftLines) {
            if(node->m_key == '\n') {
                return lineStart(node->m_R, r - leftLines - 1, leftIndex + 1 + position);
            }
            return lineStart(node->m_R, r - leftLines, leftIndex + 1 + position);
        } else if(node->m_key == '\n') {
            position += leftIndex + 1;
            return position;
        } else {
            return lineStart(node->m_R, r - leftLines, leftIndex + 1 + position);
        }
    }

    // Recursive helper function to find an element by index
    char findSymbol(CNode * node, size_t ind) const {
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

    // Found the node to edit
    static CNode * nodeToEdit(CNode * node, char toChange) {
        if (node->m_key == '\n' && toChange != '\n') {
            node->m_key = toChange;
            node->m_newLines = 0;
        } else if (node->m_key != '\n' && toChange == '\n') {
            node->m_key = toChange;
            node->m_newLines = 1;
        } else {
            node->m_key = toChange;
        }
        return node;
    }

    char prepEdit(size_t ind, char toChange) {
        CNode *nodeChange = edit(m_root, ind, toChange);
        char oldChar = nodeChange->m_key;
        nodeChange->m_key = toChange;
        return oldChar;
    }

    CNode * edit(CNode * node, size_t ind, char toChange) {
        if(node == nullptr || ind >= node->m_subTreeSize) {
            throw std:: out_of_range("out of range in edit");
        }

        CNode *findNode;

        if (node->m_L != nullptr) {
            size_t leftSize = node->m_L->m_subTreeSize;
            if (ind == leftSize) {
                findNode = nodeToEdit(node, toChange);
            } else if (ind < leftSize) {
                findNode = edit(node->m_L, ind, toChange);
            } else {
                if (node->m_L) {
                    findNode = edit(node->m_R, ind - leftSize - 1, toChange);
                } else {
                    findNode = edit(node->m_R, ind - 1, toChange);
                }
            }
        } else {
            if (ind == 0) {
                findNode = nodeToEdit(node, toChange);
            } else {
                findNode = edit(node->m_R, ind - 1, toChange);
            }
        }

        node->m_newLines = getNewLinesTree(node);

        return findNode;
    }

    void prepInsertOrDelete(char key, size_t ind, bool isInsert) {
        if(isInsert) {
            m_root = insert(m_root, key, ind);
        } else {
            m_root = del(m_root, ind);
        }
    }

    // Recursive helper function to remove an element from the tree
    CNode * del(CNode * node, size_t ind) {
        if(node == nullptr) {
            return nullptr;
        } else if((ind == 0 && !node->m_L) || (node->m_L && ind == node->m_L->m_subTreeSize)) {
            if(node->m_L == nullptr && node->m_R == nullptr) {
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
            node->m_R = del(node->m_R, 0);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
            node->m_newLines = getNewLinesTree(node);
            node = rotationTree(node);
        } else if((node->m_L == nullptr && ind < node->m_subTreeSize - 1) || (node->m_L && ind < node->m_L->m_subTreeSize)) {
            node->m_L = del(node->m_L, ind);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
            node->m_newLines = getNewLinesTree(node);
            node = rotationTree(node);
        } else {
            if(node->m_L) {
                node->m_R = del(node->m_R, ind - node->m_L->m_subTreeSize - 1);
            } else {
                node->m_R = del(node->m_R, ind - 1);
            }
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node->m_subTreeSize--;
            node->m_newLines = getNewLinesTree(node);
            node = rotationTree(node);
        }
        return node;
    }

    // Recursive helper function to insert a new element into the tree
    CNode * insert(CNode * node, char key, size_t ind) {
        if(node == nullptr) {
            node = new CNode(key);
            node->m_depth = 1;
            node->m_subTreeSize++;
            incLines(node, key);
            return node;
        }

        size_t leftIndex = getLeftIndex(node->m_L);

        if(ind <= leftIndex) {
            node->m_subTreeSize++;
            incLines(node, key);
            node->m_L = insert(node->m_L, key, ind);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        } else {
            node->m_subTreeSize++;
            if(node->m_L) {
                node->m_R = insert(node->m_R, key, ind - leftIndex - 1);
            } else {
                node->m_R = insert(node->m_R, key, ind - 1);
            }
            incLines(node, key);
            node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
            node = rotationTree(node);
        }
        return node;
    }

    // Perform a rotation on a node to maintain balance
    static CNode * rotationTree(CNode * node) {
        if (node == nullptr) {
            return nullptr;
        }

        if(2 <= getDepthSize(node->m_R) - getDepthSize(node->m_L)) {
            if(0 > getDepthSize(node->m_R->m_R) - getDepthSize(node->m_R->m_L)) {
                node->m_R = rotateRight(node->m_R);
            }
            node = rotateLeft(node);
        } else if(-2 >= getDepthSize(node->m_R) - getDepthSize(node->m_L)) {
            if (0 < getDepthSize(node->m_L->m_R) - getDepthSize(node->m_L->m_L)) {
                node->m_L = rotateLeft(node->m_L);
            }
            node = rotateRight(node);
        }
        node->m_newLines = getNewLinesTree(node);
        return node;
    }

    // Rotate a node to the left
    static CNode * rotateLeft(CNode * node) {
        CNode * rotateNode = node->m_R;
        node->m_R = rotateNode->m_L;
        rotateNode->m_L = node;
        node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
        node->m_subTreeSize = getSizeSubTree(node->m_L) + getSizeSubTree(node->m_R) + 1;
        node->m_newLines = getNewLinesTree(node);
        rotateNode->m_depth = maxDepth(rotateNode->m_R, node) + 1;
        rotateNode->m_subTreeSize = getSizeSubTree(rotateNode->m_L) + getSizeSubTree(rotateNode->m_R) + 1;
        rotateNode->m_newLines = getNewLinesTree(rotateNode);
        return rotateNode;
    }

    // Rotate a node to the right
    static CNode * rotateRight(CNode * node) {
        CNode * rotateNode = node->m_L;
        node->m_L = rotateNode->m_R;
        rotateNode->m_R = node;
        node->m_depth = maxDepth(node->m_L, node->m_R) + 1;
        node->m_subTreeSize = getSizeSubTree(node->m_L) + getSizeSubTree(node->m_R) + 1;
        node->m_newLines = getNewLinesTree(node);
        rotateNode->m_depth = maxDepth(rotateNode->m_L, node) + 1;
        rotateNode->m_subTreeSize = getSizeSubTree(rotateNode->m_L) + getSizeSubTree(rotateNode->m_R) + 1;
        rotateNode->m_newLines = getNewLinesTree(rotateNode);
        return rotateNode;
    }

protected:
    // Nested class for tree nodes
    class CNode {
    public:
        explicit CNode(char key) : m_key(key) {}
        ~CNode() {
            delete m_L;
            delete m_R;
        }

        size_t m_newLines = 0;
        int m_depth = 0;
        size_t m_subTreeSize = 0;
        char m_key;
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
    };
    CNode * m_root = nullptr;
};

struct TextEditorBackend {
    CTree tree;

    explicit TextEditorBackend(const std::string& text) {
        for(size_t i = 0; i < text.size(); i++) {
            insert(i, text[i]);
        }
    }

    size_t size() const {
        return CTree::getSizeSubTree(tree.getRoot());
    }

    size_t lines() const {
        return tree.getRoot()->m_newLines + 1;
    }

    char at(size_t i) const {
        if(i >= size()) {
            throw std:: out_of_range("out of range in at");
        }
        return tree.findSymbol(tree.getRoot(), i);
    }

    void edit(size_t i, char c) {
        tree.prepEdit(i, c);
    }

    void insert(size_t i, char c) {
        if(i > size()) {
            throw std:: out_of_range("out of range in insert");
        }

        tree.prepInsertOrDelete(c, i, true);
    }

    void erase(size_t i) {
        if(i >= size()) {
            throw std:: out_of_range("out of range in erase");
        }

        tree.prepInsertOrDelete('\0', i, false);
    }

    size_t line_start(size_t r) const {
        if(r >= lines()) {
            throw std:: out_of_range("out of range in line start");
        }

        if(r == 0) {
            return 0;
        } else {
            size_t control = tree.lineStart(tree.getRoot(), r - 1, 0);
            return control;
        }
    }

    size_t line_length(size_t r) const {
        if(r >= lines()) {
            throw std:: out_of_range("out of range in line length");
        }

        if(r == 0 && lines() == 1) {
            return size();
        } else if(lines() == r + 1) {
            return size() - tree.lineStart(tree.getRoot(), r - 1, 0);
        } else {
            size_t leftLine;
            if(r == 0) {
                return leftLine = tree.lineStart(tree.getRoot(), 0, 0);
            } else {
                leftLine = tree.lineStart(tree.getRoot(), r - 1, 0) - 1;
            }
            size_t rightLine = tree.lineStart(tree.getRoot(), r, 0) - 1;
            return rightLine - leftLine;
        }
    }

    size_t char_to_line(size_t i) const {
        if(i >= size()) {
            throw std:: out_of_range("out of range in line char to line");
        }
        size_t control = CTree::charToLine(tree.getRoot(), i, 0);
        return control;
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


