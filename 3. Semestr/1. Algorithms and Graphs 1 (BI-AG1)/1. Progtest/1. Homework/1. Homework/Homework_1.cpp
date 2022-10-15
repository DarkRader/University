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
    
    Place getTypesItems(void) const { return m_contItem.size(); }
    std::vector<Place> getContItem(void) const { return m_contItem; }
    std::vector<Place> getNeighbours(void) const { return m_neighbours; }
    std::vector<std::vector<Place>> getMaxItem(void) const { return m_maxItem; };
    void addMaxItem (std::vector<Place> maxItem) { m_maxItem.push_back(maxItem); }
    
    bool visitedOrNot(std::vector<Place> vis, Place name)
    {
        for(Place i = 0; i < vis.size(); i++) {
            if(vis[i] == name)
                return true;
        }
        return false;
    }

private:
    std::vector<Place> m_contItem;
    std::vector<Place> m_neighbours;
    std::vector<std::vector<Place>> m_maxItem;
    
};

class CPath
{
public:
    CPath(Place distance, Place level, std::list<Place> path, Place name) : m_distance(distance), m_level(level)
    {
        for(auto itr = path.begin(); itr != path.end(); itr++)
            m_path.push_back(*itr);
        m_path.push_back(name);
    }
    
    CPath(Place distance, Place level, std::vector<Place> contItem, std::list<Place> path, Place name) : m_distance(distance), m_level(level)
    {
        for(auto itr = path.begin(); itr != path.end(); itr++) {
            m_path.push_back(*itr);
        }
        m_path.push_back(name);
        
        if(m_traceItem.size() == 0) {
            for(Place i = 0; i < contItem.size(); i++) {
                m_traceItem.push_back(contItem[i]);
            }
        } else {
            for(Place i = 0; i < contItem.size(); i++) {
                for(Place j = 0; j < m_traceItem.size(); j++) {
                    if(contItem[i] == m_traceItem[j])
                        break;
                    else if(j == m_traceItem.size() - 1)
                        m_traceItem.push_back(contItem[i]);
                }
            }
        }
    }
    
    Place getDistance(void) { return m_distance; }
    Place getLevel(void) const { return m_level; }
    std::list<Place> getListPath(void) { return m_path; }
    std::vector<Place> getTraceItem(void) { return m_traceItem; }
    void changeLevel(Place level) { m_level = level; }

    void addStartItem(std::vector<Place> items)
    {
        for(Place i = 0; i < items.size(); i++)
            m_traceItem.push_back(items[i]);
    }
    
    bool newOrNotNewItem(std::vector<Place> father, std::vector<Place> son, std::vector<Place> & itemPath)
    {
        if(father.size() == 0 && son.size() != 0) {
            for(Place i = 0; i < son.size(); i++)
                itemPath.push_back(son[i]);
            return true;
        }
        
        for(Place i = 0; i < m_traceItem.size(); i++) {
            itemPath.push_back(m_traceItem[i]);
        }
        
        Place oldSize = father.size();
        Place newSize = oldSize;
        Place alrExist = 0;
        
        for(Place i = 0; i < son.size(); i++) {
            for(Place j = 0; j < father.size(); j++) {
                if(father[j] == son[i]) {
                    alrExist = 1;
                    break;
                }
                else if(j == father.size() - 1) {
                    newSize++;
                    itemPath.push_back(son[i]);
                }
            }
            if(alrExist == 1)
                break;
        }
        
        if(oldSize == newSize)
            return false;
        else
            return true;
    }
    
    bool closeRouteOrNot(std::vector<Place> itemPath, std::vector<std::vector<Place>> maxItem)
    {
        if(maxItem.size() == 0)
            return true;
        
        Place exBigger = 0;
        
        for(Place i = 0; i < maxItem.size(); i++) {
            if(maxItem[i].size() < itemPath.size()) {
                exBigger = 1;
            }
            else {
                if(haveNewItem(maxItem[i], itemPath) == false)
                    return false;
                exBigger = 0;
            }
        }
        if(exBigger == 1)
            return true;
        return true;
    }
    
private:
    Place m_distance;
    Place m_level;
    std::vector<Place> m_traceItem;
    std::list<Place> m_path;

