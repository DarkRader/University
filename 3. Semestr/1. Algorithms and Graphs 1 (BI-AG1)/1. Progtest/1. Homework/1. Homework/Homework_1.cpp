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
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

using Place = size_t;

struct Map {
  size_t places;
  Place start, end;
  std::vector<std::pair<Place, Place>> connections;
  std::vector<std::vector<Place>> items;
};

template < typename F, typename S >
struct std::hash<std::pair<F, S>> {
  std::size_t operator () (const std::pair<F, S> &p) const noexcept {
    // something like boost::combine would be much better
    return std::hash<F>()(p.first) ^ (std::hash<S>()(p.second) << 1);
  }
};

#endif

struct parentPath {
    parentPath(Place Sname, Place level, Place index) : name(Sname), levelParent(level), indexParent(index) {}
    
    Place name;
    Place levelParent;
    Place indexParent;
};

class CGraph
{
public:
    CGraph(const Map &map, Place name)
    {
        for(Place i = 0; i < map.connections.size(); i++) {
            if(map.connections[i].first == name)
                m_neighbours.push_back(map.connections[i].second);
            else if(map.connections[i].second == name)
                m_neighbours.push_back(map.connections[i].first);
        }
        
        for(Place i = 0; i < map.items.size(); i++) {
            for(auto it = map.items.at(i).begin(); it != map.items.at(i).end(); ++it) {
                if(*it == name) {
                    m_contItem.push_back(i);
                    break;
                }
            }
        }
    }
    
    void addItemsInLevel (Place itemSize)
    {
        m_itemsInLevels.push_back(std::vector<Place>());
        auto currentItems = m_contItem.begin();
        for(Place i = 0; i < itemSize; i++) {
            if(currentItems != m_contItem.end() && i == *currentItems) {
                m_itemsInLevels[0].push_back(1);
                currentItems++;
            } else {
                m_itemsInLevels[0].push_back(0);
            }
        }
    }
    
    void addItemsInLevelNew (Place itemSize, std::vector<Place> oldInItems)
    {
        m_itemsInLevels.push_back(std::vector<Place>());
        auto currentItems = m_contItem.begin();
        for(Place i = 0; i < itemSize; i++) {
            if(currentItems != m_contItem.end() && i == *currentItems) {
                m_itemsInLevels[m_itemsInLevels.size() - 1].push_back(1);
                currentItems++;
            } else if(oldInItems[i] == 1) {
                m_itemsInLevels[m_itemsInLevels.size() - 1].push_back(1);
            }else {
                m_itemsInLevels[m_itemsInLevels.size() - 1].push_back(0);
            }
        }
    }
    
    void addItemsBin (Place itemSize, std::vector<Place> items)
    {
        m_itemsInLevels.push_back(std::vector<Place>());
        auto currentItems = items.begin();
        for(Place i = 0; i < itemSize; i++) {
            if(*currentItems == 1) {
                m_itemsInLevels[m_itemsInLevels.size() - 1].push_back(1);
            } else {
                m_itemsInLevels[m_itemsInLevels.size() - 1].push_back(0);
            }
            currentItems++;
        }
    }
    
    Place getTypesItems(void) const { return m_contItem.size(); }
    std::vector<Place> getContItem(void) const { return m_contItem; }
    std::vector<Place> getNeighbours(void) const { return m_neighbours; }
    std::vector<Place> getItemsInLevelLast(void) { return m_itemsInLevels[m_itemsInLevels.size() - 1]; };
    std::vector<std::vector<Place>> getInLevelFully(void) const { return m_itemsInLevels; }
    bool visitedOrNot(std::vector<parentPath> vis, Place name)
    {
        for(Place i = 0; i < vis.size(); i++) {
            if(vis[i].name == name)
                return true;
        }
        return false;
    }

private:
    std::vector<Place> m_contItem;
    std::vector<Place> m_neighbours;
    std::vector<std::vector<Place>> m_itemsInLevels;
};

class CPath
{
public:
    CPath(Place distance, Place level, Place name, Place index, Place items, std::vector<Place> traceItem) : m_distance(distance), m_level(level), m_index(index), m_itemsIn(items), m_traceItem(traceItem)
    {
//        for(Place i = 0; i < traceItem.size(); i++)
//            m_traceItem.push_back(traceItem[i]);
    }
    
    Place getDistance(void) { return m_distance; }
    Place getLevel(void) const { return m_level; }
    Place getIndex(void) const { return m_index; }
    Place getItemsIn(void) const { return m_itemsIn; }
    std::vector<Place> getTraceItem(void) { return m_traceItem; }
    
