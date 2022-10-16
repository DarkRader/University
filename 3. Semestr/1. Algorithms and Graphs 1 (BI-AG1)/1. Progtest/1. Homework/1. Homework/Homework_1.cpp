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
    
    std::vector<Place> getContItem(void) const { return m_contItem; }
    std::vector<Place> getNeighbours(void) const { return m_neighbours; }
    std::vector<Place> getItemsInLevelLast(void) { return m_itemsInLevels[m_itemsInLevels.size() - 1]; };
    std::vector<std::vector<Place>> getInLevelFully(void) const { return m_itemsInLevels; }
    bool visitedOrNot(std::vector<Place> vis, Place name)
    {
        for(Place i = 0; i < vis.size(); i++)
            if(vis[i] == name)
                return true;
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
    CPath(Place distance, Place level, Place index, Place items, std::vector<Place> traceItem, std::list<Place> path, Place name) : m_distance(distance), m_level(level), m_index(index), m_itemsIn(items), m_traceItem(traceItem)
    {
        for(auto itr = path.begin(); itr != path.end(); itr++)
            m_path.push_back(*itr);
        m_path.push_back(name);
    }
    
    Place getDistance(void) { return m_distance; }
    Place getLevel(void) const { return m_level; }
    Place getIndex(void) const { return m_index; }
    Place getItemsIn(void) const { return m_itemsIn; }
    std::vector<Place> getTraceItem(void) { return m_traceItem; }
    std::list<Place> getListPath(void) { return m_path; }
    
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
    std::list<Place> m_path;
};

std::list<Place> find_path(const Map &map) {
    //list for path
    std::list<Place> path;
    
    Place level = 0;
    std::unordered_map<Place, CGraph> Vertex_contents;
    std::queue<std::pair<Place, CPath>> que;
    std::vector<std::vector<Place>> visited;
    Vertex_contents.insert({map.start, CGraph(map, map.start)});
      
    auto iter = Vertex_contents.find(map.start);
    iter->second.addItemsInLevel(map.items.size());
    que.push({map.start, {0, 0, 0, iter->second.getContItem().size(), iter->second.getItemsInLevelLast(), path, map.start}});
    visited.push_back(std :: vector<Place>());
    visited[level].push_back(map.start);
    
    while(!que.empty())
    {
        auto parentNode = Vertex_contents.find(que.front().first);
        Place parent = parentNode->first;
        CPath addInfVer = que.front().second;
        que.pop();

        for(Place i = 0; i < parentNode->second.getNeighbours().size(); i++) {
            if(parentNode->second.visitedOrNot(visited[addInfVer.getLevel()], parentNode->second.getNeighbours()[i]) == false) {

                auto childNode = Vertex_contents.find(parentNode->second.getNeighbours()[i]);

                if(childNode == Vertex_contents.end()) {
                    Vertex_contents.insert({parentNode->second.getNeighbours()[i], CGraph(map, parentNode->second.getNeighbours()[i])});
                    childNode = Vertex_contents.find(parentNode->second.getNeighbours()[i]);
                }

                if(addInfVer.closeRouteOrNot(addInfVer.getTraceItem(), childNode->second.getInLevelFully()) == false)
                    continue;

                Place itemSize = 0;
                if(addInfVer.newOrNotNewItem(addInfVer.getTraceItem(), childNode->second.getContItem(), itemSize) == true) {
                    level++;
                    visited.push_back(std :: vector<Place>());
                    visited[level].push_back(childNode->first);
                    childNode->second.addItemsInLevelNew(map.items.size(), addInfVer.getTraceItem());
                    que.push({childNode->first, {addInfVer.getDistance() + 1, level, 0, addInfVer.getItemsIn() + itemSize, childNode->second.getItemsInLevelLast(), addInfVer.getListPath(), childNode->first}});
                } else {
                    visited[addInfVer.getLevel()].push_back(childNode->first);
                    childNode->second.addItemsBin(map.items.size(), addInfVer.getTraceItem());
                    que.push({childNode->first, {addInfVer.getDistance() + 1, addInfVer.getLevel(), visited[addInfVer.getLevel()].size() - 1, addInfVer.getItemsIn(), addInfVer.getTraceItem(), addInfVer.getListPath(), childNode->first}});
                }
            }
        }
        
        if(parent == map.end && addInfVer.getItemsIn() == map.items.size()) {
            return addInfVer.getListPath();
        }

    }
      
      
       return path;
}

#ifndef __PROGTEST__

using TestCase = std::pair<size_t, Map>;

// Class template argument deduction exists since C++17 :-)
const std::array examples = {
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