    bool haveNewItem(std::vector<Place> maxItem, std::vector<Place> itemPath)
    {
        for(Place i = 0; i < itemPath.size(); i++)
            for(Place j = 0; j < maxItem.size(); j++)
                if(maxItem[j] == itemPath[i])
                    continue;
                else if(j == maxItem.size() - 1)
                    return true;
        return false;
    }
    
};

//control, that we don't have any empty type of items
bool control_items(const Map &map)
{
    for(Place i = 0; i < map.items.size(); i++)
        if(map.items[i].size() == 0)
            return false;
    return true;
}

std::list<Place> find_path(const Map &map) {
    //list for path
    std::list<Place> path;
    
    if(map.connections.size() == 0 || control_items(map) == false)
        return path;
      
    std::unordered_map<Place, CGraph> Vertex_contents;
    std::queue<std::pair<Place, CPath>> que;
    std::vector<std::vector<Place>> visited;
    Vertex_contents.insert({map.start, CGraph(map, map.start)});
    Place level = 0;
      
    auto iter = Vertex_contents.find(map.start);
    que.push({map.start, {0, 0, path, map.start}});
    visited.push_back(std :: vector<Place>());
    visited[level].push_back(map.start);
    
    if(iter->second.getContItem().size() > 0) {
        que.front().second.addStartItem(iter->second.getContItem());
    }
    
    while(!que.empty())
    {
        auto node = Vertex_contents.find(que.front().first);
        Place currentNode = node->first;
//        if(currentNode == 3) // 1
//            std::cout << "Control vertex!" << std::endl;
        CPath addInfVer = que.front().second;
        que.pop();
        
        
        for(Place i = 0; i < node->second.getNeighbours().size(); i++) {
            if(node->second.visitedOrNot(visited[addInfVer.getLevel()], node->second.getNeighbours()[i]) == false) {
                
                auto tmpNode = Vertex_contents.find(node->second.getNeighbours()[i]);
                
                if(tmpNode == Vertex_contents.end()) {
                    Vertex_contents.insert({node->second.getNeighbours()[i], CGraph(map, node->second.getNeighbours()[i])});
                    tmpNode = Vertex_contents.find(node->second.getNeighbours()[i]);
                }

                //Place newNode = tmpNode->first;
                if(addInfVer.closeRouteOrNot(addInfVer.getTraceItem(), tmpNode->second.getMaxItem()) == false)
                    continue;
                
                std::vector<Place> newItemPath;
                if(addInfVer.newOrNotNewItem(addInfVer.getTraceItem(), tmpNode->second.getContItem(), newItemPath) == true) {
                    level++;
                    visited.push_back(std :: vector<Place>());
                    visited[level].push_back(tmpNode->first);
                    tmpNode->second.addMaxItem(newItemPath);
                    que.push({tmpNode->first, {addInfVer.getDistance() + 1, level, newItemPath, addInfVer.getListPath(), tmpNode->first}});
                } else {
                    visited[addInfVer.getLevel()].push_back(tmpNode->first);
                    tmpNode->second.addMaxItem(newItemPath);
                    que.push({tmpNode->first, {addInfVer.getDistance() + 1, addInfVer.getLevel(), newItemPath, addInfVer.getListPath(), tmpNode->first}});
                }
            }
        }
        
        if(currentNode == map.end && addInfVer.getTraceItem().size() == map.items.size()) {
            return addInfVer.getListPath();
        }

    }
      
      
       return path;
}

#ifndef __PROGTEST__

using TestCase = std::pair<size_t, Map>;

