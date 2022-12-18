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

//struct SVertex {
//    SVertex(uint64_t name, uint64_t unvis, bool visited, bool final, uint64_t withGuard, uint64_t withoutGuard)
//    : Name(name), Unvis(unvis), Visited(visited), Final(final), GiftWithGuard(withGuard), GiftWithoutGuard(withoutGuard) {}
//    
//    uint64_t Name;
//    uint64_t Unvis;
//    bool Visited;
//    bool Final;
//    std::vector<uint64_t> Neighbours;
//    uint64_t GiftWithGuard;
//    uint64_t GiftWithoutGuard;
//};

class CVertex {
public:
    CVertex(uint64_t name, uint64_t unvis, bool visited, bool final, uint64_t withGuard, uint64_t withoutGuard)
    : m_name(name), m_unvis(unvis), m_visited(visited), m_final(final), m_giftWithGuard(withGuard), m_giftWithoutGuard(withoutGuard) {}
    
    void setNewInfo(bool visited, uint64_t withGuard, uint64_t withoutGuard) {
        m_visited = true;
        m_giftWithGuard = withGuard;
        m_giftWithoutGuard = withoutGuard;
    }
    
    uint64_t getName(void) const {
        return m_name;
    }
    
    uint64_t getGiftWithGuard(void) {
        return m_giftWithGuard;
    }
    
    void setGiftWithGuard(uint64_t sizeGift) {
        m_giftWithGuard = sizeGift;
    }
    
    uint64_t getGiftWithoutGuard(void) {
        return m_giftWithoutGuard;
    }
    
    void setGiftWithoutGuard(uint64_t sizeGift) {
        m_giftWithoutGuard = sizeGift;
    }
    
    void pushNeighbours (uint64_t Vertex) {
        m_neighbours.push_back(Vertex);
    }
    
    uint64_t getSizeNeighbours(void) const {
        return m_neighbours.size();
    }
    
    bool getVisited(void) const {
        return m_visited;
    }
    
    void setVisited(bool visited) {
        m_visited = true;
    }
    
    uint64_t getSpecNeighbor(uint64_t Vertex) const {
        return m_neighbours[Vertex];
    }
    
    uint64_t getUnvis(void) const {
        return m_unvis;
    }
    
    void setUnvis(uint64_t unvis) {
        m_unvis = unvis;
    }
    
    bool getFinal(void) const {
        return m_final;
    }
    
    void setFinal(bool visited) {
        m_final = true;
    }
    
private:
    uint64_t m_name;
    uint64_t m_unvis;
    bool m_visited;
    bool m_final;
    std::vector<uint64_t> m_neighbours;
    uint64_t m_giftWithGuard;
    uint64_t m_giftWithoutGuard;
};

void controlOnList(const TreeProblem& infoTreeProblem, std::vector<CVertex>& infoVertex, std::vector<uint64_t>& lists, uint64_t poz) {
    if(infoVertex[infoTreeProblem.connections[poz].first].getSizeNeighbours() == 1) {
        lists.push_back(infoTreeProblem.connections[poz].first);
        infoVertex[infoTreeProblem.connections[poz].first].setGiftWithGuard(infoTreeProblem.gifts[infoTreeProblem.connections[poz].first]);
        infoVertex[infoTreeProblem.connections[poz].first].setGiftWithoutGuard(0);
        infoVertex[infoTreeProblem.connections[poz].first].setVisited(true);
    }
    if(infoVertex[infoTreeProblem.connections[poz].second].getSizeNeighbours() == 1) {
        lists.push_back(infoTreeProblem.connections[poz].second);
        infoVertex[infoTreeProblem.connections[poz].second].setGiftWithGuard(infoTreeProblem.gifts[infoTreeProblem.connections[poz].second]);
        infoVertex[infoTreeProblem.connections[poz].second].setGiftWithoutGuard(0);
        infoVertex[infoTreeProblem.connections[poz].second].setVisited(true);
    }
}

