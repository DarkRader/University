#ifndef __PROGTEST__

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <variant>
#include <vector>

using State = unsigned int;
using Symbol = uint8_t;

struct NFA {
    std::set<State> m_States;
    std::set<Symbol> m_Alphabet;
    std::map<std::pair<State, Symbol>, std::set<State>> m_Transitions;
    State m_InitialState;
    std::set<State> m_FinalStates;
};

struct DFA {
    std::set<State> m_States;
    std::set<Symbol> m_Alphabet;
    std::map<std::pair<State, Symbol>, State> m_Transitions;
    State m_InitialState;
    std::set<State> m_FinalStates;
};

#endif


//class for preparing all needs information about transition
class CTransitions
{
public:
    CTransitions(std::map<std::pair<State, Symbol>, std::set<State>> transitionsA,
                 std::map<std::pair<State, Symbol>, std::set<State>> transitionsB,
                 State state, std::set<Symbol> alph, std::map<State, std::pair <std::set<State>, std::set<State>>>& existState)
    {
        
        State i = 0;
        for(auto itAlph = alph.begin(); itAlph != alph.end(); ++itAlph)
        {
            auto itA = transitionsA.find(std::make_pair(state, *itAlph));
            m_NFAstateA.push_back(std :: set<State>());
            if(itA != transitionsA.end()) {
                for(auto it = itA->second.begin(); it != itA->second.end(); ++it)
                {
                    m_NFAstateA[i].insert(*it);
                }
            }
            
            auto itB = transitionsB.find(std::make_pair(state, *itAlph));
            m_NFAstateB.push_back(std :: set<State>());
            if(itB != transitionsB.end()) {
                for(auto it = itB->second.begin(); it != itB->second.end(); ++it)
                {
                    m_NFAstateB[i].insert(*it);
                }
            }
            i++;
        }
        
        State stage = 1;
        auto itA = m_NFAstateA.begin(), itB = m_NFAstateB.begin();
        while(itA != m_NFAstateA.end() && itB != m_NFAstateB.end())
        {
            existState.insert({stage, std::make_pair(*itA, *itB)});
            auto itExState = existState.find(stage);
            if(itExState != existState.end())
                stage++;
            itA++;
            itB++;
        }
    }
    
    CTransitions(std::map<std::pair<State, Symbol>, std::set<State>> transitionsA,
                 std::map<std::pair<State, Symbol>, std::set<State>> transitionsB,
                 State state, std::set<Symbol> alph, std::map<State, std::pair <std::set<State>, std::set<State>>>::iterator& existState)
    {
        State i = 0;
        
        for(auto itAlph = alph.begin(); itAlph != alph.end(); ++itAlph)
        {
            std::cout << *itAlph << std::endl;
            m_NFAstateA.push_back(std :: set<State>());
            for(auto it = existState->second.first.begin(); it != existState->second.first.end(); ++it) {
                std::cout << *it << std::endl;
                auto itTranA = transitionsA.find(std::make_pair(*it, *itAlph));
                for(auto itA = itTranA->second.begin(); itA != itTranA->second.end(); ++itA) {
                    std::cout << *itA << std::endl;
                    m_NFAstateA[i].insert(*itA);
                }
            }
            
            m_NFAstateB.push_back(std :: set<State>());
            for(auto it = existState->second.second.begin(); it != existState->second.second.end(); ++it) {
                auto itTranB = transitionsB.find(std::make_pair(*it, *itAlph));
                for(auto itB = itTranB->second.begin(); itB != itTranB->second.end(); ++itB) {
                    m_NFAstateB[i].insert(*itB);
                }
            }
            i++;
        }
        
    }
    
    bool addNewStage()
    {
        
        
        return true;
    }
    
    std::vector<std::set<State>> getStateA (void) const { return m_NFAstateA; }
    std::vector<std::set<State>> getStateB (void) const { return m_NFAstateB; }
    
private:
    std::vector<std::set<State>> m_NFAstateA;
    std::vector<std::set<State>> m_NFAstateB;
};

//fill automat all alphabet which will be in result DFA
void fillAlph (const NFA& a, const NFA& b, DFA& resDFA)
{
    for(auto itA = a.m_Alphabet.begin(), itB = b.m_Alphabet.begin();
            itA != a.m_Alphabet.end() && itB != b.m_Alphabet.end(); )
        {
            if(*itA == *itB) {
                resDFA.m_Alphabet.insert(*itA);
                if(itA != a.m_Alphabet.end()) { itA++; }
                if(itB != b.m_Alphabet.end()) { itB++; }
            } else if(*itA < *itB) {
                resDFA.m_Alphabet.insert(*itA);
                if(itA != a.m_Alphabet.end()) { itA++; }
            } else if(*itA > *itB) {
                resDFA.m_Alphabet.insert(*itB);
                if(itB != b.m_Alphabet.end()) { itB++; }
            }
        }
}

void fillState (const NFA& a, const NFA& b, DFA& resDFA)
{
    State curState = 0;
    size_t lenghtOfStage = 0;
    
    //std::set<std::pair <std::set<State>, std::set<State>>> existState;
    std::map<State, std::pair <std::set<State>, std::set<State>>> existState;

    std::map<State, CTransitions> infoTransitions;
    
    infoTransitions.insert({0, CTransitions(a.m_Transitions, b.m_Transitions, 0, resDFA.m_Alphabet, existState)});
    
    curState++;
    
    std::cout << "Control!" << std::endl;
    
    while(true)
    {
        lenghtOfStage = existState.size();
        
        auto itState = existState.find(curState);
        
        std::cout << itState->first << std::endl;
        infoTransitions.insert({curState, CTransitions(a.m_Transitions, b.m_Transitions, curState, resDFA.m_Alphabet, itState)});
    }
    
    
}

