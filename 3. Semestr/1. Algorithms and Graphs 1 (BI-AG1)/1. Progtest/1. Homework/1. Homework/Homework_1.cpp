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
    CGraph(Place distance, std::string condition, Place level /*const Map &map, Place types*/)
    : m_distance(distance), m_condition(condition), m_level(level) {}
    
    Place getTypesItems(void) const { return m_contItem.size(); }
    Place getTraceItems(void) const { return m_traceItem.size(); }
    std::string getCondition(void) const { return m_condition; }
    std::vector<Place> getContItem(void) const { return m_contItem; }
    std::vector<Place> getNeighbours(void) const { return m_neighbours; }
    Place getDistance(void) const { return m_distance; }
    Place getLevel(void) const { return m_level; }
    void changeLevel(Place level) { m_level = level; }
    void changeCondition(std::string newCondition) { m_condition = newCondition; }
    void changeDistantion(Place distantion) { m_distance = distantion + 1; }
    
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
    
    void addTraceItem(std::vector<Place> contItem)
    {
        if(contItem.size() != 0) {
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
    
    void addNewTraceItem(std::vector<Place> contItem)
    {
        if(m_traceItem.size() == 0) {
            for(Place i = 0; i < contItem.size(); i++) {
                m_traceItem.push_back(contItem[i]);
            }
        } else {
            
        }
    }
    
//    bool controlRightItems(std::vector<Place> contItem)
//    {
//        if(contItem)
//    }
    
    bool visitedOrNot(std::vector<Place> vis, Place name)
    {
        for(Place i = 0; i < vis.size(); i++) {
            if(vis[i] == name)
                return true;
        }
        return false;
    }

private:
    Place m_distance;
    std::vector<Place> m_contItem;
    std::vector<Place> m_traceItem;
    std::vector<Place> m_neighbours;
    std::string m_condition;
    Place m_level;
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
    //std::vector<std::pair<Place, std::string>> queue;
    std::queue<Place> que;
    //std::queue<CGraph> que;
    //std::vector<Place> visited;
    std::vector<std::vector<Place>> visited;
    Place level = 0;
    Vertex_contents.insert({map.start, CGraph(0, "open", 0)});
      
    auto iter = Vertex_contents.find(map.start);
    que.push(map.start);
    iter->second.addNeighbours(iter->first, map);
    iter->second.controlExistItems(map, iter->first, typeItems);
    //visited.push_back(map.start);
    visited.push_back(std :: vector<Place>());
    visited[level].push_back(map.start);
    
//    if(que.front() == map.end && iter->second.getTypesItems() == typeItems) {
//        m_path.push_back(map.start);
//        return m_path;
//    }
    
    while(!que.empty())
    {
        auto node = Vertex_contents.find(que.front());
        que.pop();
        for(Place i = 0; i < node->second.getNeighbours().size(); i++) {
            Place currentNode = node->first;
            if(node->second.visitedOrNot(visited[node->second.getLevel()], node->second.getNeighbours()[i]) == false) {
                Vertex_contents.insert({node->second.getNeighbours()[i], CGraph(node->second.getDistance() + 1, "open", node->second.getLevel())});
                
                auto tmpNode = Vertex_contents.find(node->second.getNeighbours()[i]);
                Place newNode = tmpNode->first;
                tmpNode->second.controlExistItems(map, tmpNode->first, typeItems);
                
                if(node->second.getTypesItems() < tmpNode->second.getTypesItems()) {
                    level++;
                    tmpNode->second.changeLevel(level);
                    visited.push_back(std :: vector<Place>());
                    visited[level].push_back(tmpNode->first);
                } else {
                    visited[node->second.getLevel()].push_back(tmpNode->first);
                    tmpNode->second.changeLevel(node->second.getLevel());
                }
                
                if(node->second.getTypesItems() > 0) {
                    tmpNode->second.addNewTraceItem(node->second.getContItem());
                }
                   
                tmpNode->second.addTraceItem(node->second.getContItem());
                que.push(tmpNode->first);
                //que.push(node->second.getNeighbours()[i]);
                //visited.push_back(node->second.getNeighbours()[i]);
            }
        }
        auto newNode = Vertex_contents.find(que.front());
        if(newNode->second.getCondition() == "open")
            newNode->second.addNeighbours(newNode->first, map);
        else
            newNode->second.changeDistantion(node->second.getDistance());
        //newNode->second.controlExistItems(map, newNode->first, typeItems);
        
        
        if(level > 7)
            break;
        
        if(newNode->first == map.end && newNode->second.getTypesItems() == typeItems)
            break;
            //return m_path;
        node->second.changeCondition("close");
    }

    
    
    
    
    
  //    m_path.push_back(map.start);
  //    if(!map.items.empty())
  //    {
  //        for(auto it = map.items.at(0).begin(); it != map.items.at(0).end(); ++it)
  //            std :: cout << (*it) << " ";
  //        std :: cout << std :: endl;
  //    }
      
  //    auto it = map.items.at(0).begin();
  //
  //    if((map.items.size() == 0 || (map.items.size() == 1 && it[0] == map.start))
  //       && map.start == map.end)
  //        return m_path;
      
      
      
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