    bool newOrNotNewItem(std::vector<Place> father, std::vector<Place> son, Place & itemSize)
    {
        for(Place i = 0; i < son.size(); i++) {
            if(father[son[i]] == 0)
                itemSize++;
        }
        if(itemSize > 0)
            return true;
        else
            return false;
    }
    
    bool closeRouteOrNot(std::vector<Place> itemPath, std::vector<std::vector<Place>> maxItem)
    {
        if(maxItem.size() == 0)
            return true;
        

        std::vector<Place> typItems;
        for(Place i = 0; i < itemPath.size(); i++) {
            if(itemPath[i] == 1)
                typItems.push_back(i);
        }
        
        for(Place i = 0; i < maxItem.size(); i++) {
            for(Place j = 0; j < typItems.size(); j++) {
                if(maxItem[i][typItems[j]] == 0) {
                    break;
                } else if(j == typItems.size() - 1) {
                    return false;;
                }
            }
        }
        return true;
    }
    
private:
    Place m_distance;
    Place m_level;
    Place m_index;
    Place m_itemsIn;
    std::vector<Place> m_traceItem;
};

//control, that we don't have any empty type of items
bool control_items(const Map &map)
{
    for(Place i = 0; i < map.items.size(); i++)
        if(map.items[i].size() == 0)
            return false;
    return true;
}

std::list<Place> getList(Place start, std::vector<std::vector<parentPath>> visited, Place level, Place index, Place dist)
{
    std::list<Place> path;
    
    while(dist != 0)
    {
        if(level > visited.size() - 1) {
            std::cout << "Something wrong!" << std::endl;
            std::list<Place> emptyPath;
            return emptyPath;
        } else if(index > visited[level].size() - 1) {
            std::cout << "Something wrong!" << std::endl;
            std::list<Place> emptyPath;
            return path;
        }
            
        path.push_front(visited[level][index].name);
        level = visited[level][index].levelParent;
        index = visited[level][index].indexParent;
        dist--;
    }
    
    path.push_front(start);
    
    return path;
}

std::list<Place> find_path(const Map &map) {
    //list for path
    std::list<Place> path;
    
//    if(control_items(map) == false)
//        return path;
    
    std::unordered_map<Place, CGraph> Vertex_contents;
    std::queue<std::pair<Place, CPath>> que;
    std::vector<std::vector<parentPath>> visited;
    Vertex_contents.insert({map.start, CGraph(map, map.start)});
    Place level = 0;
      
    auto iter = Vertex_contents.find(map.start);
    iter->second.addItemsInLevel(map.items.size());
    que.push({map.start, {0, 0, map.start, 0, iter->second.getContItem().size(), iter->second.getItemsInLevelLast()}});
    visited.push_back(std::vector<parentPath>());
    visited[level].push_back(parentPath(map.start, 0, 0));
    
    while(!que.empty())
    {
        auto parentNode = Vertex_contents.find(que.front().first);
        Place parent = parentNode->first;
//        if(parent == 3) // 1
//            std::cout << "Control vertex!" << std::endl;
        CPath addInfVer = que.front().second;
        que.pop();


        for(Place i = 0; i < parentNode->second.getNeighbours().size(); i++) {
            if(parentNode->second.visitedOrNot(visited[addInfVer.getLevel()], parentNode->second.getNeighbours()[i]) == false) {

                auto childNode = Vertex_contents.find(parentNode->second.getNeighbours()[i]);

                if(childNode == Vertex_contents.end()) {
                    Vertex_contents.insert({parentNode->second.getNeighbours()[i], CGraph(map, parentNode->second.getNeighbours()[i])});
                    childNode = Vertex_contents.find(parentNode->second.getNeighbours()[i]);
                }

                Place newNode = childNode->first;
                if(addInfVer.closeRouteOrNot(addInfVer.getTraceItem(), childNode->second.getInLevelFully()) == false)
                    continue;

                Place itemSize = 0;
                if(addInfVer.newOrNotNewItem(addInfVer.getTraceItem(), childNode->second.getContItem(), itemSize) == true) {
                    level++;
                    visited.push_back(std::vector<parentPath>());
                    visited[level].push_back(parentPath(newNode, addInfVer.getLevel(), addInfVer.getIndex()));
                    childNode->second.addItemsInLevelNew(map.items.size(), addInfVer.getTraceItem());
                    que.push({newNode, {addInfVer.getDistance() + 1, level, newNode, 0, addInfVer.getItemsIn() + itemSize, childNode->second.getItemsInLevelLast()}});
                } else {
                    visited[addInfVer.getLevel()].push_back(parentPath(newNode, addInfVer.getLevel(), addInfVer.getIndex()));
                    childNode->second.addItemsBin(map.items.size(), addInfVer.getTraceItem());
                    que.push({newNode, {addInfVer.getDistance() + 1, addInfVer.getLevel(), newNode, visited[addInfVer.getLevel()].size() - 1, addInfVer.getItemsIn(), addInfVer.getTraceItem()}});
                }
            }
        }

        if(parent == map.end && addInfVer.getItemsIn() == map.items.size()) {
            return getList(map.start, visited, addInfVer.getLevel(), addInfVer.getIndex(), addInfVer.getDistance());
        }

    }
      
      
       return path;
}

