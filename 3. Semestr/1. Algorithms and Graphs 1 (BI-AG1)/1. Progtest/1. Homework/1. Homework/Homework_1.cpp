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
    CGraph(std::string condition)
    : m_condition(condition) {}
    
    Place getTypesItems(void) const { return m_contItem.size(); }
    std::string getCondition(void) const { return m_condition; }
    std::vector<Place> getContItem(void) const { return m_contItem; }
    std::vector<Place> getNeighbours(void) const { return m_neighbours; }
    void changeCondition(std::string newCondition) { m_condition = newCondition; }
    
    void addNeighbours(Place name, const Map &map)
    {
        for(Place i = 0; i < map.connections.size(); i++) {
            if(map.connections[i].first == name)
                m_neighbours.push_back(map.connections[i].second);
            else if(map.connections[i].second == name)
                m_neighbours.push_back(map.connections[i].first);
        }
    }
    
    void controlExistItems(const Map &map, Place name, Place types)
    {
        for(Place i = 0; i < map.items.size(); i++) {
            for(auto it = map.items.at(i).begin(); it != map.items.at(i).end(); it++) {
                if(*it == name)
                    m_contItem.push_back(i);
            }
        }
    }
    
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
    std::string m_condition;
};

class CPath
{
public:
    CPath(Place distance, Place level) : m_distance(distance), m_level(level) {}
    CPath(Place distance, Place level, std::vector<Place> contItem) : m_distance(distance), m_level(level)
    {
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
    void changeLevel(Place level) { m_level = level; }
    std::vector<Place> getTraceItem(void) { return m_traceItem; }
    
    bool newOrNotNewItem(std::vector<Place> father, std::vector<Place> son, std::vector<Place> & itemPath)
    {
        if(father.size() == 0 && son.size() != 0)
            return true;
        
        for(Place i = 0; i < m_traceItem.size(); i++) {
            itemPath.push_back(m_traceItem[i]);
        }
        
        Place oldSize = father.size();
        
        Place newSize = oldSize;
        
        for(Place i = 0; i < father.size(); i++) {
            for(Place j = 0; j < son.size(); j++) {
                if(father[i] == son[j])
                    break;
                else if(j == father.size() - 1) {
                    newSize++; //m_traceItem.push_back(son[i]);
                    itemPath.push_back(son[i]);
                }
            }
        }
        
        //Place newSize = m_traceItem.size();
        
        if(oldSize == newSize)
            return false;
        else
            return true;
    }
    
    
private:
    Place m_distance;
    Place m_level;
    std::vector<Place> m_traceItem;
    //std::list<Place> m_path;
    
};

//control, that we don't have any empty type of items
int control_items(const Map &map)
{
    int i;
    for(i = 0; i < map.items.size(); i++)
        if(map.items[i].size() == 0)
            return -1;
    return i;
}

std::list<Place> find_path(const Map &map) {
    //list for path
    std::list<Place> m_path;
    Place typeItems = 0;
  
    typeItems = control_items(map);
    if(typeItems == -1)
        return m_path;
      
    std::unordered_map<Place, CGraph> Vertex_contents;

    std::queue<std::pair<Place, CPath>> que;

    std::vector<std::vector<Place>> visited;
    Place level = 0;
    Vertex_contents.insert({map.start, CGraph("open")});
      
    auto iter = Vertex_contents.find(map.start);
    que.push({map.start, {0, 0}});
    iter->second.addNeighbours(iter->first, map);
    iter->second.controlExistItems(map, iter->first, typeItems);

    visited.push_back(std :: vector<Place>());
    visited[level].push_back(map.start);
    
//    if(que.front() == map.end && iter->second.getTypesItems() == typeItems) {
//        m_path.push_back(map.start);
//        return m_path;
//    }
    
    while(!que.empty())
    {
        auto node = Vertex_contents.find(que.front().first);
        Place currentNode = node->first;
        if(currentNode == 4) // 1
            std::cout << "Control vertex!" << std::endl;
        CPath addInfVer = que.front().second;
        que.pop();
        
        
        for(Place i = 0; i < node->second.getNeighbours().size(); i++) {
            if(node->second.visitedOrNot(visited[addInfVer.getLevel()], node->second.getNeighbours()[i]) == false) {
                
                auto tmpNode = Vertex_contents.find(node->second.getNeighbours()[i]);
                
                if(tmpNode == Vertex_contents.end()) {
                    Vertex_contents.insert({node->second.getNeighbours()[i], CGraph("open")});
                    tmpNode = Vertex_contents.find(node->second.getNeighbours()[i]);
                    tmpNode->second.addNeighbours(tmpNode->first, map);
                    tmpNode->second.controlExistItems(map, tmpNode->first, typeItems);
                }

                Place newNode = tmpNode->first;

                std::vector<Place> newItemPath;
                if(addInfVer.newOrNotNewItem(addInfVer.getTraceItem(), tmpNode->second.getContItem(), newItemPath) == true) {
                    level++;
                    visited.push_back(std :: vector<Place>());
                    visited[level].push_back(tmpNode->first);
                    if(addInfVer.getTraceItem().size() > 0)
                        que.push({tmpNode->first, {addInfVer.getDistance() + 1, level, newItemPath}});
                        //que.push({tmpNode->first, {addInfVer.getDistance() + 1, level, addInfVer.getTraceItem()}});
                    else
                        que.push({tmpNode->first, {addInfVer.getDistance() + 1, level, node->second.getContItem()}});
                } else {
                    visited[addInfVer.getLevel()].push_back(tmpNode->first);
                    if(node->second.getTypesItems() != 0 && tmpNode->second.getTypesItems() == 0)
                        //que.push({tmpNode->first, {addInfVer.getDistance() + 1, addInfVer.getLevel(), newItemPath}});
                        que.push({tmpNode->first, {addInfVer.getDistance() + 1, addInfVer.getLevel(), node->second.getContItem()}});
                    else
                        que.push({tmpNode->first, {addInfVer.getDistance() + 1, addInfVer.getLevel(), addInfVer.getTraceItem()}});
                    //que.push({tmpNode->first, {addInfVer.getDistance() + 1, addInfVer.getLevel(), newItemPath}});
                }
            }
        }
        
        auto newNode = Vertex_contents.find(que.front().first);
        
        if(level > 3) //hodnota 3 je uzitecna //5 //6 //7
        {
            std::cout << "Control level!" << std::endl;
        }
        
        if(newNode->first == map.end && addInfVer.getTraceItem().size() == typeItems) {
            std::cout << newNode->first << std::endl;
            std::cout << addInfVer.getTraceItem().size() << std::endl;
            std::cout << addInfVer.getDistance() << std::endl;
            
            break;
        }
            //return m_path;
        node->second.changeCondition("close");
    }
      
      
       return m_path;
}

#ifndef __PROGTEST__

using TestCase = std::pair<size_t, Map>;

// Class template argument deduction exists since C++17 :-)
const std::array examples = {
    TestCase{5, Map{11, 0, 10,
        {{0, 1}, {0, 2}, {0, 5}, {1, 3}, {1, 4}, {1, 8}, {5, 9}, {5, 6}, {5, 10}, {2, 7}, {7, 6}, {8, 10}, {7, 10}},
        {{2, 6, 3, 9}, {4, 9}}
    }},
    
  TestCase{ 1, Map{ 2, 0, 0,
    { { 0, 1 } },
    { { 0 } }
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
