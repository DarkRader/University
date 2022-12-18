#ifndef __PROGTEST__
#include <cassert>
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
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>

using ChristmasTree = size_t;

struct TreeProblem {
  int max_group_size;
  std::vector<uint64_t> gifts;
  std::vector<std::pair<ChristmasTree, ChristmasTree>> connections;
};

#endif

struct SVertex {
    SVertex(uint64_t name, uint64_t unvis, bool visited, bool final, uint64_t withGuard, uint64_t withoutGuard)
    : Name(name), Unvis(unvis), Visited(visited), Final(final), GiftWithGuard(withGuard), GiftWithoutGuard(withoutGuard) {}

    uint64_t Name;
    uint64_t Unvis;
    bool Visited;
    bool Final;
    std::vector<uint64_t> Neighbours;
    uint64_t GiftWithGuard;
    uint64_t GiftWithoutGuard;
};

void controlOnList(const TreeProblem& infoTreeProblem, std::vector<SVertex>& infoVertex, std::vector<uint64_t>& lists, uint64_t i,
                   std::queue<SVertex>& que) {
    uint64_t position = 0;
    uint64_t gifts = 0;
    if(infoVertex[infoTreeProblem.connections[i].first].Neighbours.size() == 1) {
        position = infoTreeProblem.connections[i].first;
        gifts = infoTreeProblem.connections[i].first;
    } else if(infoVertex[infoTreeProblem.connections[i].second].Neighbours.size() == 1) {
        position = infoTreeProblem.connections[i].second;
        gifts = infoTreeProblem.connections[i].second;
    }
    if(infoVertex[position].Neighbours.size() == 1) {
        que.push(infoVertex[position]);
        lists.push_back(position);
        infoVertex[position].GiftWithGuard = infoTreeProblem.gifts[gifts];
        infoVertex[position].GiftWithoutGuard = 0;
        infoVertex[position].Visited = true;
    }
}

std::vector<uint64_t> getLists(const TreeProblem& infoTreeProblem, std::vector<SVertex>& infoVertex, std::vector<uint64_t>& lists,
                               std::queue<SVertex>& que) {
    for(uint64_t i = 0; i < infoTreeProblem.gifts.size(); ++i) {
        infoVertex.push_back({i, i, false, false, 0, 0});
    }
    for(uint64_t i = 0; i < infoTreeProblem.connections.size(); ++i) {
        infoVertex[infoTreeProblem.connections[i].second].Neighbours.push_back(infoTreeProblem.connections[i].first);
        infoVertex[infoTreeProblem.connections[i].first].Neighbours.push_back(infoTreeProblem.connections[i].second);
    }
    for(uint64_t i = 0; i < infoTreeProblem.connections.size(); ++i) {
        controlOnList(infoTreeProblem, infoVertex, lists, i, que);
    }
    return lists;
}

uint64_t controlNextVert(std::vector<SVertex>& infoVertex, SVertex& curVertex) {
    uint64_t counterNeighbours = 0;
    uint64_t candidate = curVertex.Name;
    for(uint64_t i = 0; i < curVertex.Neighbours.size(); ++i) {
        if(infoVertex[curVertex.Neighbours[i]].Visited == false) {
            candidate = curVertex.Neighbours[i];
            counterNeighbours++;
        }
        if(counterNeighbours > 1) {
            return curVertex.Name;
        }
    }
    if(counterNeighbours == 0) {
        infoVertex[curVertex.Name].Final = true;
    }
    infoVertex[curVertex.Name].Unvis = candidate;
    return candidate;
}

uint64_t findNextVertex(std::vector<SVertex>& infoVertex, SVertex& curVertex) {
    SVertex nextVertex(0, 0, false, false, 0, 0);
    if(curVertex.Neighbours.size() == 1) {
        nextVertex = infoVertex[curVertex.Neighbours[0]];
    } else {
        nextVertex = infoVertex[curVertex.Unvis];
    }
    uint64_t controlVertex = controlNextVert(infoVertex, nextVertex);
    if(nextVertex.Name == controlVertex) {
        if(nextVertex.Final == true) {
            return nextVertex.Name;
        } else {
            return curVertex.Name;
        }
    } else {
        return nextVertex.Name;
    }
}