DFA unify(const NFA& a, const NFA& b)
{
    DFA resDFA;
    
    return resDFA;
}

DFA intersect(const NFA& a, const NFA& b)
{
    DFA resDFA;
    
    //std::vector<State> existState;
    
    fillAlph(a, b, resDFA);
    
    fillState(a, b, resDFA);
    
    

    
    return resDFA;
}

#ifndef __PROGTEST__

// You may need to update this function or the sample data if your state naming strategy differs.
bool operator==(const DFA& a, const DFA& b)
{
    return std::tie(a.m_States, a.m_Alphabet, a.m_Transitions, a.m_InitialState, a.m_FinalStates) == std::tie(b.m_States, b.m_Alphabet, b.m_Transitions, b.m_InitialState, b.m_FinalStates);
}

int main()
{
    NFA a1 {
        {0, 1, 2},
        {'a', 'b'},
        {
            {{0, 'a'}, {0, 1}},
            {{0, 'b'}, {0}},
            {{1, 'a'}, {2}},
        },
        0,
        {2},
    };
    NFA a2 {
        {0, 1, 2},
        {'a', 'b'},
        {
            {{0, 'a'}, {1}},
            {{1, 'a'}, {2}},
            {{2, 'a'}, {2}},
            {{2, 'b'}, {2}},
        },
        0,
        {2},
    };
    DFA a {
        {0, 1, 2, 3, 4},
        {'a', 'b'},
        {
            {{0, 'a'}, {1}},
            {{1, 'a'}, {2}},
            {{2, 'a'}, {2}},
            {{2, 'b'}, {3}},
            {{3, 'a'}, {4}},
            {{3, 'b'}, {3}},
            {{4, 'a'}, {2}},
            {{4, 'b'}, {3}},
        },
        0,
        {2},
    };
    assert(intersect(a1, a2) == a);

    NFA b1 {
        {0, 1, 2, 3, 4},
        {'a', 'b'},
        {
            {{0, 'a'}, {1}},
            {{0, 'b'}, {2}},
            {{2, 'a'}, {2, 3}},
            {{2, 'b'}, {2}},
            {{3, 'a'}, {4}},
        },
        0,
        {1, 4},
    };
    NFA b2 {
        {0, 1, 2, 3, 4},
        {'a', 'b'},
        {
            {{0, 'b'}, {1}},
            {{1, 'a'}, {2}},
            {{2, 'b'}, {3}},
            {{3, 'a'}, {4}},
            {{4, 'a'}, {4}},
            {{4, 'b'}, {4}},
        },
        0,
        {4},
    };
    DFA b {
        {0, 1, 2, 3, 4, 5},
        {'a', 'b'},
        {
            {{0, 'a'}, {1}},
            {{0, 'b'}, {2}},
            {{2, 'a'}, {3}},
            {{3, 'a'}, {1}},
            {{3, 'b'}, {4}},
            {{4, 'a'}, {5}},
            {{5, 'a'}, {5}},
            {{5, 'b'}, {5}},
        },
        0,
        {1, 5},
    };
    assert(unify(b1, b2) == b);

    NFA c1 {
        {0, 1, 2, 3, 4},
        {'a', 'b'},
        {
            {{0, 'a'}, {1}},
            {{0, 'b'}, {2}},
            {{2, 'a'}, {2, 3}},
            {{2, 'b'}, {2}},
            {{3, 'a'}, {4}},
        },
        0,
        {1, 4},
    };
    NFA c2 {
        {0, 1, 2},
        {'a', 'b'},
        {
            {{0, 'a'}, {0}},
            {{0, 'b'}, {0, 1}},
            {{1, 'b'}, {2}},
        },
        0,
        {2},
    };
    DFA c {
        {0},
        {'a', 'b'},
        {},
        0,
        {},
    };
    assert(intersect(c1, c2) == c);

    NFA d1 {
        {0, 1, 2, 3},
        {'i', 'k', 'q'},
        {
            {{0, 'i'}, {2}},
            {{0, 'k'}, {1, 2, 3}},
            {{0, 'q'}, {0, 3}},
            {{1, 'i'}, {1}},
            {{1, 'k'}, {0}},
            {{1, 'q'}, {1, 2, 3}},
            {{2, 'i'}, {0, 2}},
            {{3, 'i'}, {3}},
            {{3, 'k'}, {1, 2}},
        },
        0,
        {2, 3},
    };
    NFA d2 {
        {0, 1, 2, 3},
        {'i', 'k'},
        {
            {{0, 'i'}, {3}},
            {{0, 'k'}, {1, 2, 3}},
            {{1, 'k'}, {2}},
            {{2, 'i'}, {0, 1, 3}},
            {{2, 'k'}, {0, 1}},
        },
        0,
        {2, 3},
    };
    DFA d {
        {0, 1, 2, 3},
        {'i', 'k', 'q'},
        {
            {{0, 'i'}, {1}},
            {{0, 'k'}, {2}},
            {{2, 'i'}, {3}},
            {{2, 'k'}, {2}},
            {{3, 'i'}, {1}},
            {{3, 'k'}, {2}},
        },
        0,
        {1, 2, 3},
    };
    assert(intersect(d1, d2) == d);
}
#endif
