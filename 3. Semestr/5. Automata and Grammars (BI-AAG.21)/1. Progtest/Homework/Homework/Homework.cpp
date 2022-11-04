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
        auto itState = existState.find(state);
        
        for(auto itAlph = alph.begin(); itAlph != alph.end(); ++itAlph)
        {
            //std::cout << "Alphabet: " << *itAlph << std::endl;
            
            m_automatA.push_back(std :: set<State>());
            for(auto it = itState->second.first.begin(); it != itState->second.first.end(); ++it) {
                fillAutomat(transitionsA, itState, itAlph, i, m_automatA, it);
            }
            
            m_automatB.push_back(std :: set<State>());
            for(auto it = itState->second.second.begin(); it != itState->second.second.end(); ++it) {
                fillAutomat(transitionsB, itState, itAlph, i, m_automatB, it);
            }

            i++;
        }
        
        //TODO non-correct filling - correct stage
        State stage = 1;
        auto itA = m_automatA.begin(), itB = m_automatB.begin();
        while(itA != m_automatA.end() && itB != m_automatB.end())
        {
            existState.insert({stage, std::make_pair(*itA, *itB)});
            auto itExState = existState.find(stage); //this stage
            if(itExState != existState.end())
                stage++;
            itA++;
            itB++;
        }
    }
    
    std::vector<std::set<State>> getStateA (void) const { return m_automatA; }
    std::vector<std::set<State>> getStateB (void) const { return m_automatB; }
    
private:
    std::vector<std::set<State>> m_automatA;
    std::vector<std::set<State>> m_automatB;
    
    void fillAutomat(std::map<std::pair<State, Symbol>, std::set<State>> transition, std::map<State, std::pair <std::set<State>, std::set<State>>>::iterator& itState, std::set<Symbol>::iterator itAlph, State i, std::vector<std::set<State>>& automat, std::set<State>::iterator& it)
    {
        //std::cout << "Stage automat: " << *it << std::endl;
        auto itTran = transition.find(std::make_pair(*it, *itAlph));
        if(itTran != transition.end()) {
            for(auto itAutomat = itTran->second.begin(); itAutomat != itTran->second.end(); ++itAutomat) {
                //std::cout << "Add stage automat: " << *itAutomat << std::endl;
                automat[i].insert(*itAutomat);
            }
        }
    }
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
    std::map<State, std::pair <std::set<State>, std::set<State>>> existState;
    std::map<State, CTransitions> infoTransitions;
    std::set<State> startStage = {0};
    
    existState.insert({curState, std::make_pair(startStage, startStage)});
    
    while(true)
    {
        lenghtOfStage = existState.size();
        infoTransitions.insert({curState, CTransitions(a.m_Transitions, b.m_Transitions, curState, resDFA.m_Alphabet, existState)});
        
        curState++;
        
        if(lenghtOfStage == existState.size())
            break;
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
