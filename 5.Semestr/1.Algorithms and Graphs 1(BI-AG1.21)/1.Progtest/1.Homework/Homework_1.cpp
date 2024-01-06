#ifndef __PROGTEST__

#include <algorithm>
#include <bitset>
#include <iomanip>
#include <list>
#include <map>
#include <memory>
#include <queue>
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

struct CVertex {
    int m_name;
    vector<pair<size_t, size_t>> m_neighbour;
    unsigned m_size;
    int m_parent = -1;
    size_t m_level;
    bool m_exist;
};

void compareParentNeighbours(vector<CVertex> &vertexes, CVertex &curVertex) {
    for(const auto &neighbour : curVertex.m_neighbour) {
        CVertex newNeighbour = vertexes[neighbour.first];

        size_t newPathSize = neighbour.second + curVertex.m_size;
        if(newNeighbour.m_size < newPathSize) {
            vertexes[newNeighbour.m_name].m_size = newPathSize;
            vertexes[newNeighbour.m_name].m_parent = curVertex.m_name;
        }
    }
}

void findSource(const vector<Path> &all_paths, vector<CVertex> &vertexInfo, queue<size_t> &que) {
    for(const auto &path : all_paths) {
        if(!vertexInfo[path.from].m_exist) {
            vertexInfo[path.from].m_name = path.from;
            vertexInfo[path.from].m_exist = true;
        }
        vertexInfo[path.from].m_neighbour.emplace_back(path.to, path.length);

        if(!vertexInfo[path.to].m_exist) {
            vertexInfo[path.to].m_name = path.to;
            vertexInfo[path.to].m_exist = true;
        }
        vertexInfo[path.to].m_level++;
    }

    for(size_t i = 0; i < vertexInfo.size(); i++) {
        if (vertexInfo[i].m_exist && vertexInfo[i].m_level == 0) {
            que.push(i);
        }
    }
}

void topSort(const vector<Path> &all_paths, vector<CVertex> &vertexInfo, vector<size_t> &result) {

    queue<size_t> que;
    findSource(all_paths, vertexInfo, que);

    while (!que.empty()) {
        size_t curVertex = que.front();
        que.pop();
        result.push_back(curVertex);

        for (const auto& edge : vertexInfo[curVertex].m_neighbour) {
            vertexInfo[edge.first].m_level--;
            if(vertexInfo[edge.first].m_level == 0) {
                que.push(edge.first);
            }
        }
    }
}

vector<Path> trackRecovery(CVertex &vertex, vector<CVertex> &vertexInfo) {
    vector<Path> path;
    CVertex curVertex = std::move(vertex);
    while(curVertex.m_parent != -1) {
        Path tmpPath = {static_cast<size_t>(curVertex.m_parent), static_cast<size_t>(curVertex.m_name),
                        curVertex.m_size - vertexInfo[curVertex.m_parent].m_size};
        path.insert(path.begin(), tmpPath);
        curVertex = vertexInfo[curVertex.m_parent];
    }
    return path;
}

std::vector<Path> longest_track(size_t points, const std::vector<Path> &all_paths) {
    // vector for path
    vector<Path> path;
    vector<CVertex> vertexes(points);

    vector<size_t> result;
    topSort(all_paths, vertexes, result);
    CVertex maxVertex = vertexes[result[0]];

    for(const auto &vertex : result) {
        compareParentNeighbours(vertexes, vertexes[vertex]);
        if(maxVertex.m_size < vertexes[vertex].m_size) {
            maxVertex = vertexes[vertex];
        }
    }
    return trackRecovery(maxVertex, vertexes);
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