void fillCrossroad(std::vector<SVertex>& infoVertex, SVertex& curVertex, const uint64_t& gifts) {
    uint64_t withGuard = gifts;
    uint64_t withoutGuard = 0;
    for(uint64_t i = 0; i < curVertex.Neighbours.size(); ++i) {
        if(infoVertex[curVertex.Neighbours[i]].Visited == true) {
            withGuard += infoVertex[curVertex.Neighbours[i]].GiftWithoutGuard;
            if(infoVertex[curVertex.Neighbours[i]].GiftWithGuard > infoVertex[curVertex.Neighbours[i]].GiftWithoutGuard) {
                withoutGuard += infoVertex[curVertex.Neighbours[i]].GiftWithGuard;
            } else {
                withoutGuard += infoVertex[curVertex.Neighbours[i]].GiftWithoutGuard;
            }
        }
    }
    curVertex.Visited = true;
    curVertex.GiftWithGuard = withGuard;
    curVertex.GiftWithoutGuard = withoutGuard;
}

uint64_t getRes(const TreeProblem& infoTreeProblem) {
    std::vector<SVertex> infoVertex;
    std::vector<uint64_t> lists;
    std::queue<SVertex> que;
    lists = getLists(infoTreeProblem, infoVertex, lists, que);

    uint64_t result = 0;
    while(!que.empty()) {
        SVertex curVertex = que.front();
        que.pop();
        uint64_t nextVertex = findNextVertex(infoVertex, curVertex);
        if(nextVertex == curVertex.Name && infoVertex[nextVertex].Final == false) {
            continue;
        } else {
            if(infoVertex[nextVertex].Visited == true) {
                continue;
            }
            fillCrossroad(infoVertex, infoVertex[nextVertex], infoTreeProblem.gifts[nextVertex]);
            que.push(infoVertex[nextVertex]);
            if(infoVertex[nextVertex].Final == true) {
                if(infoVertex[nextVertex].GiftWithGuard > infoVertex[nextVertex].GiftWithoutGuard) {
                    result = infoVertex[nextVertex].GiftWithGuard;
                } else {
                    result = infoVertex[nextVertex].GiftWithoutGuard;
                }
                break;
            }
        }
    }
    return result;
}

uint64_t solve(const TreeProblem& infoTreeProblem) {
    return getRes(infoTreeProblem);
}

#ifndef __PROGTEST__

using TestCase = std::pair<uint64_t, TreeProblem>;

const std::vector<TestCase> BASIC_TESTS = {
    { 3, { 1, { 1, 1, 1, 2 }, { {0,3}, {1,3}, {2,3} }}},
    { 4, { 1, { 1, 1, 1, 4 }, { {0,3}, {1,3}, {2,3} }}},
      { 57, { 1, {
        17, 11, 5, 13, 8, 12, 7, 4, 2, 8,
      }, {
        {1, 4}, {6, 1}, {2, 1}, {3, 8}, {8, 0}, {6, 0}, {5, 6}, {7, 2}, {0, 9},
      }}},
      { 85, { 1, {
        10, 16, 13, 4, 19, 8, 18, 17, 18, 19, 10,
      }, {
        {9, 7}, {9, 6}, {10, 4}, {4, 9}, {7, 1}, {0, 2}, {9, 2}, {3, 8}, {2, 3}, {5, 4},
      }}},
      { 79, { 1, {
        8, 14, 11, 8, 1, 13, 9, 14, 15, 12, 1, 11,
      }, {
        {9, 1}, {1, 2}, {1, 4}, {5, 10}, {7, 8}, {3, 7}, {11, 3}, {11, 10}, {6, 8}, {0, 1}, {0, 3},
      }}},
      { 102, { 1, {
        15, 10, 18, 18, 3, 4, 18, 12, 6, 19, 9, 19, 10,
      }, {
        {10, 2}, {11, 10}, {6, 3}, {10, 8}, {5, 3}, {11, 1}, {9, 5}, {0, 4}, {12, 3}, {9, 7}, {11, 9}, {4, 12},
      }}},
      { 93, { 1, {
        1, 7, 6, 18, 15, 2, 14, 15, 18, 8, 15, 1, 5, 6,
      }, {
        {0, 13}, {6, 12}, {0, 12}, {7, 8}, {8, 3}, {12, 11}, {12, 1}, {10, 12}, {2, 6}, {6, 9}, {12, 7}, {0, 4}, {0, 5},
      }}},
};

const std::vector<TestCase> BONUS_TESTS = {
  { 3, { 2, { 1, 1, 1, 2 }, { {0,3}, {1,3}, {2,3} }}},
  { 5, { 2, { 1, 1, 1, 4 }, { {0,3}, {1,3}, {2,3} }}},
};

void test(const std::vector<TestCase>& T) {
  int i = 0;
  for (auto &[s, t] : T) {
    if (s != solve(t))
      std::cout << "Error in " << i << " (returned " << solve(t) << ")"<< std::endl;
    i++;
  }
  std::cout << "Finished" << std::endl;
}

int main() {
  test(BASIC_TESTS);
  // test(BONUS_TESTS);
}

#endif


