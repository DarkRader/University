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
    CTransitions(const NFA& a, const NFA& b,
                 State state, std::set<Symbol> alph, State& finalState,
                 std::map<State, std::pair <std::set<State>, std::set<State>>>& existState,
                 std::map<std::pair <std::set<State>, std::set<State>>, State>& elemOfStages) {
        
        fillTransition(a, b, state, alph, existState);
        
        //filling new States in automation
        size_t stage = existState.size();
        size_t controlSize = existState.size() - 1;
        auto itA = m_automatA.begin(), itB = m_automatB.begin();
        while(itA != m_automatA.end() && itB != m_automatB.end()) {
            size_t newOrNotNewElem = elemOfStages.size();
            elemOfStages.insert({std::make_pair(*itA, *itB), (unsigned int)stage});
            if(newOrNotNewElem != elemOfStages.size()) {
                existState.insert({(unsigned int)stage, std::make_pair(*itA, *itB)});
                stage++;
            }
            itA++;
            itB++;
        }
        
        auto itEnd = existState.end();
        auto itControl = existState.find((unsigned int)controlSize);
        --itEnd;
        if(itEnd == itControl && controlSize == existState.size() - 1) {
            finalState = (unsigned int)controlSize + 1;
        }
    }
    
    void addTransitionInDFA(std::map<State, std::pair <std::set<State>, std::set<State>>> existState,
                            std::map<std::pair <std::set<State>, std::set<State>>, State> elemOfStages,
                            DFA& resDFA, State state)
    {
        auto itA = m_automatA.begin(), itB = m_automatB.begin();
        for(auto itAlph = resDFA.m_Alphabet.begin(); itAlph != resDFA.m_Alphabet.end(); ++itAlph) {
            if(itA != m_automatA.end() && itB != m_automatB.end()) {
                auto renameState = elemOfStages.find(std::make_pair(*itA, *itB));
                State trans = renameState->second;
                resDFA.m_Transitions.insert({std::make_pair(state, *itAlph), trans});
                itA++;
                itB++;
            }
        }
    }
    
    std::vector<std::set<State>> getStateA (void) const { return m_automatA; }
    std::vector<std::set<State>> getStateB (void) const { return m_automatB; }
    State getStartState (void) const { return m_startState; }
    State getEndState (void) const { return m_endState; }
    
private:
    std::vector<std::set<State>> m_automatA;
    std::vector<std::set<State>> m_automatB;
    State m_startState = 0;
    State m_endState = 0;
    
    void fillAutomat(const NFA& transition, std::map<State, std::pair <std::set<State>, std::set<State>>>::iterator& itState, std::set<Symbol>::iterator itAlph, State i, std::vector<std::set<State>>& automat, std::set<State>::iterator& it) {
        auto itTran = transition.m_Transitions.find(std::make_pair(*it, *itAlph));
        if(itTran != transition.m_Transitions.end()) {
            for(auto itAutomat = itTran->second.begin(); itAutomat != itTran->second.end(); ++itAutomat) {
                automat[i].insert(*itAutomat);
            }
        }
    }
    
    void fillTransition(const NFA& a, const NFA& b, State state, std::set<Symbol> alph,
                        std::map<State, std::pair <std::set<State>, std::set<State>>>& existState) {
        State i = 0;
        auto itState = existState.find(state);
        for(auto itAlph = alph.begin(); itAlph != alph.end(); ++itAlph) {
            std::set<State> endState = a.m_FinalStates;
            m_automatA.push_back(std :: set<State>());
            for(auto it = itState->second.first.begin(); it != itState->second.first.end(); ++it) {
                std::set<State> endState = a.m_FinalStates;
                size_t sizeEndState = endState.size();
                if(*it == a.m_InitialState && m_startState == 0) {
                    m_startState++;
                }
                endState.insert(*it);
                if(endState.size() == sizeEndState && m_endState == 0) {
                    m_endState++;
                }
                fillAutomat(a, itState, itAlph, i, m_automatA, it);
            }
            
            m_automatB.push_back(std :: set<State>());
            for(auto it = itState->second.second.begin(); it != itState->second.second.end(); ++it) {
                std::set<State> endState = a.m_FinalStates;
                size_t sizeEndState = endState.size();
                if(*it == b.m_InitialState && m_startState == 1) {
                    m_startState++;
                }
                endState.insert(*it);
                if(endState.size() == sizeEndState && m_endState == 1) {
                    m_endState++;
                }
                fillAutomat(b, itState, itAlph, i, m_automatB, it);
            }
            i++;
        }
    }
};