std::vector<uint64_t> getLists(const TreeProblem& infoTreeProblem, std::vector<CVertex>& infoVertex, std::vector<uint64_t>& lists, uint64_t poz) {
    
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

uint64_t controlNextVert(std::vector<CVertex>& infoVertex, CVertex& curVertex) {

    uint64_t counterNeighbours = 0;
    uint64_t candidate = curVertex.getName();
    for(uint64_t i = 0; i < curVertex.getSizeNeighbours(); ++i) {
        if(infoVertex[curVertex.getSpecNeighbor(i)].getVisited() == false) {
            candidate = curVertex.getSpecNeighbor(i);
            counterNeighbours++;
        }
        if(counterNeighbours > 1) {
            return curVertex.getName();
        }
    }
    
    if(counterNeighbours == 0) {
        infoVertex[curVertex.getName()].setFinal(true);
    }
    
    infoVertex[curVertex.getName()].setUnvis(candidate);
    return candidate;
}

uint64_t findNextVertex(std::vector<CVertex>& infoVertex, CVertex& curVertex) {
    if(curVertex.getSizeNeighbours() == 1) {
        CVertex nextVertex = infoVertex[curVertex.getSpecNeighbor(0)];
        uint64_t controlVertex = controlNextVert(infoVertex, nextVertex);
        if(nextVertex.getName() == controlVertex) {
            if(nextVertex.getFinal() == true) {
                return nextVertex.getName();
            } else {
                return curVertex.getName();
            }
        } else {
            return nextVertex.getName();
        }
    } else {
        CVertex nextVertex = infoVertex[curVertex.getUnvis()];
        uint64_t controlVertex = controlNextVert(infoVertex, nextVertex);
        if(nextVertex.getName() == controlVertex) {
            if(nextVertex.getFinal() == true) {
                return nextVertex.getName();
            } else {
                return curVertex.getName();
            }
        } else {
            return nextVertex.getName();
        }
    }
}

void fillCrossroad(std::vector<CVertex>& infoVertex, CVertex& curVertex, const uint64_t& gifts) {

    uint64_t withGuard = gifts;
    uint64_t withoutGuard = 0;
    for(uint64_t i = 0; i < curVertex.getSizeNeighbours(); ++i) {
        if(infoVertex[curVertex.getSpecNeighbor(i)].getVisited() == true) {
            withGuard += infoVertex[curVertex.getSpecNeighbor(i)].getGiftWithoutGuard();
            if(infoVertex[curVertex.getSpecNeighbor(i)].getGiftWithGuard() > infoVertex[curVertex.getSpecNeighbor(i)].getGiftWithoutGuard()) {
                withoutGuard += infoVertex[curVertex.getSpecNeighbor(i)].getGiftWithGuard();
            } else {
                withoutGuard += infoVertex[curVertex.getSpecNeighbor(i)].getGiftWithoutGuard();
            }
        }
    }
    curVertex.setNewInfo(true, withGuard, withoutGuard);
}

uint64_t getRes(const TreeProblem& infoTreeProblem) {
    std::vector<CVertex> infoVertex;
    for(size_t i = 0; i < infoTreeProblem.gifts.size(); ++i) {
        infoVertex.push_back({i, i, false, false, 0, 0});
    }
    std::vector<uint64_t> lists;
    lists = getLists(infoTreeProblem, infoVertex, lists, 0);
    std::queue<CVertex> que;
    
    for(uint64_t i = 0; i < lists.size(); ++i) {
        que.push(infoVertex[lists[i]]);
    }
 
    uint64_t result = 0;
    while(!que.empty()) {
        CVertex curVertex = que.front();
        que.pop();
        uint64_t nextVertex = findNextVertex(infoVertex, curVertex);
        if(nextVertex == curVertex.getName() && infoVertex[nextVertex].getFinal() == false) {
            continue;
        } else {
            if(curVertex.getFinal() == true) {
                if(curVertex.getGiftWithGuard() > curVertex.getGiftWithoutGuard()) {
                    result = curVertex.getGiftWithGuard();
                } else {
                    result = curVertex.getGiftWithoutGuard();
                }
            }
            if(infoVertex[nextVertex].getVisited() == true) {
                continue;
            }
            fillCrossroad(infoVertex, infoVertex[nextVertex], infoTreeProblem.gifts[nextVertex]);
            que.push(infoVertex[nextVertex]);
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


