#ifndef __PROGTEST__

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Point : size_t {
};

struct Path {
    Point from, to;
    unsigned length;

    Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

    friend bool operator==(const Path &a, const Path &b) {
        return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
    }

    friend bool operator!=(const Path &a, const Path &b) { return !(a == b); }
};

#endif

using namespace std;

class CVertex {
public:
    CVertex(size_t name) : m_exist(false), m_name(name), m_size(0), m_parent(nullptr), m_level(0) {}

    void setSize(size_t sizePath, shared_ptr<CVertex> parent) {
        size_t newPathSize = sizePath + parent->m_size;
        if(m_size < newPathSize) {
            m_size = newPathSize;
            m_parent = parent;
        }
    }

    void setExist(bool exist) {
        m_exist = exist;
    }

    void incLevel() {
        m_level++;
    }

    bool getExist() const {
        return m_exist;
    }

    size_t getLevel() const {
        return m_level;
    }

    shared_ptr<CVertex> getParent() {
        return m_parent;
    }

    size_t getName() const {
        return m_name;
    }

    unsigned getSize() const {
        return m_size;
    }

    void addNeighbour(size_t neighbour, size_t sizePath) {
        m_neighbour.push_back(make_pair(neighbour, sizePath));
    }

    void addNeighboursInQue(queue<size_t> &queVertex, vector<shared_ptr<CVertex>> &vertexes, const shared_ptr<CVertex> &curVertex) {
        for(const auto &neighbour : m_neighbour) {
            shared_ptr<CVertex> newNeighbour = vertexes[neighbour.first];

            newNeighbour->setSize(neighbour.second, curVertex);
            queVertex.push(neighbour.first);
        }
    }


private:
    bool m_exist;
    size_t m_name;
    vector<pair<size_t, size_t>> m_neighbour;
    size_t m_size;
    shared_ptr<CVertex> m_parent;
    size_t m_level;
};

queue<size_t> findSource(const vector<Path> &all_paths, vector<shared_ptr<CVertex>> &vertexInfo) {
    queue<size_t> queSource;

    for(const auto &path : all_paths) {
        shared_ptr<CVertex> curVertex = vertexInfo[path.from];
        curVertex->setExist(true);

        curVertex->addNeighbour(path.to, path.length);

        shared_ptr<CVertex> toVertex = vertexInfo[path.to];
        toVertex->setExist(true);

        toVertex->incLevel();
    }

    for(auto &element : vertexInfo) {
        if (element->getLevel() == 0 && element->getExist()) {
            queSource.push(element->getName());
        }
    }

    return queSource;
}

std::vector<Path> trackRecovery(shared_ptr<CVertex> vertex) {
    vector<Path> path;
    shared_ptr<CVertex> curVertex = std::move(vertex);
    while(curVertex->getParent() != nullptr) {
        Path tmpPath = {curVertex->getParent()->getName(), curVertex->getName(),
                        curVertex->getSize() - curVertex->getParent()->getSize()};
        path.push_back(tmpPath);
        curVertex = curVertex->getParent();
    }
    reverse(path.begin(), path.end());

    return path;
}

std::vector<Path> longest_track(size_t points, const std::vector<Path> &all_paths) {
    // vector for path
    vector<Path> path;
    vector<shared_ptr<CVertex>> vertexes;
    for(size_t i = 0; i < points; i++) {
        vertexes.push_back(make_shared<CVertex>(i));
    }
    queue<size_t> que = findSource(all_paths, vertexes);
    shared_ptr<CVertex> maxVertex = vertexes[que.front()];

    while(!que.empty()) {
        shared_ptr<CVertex> curVertex = vertexes[que.front()];
        que.pop();

        curVertex->addNeighboursInQue(que, vertexes, curVertex);

        if(maxVertex->getSize() < curVertex->getSize()) {
            maxVertex = curVertex;
        }

        if(que.empty()) {
            path = trackRecovery(maxVertex);
        }

    }

    return path;
}


#ifndef __PROGTEST__


struct Test {
    unsigned longest_track;
    size_t points;
    std::vector<Path> all_paths;
};

inline const Test TESTS[] = {
        {13, 5, {{3, 2, 10}, {3, 0, 9}, {0, 2, 3}, {2, 4, 1}}},
        {11, 5, {{3, 2, 10}, {3, 1, 4}, {1, 2, 3}, {2, 4, 1}}},
        {16, 8, {{3, 2, 10}, {3, 1, 1}, {1, 2, 3}, {1, 4, 15}}},

        {7, 4, {{0, 1, 1}, {1, 2, 3}, {0, 2, 5}, {2, 3, 2}}},
        {16, 8, {{3, 2, 10}, {3, 1, 1}, {1, 2, 3}, {1, 4, 15}}},
        {15, 6, {{1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {3, 5, 7}, {4, 5, 1}}},
        {12, 7, {{1, 2, 4}, {1, 3, 6}, {2, 4, 2}, {2, 5, 8}, {3, 5, 5}, {4, 6, 3}}},
        {10, 5, {{1, 3, 2}, {1, 4, 7}, {3, 2, 5}, {4, 2, 3}}},
        {11, 10, {{1, 2, 2}, {1, 3, 5}, {2, 4, 3}, {2, 5, 7}, {3, 6, 1}, {3, 7, 6}, {4, 8, 4}, {5, 9, 2}}},
        {31, 10, {{1, 2, 4}, {1, 3, 3}, {2, 4, 2}, {3, 5, 5}, {4, 6, 1}, {5, 7, 6}, {6, 8, 3}, {9,3,20}}},
        {19, 6, { {3,2,10}, {3,0,9}, {0,2,3}, {2,4,1}  , {5,2,18}}},
        {10,5, {{0,2,2},{1,2,4},{2,3,5},{2,4,6}}}
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Fail: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool run_test(const Test &t) {
    auto sol = longest_track(t.points, t.all_paths);

    unsigned length = 0;
    for (auto [_, __, l]: sol) length += l;

    CHECK(t.longest_track == length,
          "Wrong length: got %u but expected %u", length, t.longest_track);

    for (size_t i = 0; i < sol.size(); i++) {
        CHECK(std::count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
              "Solution contains non-existent path: %zu -> %zu (%u)",
              sol[i].from, sol[i].to, sol[i].length);

        if (i > 0)
            CHECK(sol[i].from == sol[i - 1].to,
                  "Paths are not consecutive: %zu != %zu", sol[i - 1].to, sol[i].from);
    }

    return true;
}

#undef CHECK

int main() {
    int ok = 0, fail = 0;

    for (auto &&t: TESTS) (run_test(t) ? ok : fail)++;

    if (!fail) printf("Passed all %i tests!\n", ok);
    else printf("Failed %u of %u tests.\n", fail, fail + ok);
}

#endif