//rename States for new DFA automation
void renameStates(DFA& resDFA, std::map<State, CTransitions> infoTransitions,
                  std::map<State, std::pair <std::set<State>, std::set<State>>> existState,
                  std::map<std::pair <std::set<State>, std::set<State>>, State> elemOfStages) {
    for(auto it = infoTransitions.begin(); it != infoTransitions.end(); ++it) {
        resDFA.m_States.insert(it->first);
        it->second.addTransitionInDFA(existState, elemOfStages, resDFA, it->first);
        if(it->second.getStartState() == 2) {
            resDFA.m_InitialState = it->first;
        }
        if(it->second.getEndState() == 2) {
            resDFA.m_FinalStates.insert(it->first);
        }
    }
    
}

//fill automat all alphabet which will be in result DFA
void fillAlph (const NFA& a, const NFA& b, DFA& resDFA) {
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

//preparing new State for DFA automation
void fillState (const NFA& a, const NFA& b, DFA& resDFA, std::map<State, CTransitions>& infoTransitions,
                std::map<State, std::pair <std::set<State>, std::set<State>>>& existState,
                std::map<std::pair <std::set<State>, std::set<State>>, State>& elemOfStages) {
    State curState = 0;
    State finalState = 0;
    size_t lenghtOfStage = 0;
    
    elemOfStages.insert({{{0}, {0}}, 0});
    existState.insert({curState, elemOfStages.begin()->first});
    
    while(true) {
        lenghtOfStage = existState.size();
        infoTransitions.insert({curState, CTransitions(a, b, curState, resDFA.m_Alphabet, finalState, existState, elemOfStages)});
        curState++;
        
        if(infoTransitions.size() == finalState) {
            break;
        }
    }
}

//void removingInaccessibleStates(DFA& DFA)
//{
//    std::vector<bool> inacState(DFA.m_States.size(), false);
//    inacState[DFA.m_InitialState] = true;
//    std::queue<State> que;
//    que.push(DFA.m_InitialState);
//
//    while(!que.empty())
//    {
//        State curState = que.front();
//        que.pop();
//
//        for(auto itAlph = DFA.m_Alphabet.begin(); itAlph != DFA.m_Alphabet.end(); ++itAlph)
//        {
//            auto it = DFA.m_Transitions.find({curState, *itAlph});
//            //inacState[it->second] = true;
//            if(curState != it->second && inacState[it->second] == false)
//                que.push(it->second);
//            inacState[it->second] = true;
//        }
//    }
//
//    size_t i = 0;
//    for(auto it = DFA.m_States.begin(); it != DFA.m_States.end(); ++i)
//    {
//        if(inacState[i] == false)
//        {
//            auto tmpIt = it;
//            it++;
//            DFA.m_States.erase(tmpIt);
//            auto itMap = m_
//        }
//    }
//
//}

//void removeUselessStates(DFA& DFA) {
//    std::vector<State> uselessState;
//
//    for(auto itAlph = DFA.m_Alphabet.begin(); itAlph != DFA.m_Alphabet.end(); ++itAlph) {
//        for(size_t i = 0; i < DFA.m_States.size(); ++i) {
//            auto it = DFA.m_Transitions.find({i, *itAlph});
//        }
//    }
//}

void removeUselessStates(DFA& DFA) {
    std::vector<State> usefulState;
    usefulState.push_back(*DFA.m_FinalStates.begin());
    
    for(size_t i = 0; usefulState.size() == 1; i++) {
        for(size_t i = 0; i < DFA.m_States.size(); i++) {
            for(auto itAlph = DFA.m_Alphabet.begin(); itAlph != DFA.m_Alphabet.end(); ++itAlph) {
                auto it = DFA.m_Transitions.find({i, *itAlph});
                if(it->second == usefulState[i]) {
                    usefulState.push_back(it->first.first);
                    break;
                }
            }
            if(usefulState[usefulState.size() - 1] == usefulState[usefulState.size() - 2]) {
                break;
            }
        }
    }
}

void minimizationDFA(DFA& resDFA) {
    removeUselessStates(resDFA);
    
    
}

DFA unify(const NFA& a, const NFA& b) {
    DFA resDFA;
    
    return resDFA;
}

DFA intersect(const NFA& a, const NFA& b) {
    DFA resDFA;
    std::map<State, CTransitions> infoTransitions;
    std::map<State, std::pair <std::set<State>, std::set<State>>> existState;
    std::map<std::pair <std::set<State>, std::set<State>>, State> elemOfStages;
    
    fillAlph(a, b, resDFA);
    fillState(a, b, resDFA, infoTransitions, existState, elemOfStages);
    renameStates(resDFA, infoTransitions, existState, elemOfStages);
    minimizationDFA(resDFA);
    
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