#ifndef __PROGTEST__

using TestCase = std::pair<size_t, Map>;

// Class template argument deduction exists since C++17 :-)
const std::array examples = {
    //        0

    TestCase{1, Map{2, 0, 0,

    {{0, 1}},

    {{0}}

    }},

    //        1

    TestCase{3, Map{2, 0, 0,

    {{0, 1}},

    {{1}

    }}},

    //        2

    TestCase{3, Map{4, 0, 1,

    {{0, 2}, {2, 3}, {0, 3}, {3, 1}},

    {}

    }},

    //        3

    TestCase{4, Map{4, 0, 1,

    {{0, 2}, {2, 3}, {0, 3}, {3, 1}},

    {{2}}

    }},

    //        4

    TestCase{0, Map{4, 0, 1,

    {{0, 2}, {2, 3}, {0, 3}, {3, 1}},

    {{2}, {}}

    }},

    //        5

    TestCase{0, Map{6, 1, 4,

    {{1, 2}, {2, 3}, {2, 4}},

    {{5}}

    }},

    //        6

    TestCase{7, Map{6, 1, 5,

    {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}},

    {{0}, {4}}

    }},

    //        7

    TestCase{0, Map{6, 1, 4,

    {{1, 2}, {2, 3}, {2, 4}},

    {{5}, {1}, {2}, {3}, {4}}

    }},

    //       8

    TestCase{0, Map{6, 1, 4,

    {},

    {{5}, {1}, {2}, {3}, {4}}

    }},

    //       9

    TestCase{0, Map{6, 1, 1,

    {},

    {{5}, {1}, {2}, {3}, {4}}

    }},

    //      10

    TestCase{5, Map{5, 0, 2,

    {{1, 4}, {1, 3}, {2, 3}, {2, 4}, {0, 3}, {0, 4}},

    {{1, 3}, {3}, {4}}

    }},

    //      11

    TestCase{6, Map{6, 2, 4,

    {{0, 3}, {0, 4}, {0, 5}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5},},

    {{5}, {5}, {1}, {0, 1}, {0}, {3}, {4}}

    }},

    //      12

    TestCase{5, Map{11, 0, 10,

    {{0, 1}, {0, 2}, {0, 5}, {1, 3}, {1, 4}, {1, 8}, {5, 9}, {5, 6}, {5, 10}, {2, 7}, {7, 6}, {8, 10}, {7, 10}},

    {{2, 6, 3, 9}, {4, 9}}

    }},

    //      13

    TestCase{5 ,Map{11, 0, 10,

    {{0, 5}, {0, 1 }, {0, 7}, {1, 2}, {1,3}, {1, 4}, {3, 10}, {5, 6}, {5, 10}, {5, 8}, {8, 9}, {7, 9}, {9, 10} },

    {

    {{2, 6, 8, 7}, {4, 6 }}

    }}},

    //       14

    TestCase{ 6, Map{

    6, 0,5, {{0,1}, {0,2 }, {0, 3}, {1, 4}, {2, 4}, {3, 4}, {4, 5}},

    {{1}, {1, 2, 3}, {3}}

    }}

    //        15

    ,TestCase { 0, Map

    {15, 0, 7, {{0, 1}, {0, 8}, {8, 2},{1, 3}, {2, 4}, {4, 5}, {5, 7}, {6, 9}, {9, 10}, {10, 7}}, {{1, 2}, {13}, {1, 4}} }},

    TestCase{ 4, Map {

    5, 0, 4, {{0, 1}, {0, 2}, {2, 3}, {3, 4}, {1, 4}}, {{1,2}, {1, 3}, {3}}

    }},

    //        16

    TestCase { 9,

    Map { 5, 0, 0, {{0, 1}, {0, 2}, {0, 3}, {0,4}}, {{1}, {2}, {3},{4}}}

    },

    //        17

    TestCase { 1,

    Map { 1, 0, 0, {{0, 0}}, {{0}, {0}, {0},{0}}}

    },

    //        18

    TestCase{2, Map{2, 0, 1, {{0, 1}},{{0,}, {1, },}}},

    //        19

    TestCase{6, Map{5, 0, 3, {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {2, 4}, {1, 3} },{{1, }, {3, }, {4, },}}},

    //        20

    TestCase{5, Map{5, 0, 3, {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {2, 4}, {1, 3} },{{0, 1,}, {3, }, {4, },}}},

    //        21

    TestCase{4, Map{5, 3, 0, {{0, 1}, {1, 2}, {1, 3}, {1, 4}, {3, 4}}, {{0, 3}, {2, 4,}, {1, 2,},}}},

    //        22

    TestCase{5, Map{5, 0, 0, {{0, 2}, {0, 3}, {2, 3}, {2, 1}, {3, 4}},{{3, },{1, 4, },{2, 3, },}}},

    //        23

    TestCase{5, Map{10, 3, 3, {{0, 1}, {0, 2}, {0, 4}, {0, 7}, {0, 8}, {0, 9}, {1, 6}, {3, 5}, {3, 6}, {3, 7}, {4, 6}, {6, 7}, {7, 9}, {8, 9}, },{{0, 2, 5, 7, },{4, 9, },{5, 6, 7, },}}},

    //        24

    TestCase{5, Map{10, 4, 4, {{0, 6}, {0, 8}, {0, 9}, {1, 4}, {1, 5}, {1, 6}, {1, 8}, {2, 3}, {2, 6}, {2, 7}, {3, 7}, {3, 8}, {4, 5}, {4, 9}, {5, 7}, {5, 8}, },{{2, 9, },{0, },{0, },}}},

    //        25

    TestCase{5, Map{6, 0, 5, {{5, 4}, {4, 3}, {0, 1}, {0, 2}, {1, 2}, {2, 3}, },{{1, 2, },{5, 1, },{3, },}}},

    //        26

    TestCase{5, Map{10, 4, 1, {{0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 2}, {1, 7}, {1, 8}, {2, 9}, {3, 4}, {3, 5}, {3, 7}, {4, 5}, {4, 6}, {4, 7}, {5, 6}, {6, 9}, {8, 9}, },{{5, 6, 7, },{1, 5, },{9, },}}},

    //        27

    TestCase{5, Map{4, 0, 0, {{0, 1}, {0, 3}, {1, 2},}, {{1,}, {3, 2,},}}},

    //        28

    TestCase{3, Map{5, 3, 3, {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {3, 4},}, {{0, 1, 2,}, {2, 3, 4,},}}},

    TestCase{ 1, Map{ 2, 0, 0,

    { { 0, 1 } },

    { { 0 } }

    }},

    TestCase{ 7, Map{24, 0, 23,

    {

    { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 7 }, { 1, 6 },

    { 2, 5 }, { 3, 4 }, { 4, 14 }, { 4, 15 }, { 5, 12 },

    { 5, 13 }, { 6, 10 }, { 6, 11 }, { 7, 8 }, { 7, 9 },

    { 8, 19 }, { 9, 19 }, { 10, 18 }, { 11, 18 }, { 12, 17 },

    { 13, 17 }, { 14, 16 }, { 15, 16 }, { 16, 22 }, { 17, 21 },

    { 17, 22 }, { 18, 21 }, { 18, 20 }, { 19, 20 }, { 20, 23 },

    { 21, 23 }, { 22, 23 }

    },

    {

    { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 23 },

    { 8, 9, 10, 11, 12, 13, 14, 15, 20, 21, 22 },

    { 16, 17, 18, 19 }

    }

    }},

    //     29

    TestCase{0, {0,0,0,

    {{}},

    {{}}

    }},

    //     30

    TestCase{0, {1,0,0,

    {{}},

    {{}}

    }},
  TestCase{ 3, Map{ 2, 0, 0,
    { { 0, 1 } },
    { { 1 } }
  }},
  TestCase{ 3, Map{ 4, 0, 1,
    { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
    {}
  }},
  TestCase{ 4, Map{ 4, 0, 1,
    { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
    { { 2 } }
  }},
  TestCase{ 0, Map{ 4, 0, 1,
    { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
    { { 2 }, {} }
  }},
};

int main() {
  int fail = 0;
  for (size_t i = 0; i < examples.size(); i++) {
    auto sol = find_path(examples[i].second);
    if (sol.size() != examples[i].first) {
      std::cout << "Wrong anwer for map " << i << std::endl;
      fail++;
    }
  }

  if (fail) std::cout << "Failed " << fail << " tests" << std::endl;
  else std::cout << "All tests completed" << std::endl;

  return 0;
}

#endif