// Class template argument deduction exists since C++17 :-)
const std::array examples = {
    //        0
    TestCase{1, Map{2, 0, 0,
        {{0, 1}},
        {{0}}
    }},
    //        1
    TestCase{3, Map{2, 0, 0,
    {{0, 1}},
        {{1}}
    }},
    //        2
    TestCase{3, Map{4, 0, 1,
    {{0, 2}, {2, 3}, {0, 3}, {3, 1}},
    {}
    }},
    //        3
    TestCase{4, Map{4, 0, 1,
    {{0, 2}, {2, 3}, {0, 3}, {3, 1}},
    {{2}}
    }},
    //        4
    TestCase{0, Map{4, 0, 1,
    {{0, 2}, {2, 3}, {0, 3}, {3, 1}},
    {{2}, {}}
    }},
    //        5
    TestCase{0, Map{6, 1, 4,
    {{1, 2}, {2, 3}, {2, 4}},
    {{5}}
    }},
    //        6
    TestCase{7, Map{6, 1, 5,
    {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}},
    {{0}, {4}}
    }},
    //        7
    TestCase{0, Map{6, 1, 4,
    {{1, 2}, {2, 3}, {2, 4}},
    {{5}, {1}, {2}, {3}, {4}}
    }},
    //       8
    TestCase{0, Map{6, 1, 4,
    {},
    {{5}, {1}, {2}, {3}, {4}}
    }},
    //       9
    TestCase{0, Map{6, 1, 1,
    {},
    {{5}, {1}, {2}, {3}, {4}}
    }},
    //      10
    TestCase{5, Map{5, 0, 2,
    {{1, 4}, {1, 3}, {2, 3}, {2, 4}, {0, 3}, {0, 4}},
    {{1, 3}, {3}, {4}}
    }},
    //      11
    TestCase{6, Map{6, 2, 4,
    {{0, 3}, {0, 4}, {0, 5}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5},},
    {{5}, {5}, {1}, {0, 1}, {0}, {3}, {4}}
    }},
    //      12
    TestCase{5, Map{11, 0, 10,
    {{0, 1}, {0, 2}, {0, 5}, {1, 3}, {1, 4}, {1, 8}, {5, 9}, {5, 6}, {5, 10}, {2, 7}, {7, 6}, {8, 10}, {7, 10}},
    {{2, 6, 3, 9}, {4, 9}}
    }},
    TestCase{5 ,Map{11, 0, 10,
    {{0, 5}, {0, 1 }, {0, 7}, {1, 2}, {1,3}, {1, 4}, {3, 10}, {5, 6}, {5, 10}, {5, 8}, {8, 9}, {7, 9}, {9, 10} },
    {
    {{2, 6, 8, 7}, {4, 6 }}
    }}},
    TestCase{ 6, Map{
    6, 0,5, {{0,1}, {0,2 }, {0, 3}, {1, 4}, {2, 4}, {3, 4}, {4, 5}},
    {{1}, {1, 2, 3}, {3}}
    }}
    ,TestCase { 0, Map
    {  15, 0, 7, {{0, 1}, {0, 8}, {8, 2},  {1, 3}, {2, 4}, {4, 5}, {5, 7}, {6, 9}, {9, 10}, {10, 7}}, {{1, 2}, {13}, {1, 4}} }},
    TestCase{ 4, Map {
    5, 0, 4, {{0, 1}, {0, 2}, {2, 3}, {3, 4}, {1, 4}}, {{1,2}, {1, 3}, {3}}
    }},
    TestCase { 9,
    Map { 5, 0, 0, {{0, 1}, {0, 2}, {0, 3}, {0,4}}, {{1}, {2}, {3},{4}}}
    },
    TestCase { 1,
    Map { 1, 0, 0, {{0, 0}}, {{0}, {0}, {0},{0}}}
    },
//  TestCase{ 1, Map{ 2, 0, 0,
//    { { 0, 1 } },
//    { { 0 } }
//  }},
//  TestCase{ 3, Map{ 2, 0, 0,
//    { { 0, 1 } },
//    { { 1 } }
//  }},
//  TestCase{ 3, Map{ 4, 0, 1,
//    { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
//    {}
//  }},
//  TestCase{ 4, Map{ 4, 0, 1,
//    { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
//    { { 2 } }
//  }},
//  TestCase{ 0, Map{ 4, 0, 1,
//    { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
//    { { 2 }, {} }
//  }},
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


