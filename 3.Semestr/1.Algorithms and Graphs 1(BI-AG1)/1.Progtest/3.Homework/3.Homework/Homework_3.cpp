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

class CVertex {
public:
    CVertex(size_t name) : m_name(name) {}
//    CVertex(const TreeProblem& infoTreeProblem, uint64_t Vertex) {
//        m_giftWithGuard = {infoTreeProblem.gifts[Vertex], 1};
//        m_giftWithoutGuard = {0, 0};
//
//        for(size_t i = 0; i < infoTreeProblem.connections.size(); ++i) {
//            if(infoTreeProblem.connections[i].first == Vertex)
//                m_neighbours.push_back(infoTreeProblem.connections[i].second);
//            else if(infoTreeProblem.connections[i].second == Vertex)
//                m_neighbours.push_back(infoTreeProblem.connections[i].first);
//        }
//
//        for(size_t i = 0; i < m_neighbours.size(); ++i) {
//            m_giftWithoutGuard.first += infoTreeProblem.gifts[m_neighbours[i]];
//        }
//    }
    
    void setGiftWithGuard(size_t sizeGift, size_t sizeGuard) {
        m_giftWithGuard = {sizeGift, sizeGuard};
    }
    
    void pushNeighbours (size_t Vertex) {
        m_neighbours.push_back(Vertex);
    }
    
    size_t getSizeNeighbours(void) const {
        return m_neighbours.size();
    }
    
private:
    size_t m_name;
    std::vector<size_t> m_neighbours;
    std::pair<size_t, size_t> m_giftWithGuard;
    std::pair<size_t, size_t> m_giftWithoutGuard;
};

void controlOnList(const TreeProblem& infoTreeProblem, std::vector<CVertex>& infoVertex, std::vector<size_t>& lists, uint64_t poz) {
    if(infoVertex[infoTreeProblem.connections[poz].first].getSizeNeighbours() == 1) {
        lists.push_back(infoTreeProblem.connections[poz].first);
        infoVertex[infoTreeProblem.connections[poz].first].setGiftWithGuard(infoTreeProblem.gifts[infoTreeProblem.connections[poz].first], 1);
    }
    if(infoVertex[infoTreeProblem.connections[poz].second].getSizeNeighbours() == 1) {
        lists.push_back(infoTreeProblem.connections[poz].second);
        infoVertex[infoTreeProblem.connections[poz].second].setGiftWithGuard(infoTreeProblem.gifts[infoTreeProblem.connections[poz].second], 1);
    }
}

std::vector<size_t> getLists(const TreeProblem& infoTreeProblem, std::vector<CVertex>& infoVertex, std::vector<size_t>& lists, uint64_t poz) {
    
    if(poz == infoTreeProblem.connections.size() - 1) {
        infoVertex[infoTreeProblem.connections[poz].second].pushNeighbours(infoTreeProblem.connections[poz].first);
        infoVertex[infoTreeProblem.connections[poz].first].pushNeighbours(infoTreeProblem.connections[poz].second);
        controlOnList(infoTreeProblem, infoVertex, lists, poz);
        return lists;
    } else {
        infoVertex[infoTreeProblem.connections[poz].second].pushNeighbours(infoTreeProblem.connections[poz].first);
        infoVertex[infoTreeProblem.connections[poz].first].pushNeighbours(infoTreeProblem.connections[poz].second);
        getLists(infoTreeProblem, infoVertex, lists, poz + 1);
    }
    
    controlOnList(infoTreeProblem, infoVertex, lists, poz);
    return lists;
}

uint64_t getRes(const TreeProblem& infoTreeProblem, std::vector<CVertex>& infoVertex, uint64_t poz) {
    std::vector<size_t> lists;
    lists = getLists(infoTreeProblem, infoVertex, lists, poz);
    for(size_t i = 0; i < infoTreeProblem.gifts.size(); ++i) {
        //infoVertex.push_back({infoTreeProblem, i});
    }
    
    
    
    return 0;
}

uint64_t solve(const TreeProblem& infoTreeProblem) {
    uint64_t res = 0;
    std::vector<CVertex> infoVertex;
    
    for(size_t i = 0; i < infoTreeProblem.gifts.size(); ++i) {
        infoVertex.push_back(i);
    }
    
    getRes(infoTreeProblem, infoVertex, 0);
    
    
    
    return 4;
}

#ifndef __PROGTEST__

using TestCase = std::pair<uint64_t, TreeProblem>;

const std::vector<TestCase> BASIC_TESTS = {
//  { 3, { 1, { 1, 1, 1, 2 }, { {0,3}, {1,3}, {2,3} }}},
//  { 4, { 1, { 1, 1, 1, 4 }, { {0,3}, {1,3}, {2,3} }}},
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


