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

#define IntMax 1000000

//class for preparing all needs information about transition
class CTransition
{
public:
    CTransition(const NFA& a, const NFA& b, DFA& DFA, std::queue<State> & que, State state,
                 std::map<State, std::pair <std::set<State>, std::set<State>>>& existState,
                 std::map<std::pair <std::set<State>, std::set<State>>, State>& elemOfStages, State op) {
        if(op == 2) {
            m_intersect = true;
        } else {
            m_intersect = false;
        }
        
        fillTransition(a, b, DFA, state, existState);
        
        //filling new States in automation
        size_t stage = existState.size();
        for(auto itA = m_automatA.begin(), itB = m_automatB.begin(); itA != m_automatA.end() && itB != m_automatB.end(); ++itA, ++itB) {
            size_t newOrNotNewElem = elemOfStages.size();
            elemOfStages.insert({std::make_pair(*itA, *itB), (unsigned int)stage});
            if(newOrNotNewElem != elemOfStages.size()) {
                m_transitionTo.push_back((unsigned int)stage);
                existState.insert({(unsigned int)stage, std::make_pair(*itA, *itB)});
                que.push((unsigned int)stage);
                stage++;
            } else {
                auto itElemStage = elemOfStages.find(std::make_pair(*itA, *itB));
                m_transitionTo.push_back(itElemStage->second);
            }
        }
        
    }
    
    bool usefulOrNotState (const std::set<State>& usefulState, State transition) {
        for(auto it = usefulState.begin(); it != usefulState.end(); ++it) {
                    if(*it == transition) {
                        return true;
                    }
                }
                return false;
    }
    
    void addTransitionInDFA(DFA& resDFA, State state, const std::set<State>& usefulState) {
        size_t i = 0;
        for(auto itAlp = resDFA.m_Alphabet.begin(); i < m_transitionTo.size(); ++itAlp, ++i) {
            if(usefulOrNotState(usefulState, m_transitionTo[i]) == true) {
               resDFA.m_Transitions.insert({std::make_pair(state, *itAlp), m_transitionTo[i]});
            }
        }
    }
    
    std::vector<std::set<State>> getStateA (void) const { return m_automatA; }
    std::vector<std::set<State>> getStateB (void) const { return m_automatB; }
    std::vector<State> getTransitionTo (void) const { return m_transitionTo;}
    
private:
    std::vector<std::set<State>> m_automatA;
    std::vector<std::set<State>> m_automatB;
    std::vector<State> m_transitionTo;
    std::pair<bool, bool> m_startState = {false, false};
    std::pair<bool, bool> m_endState = {false, false};
    bool m_intersect;
    
    void fillAutomat(const NFA& transition, std::map<State, std::pair <std::set<State>, std::set<State>>>::iterator& itState, Symbol letter, State i, std::vector<std::set<State>>& automat, std::set<State>::iterator& it) {
        auto itTran = transition.m_Transitions.find(std::make_pair(*it, letter));
        if(itTran != transition.m_Transitions.end()) {
            for(auto itAutomat = itTran->second.begin(); itAutomat != itTran->second.end(); ++itAutomat) {
                automat[i].insert(*itAutomat);
            }
        }
    }
    
    void contrEndStart(State curState, State start, const std::set<State>& End, bool& startState, bool& endState) {
        std::set<State> allEndState = End;
        size_t sizeEndState = allEndState.size();
//        if(curState == start && startState == false) {
//            startState = true;
//        }
        allEndState.insert(curState);
        if(allEndState.size() == sizeEndState && endState == false) {
            endState = true;
        }
    }
    
    void prepFillAut(const NFA& NFA, std::vector<std::set<State>>& automat, std::set<State> existState, bool& startState, bool& endState, State i, std::map<State, std::pair <std::set<State>, std::set<State>>>::iterator itState, Symbol letter) {
        automat.push_back(std :: set<State>());
        for(auto it = existState.begin(); it != existState.end(); ++it) {
            contrEndStart(*it, NFA.m_InitialState, NFA.m_FinalStates, startState, endState);
            fillAutomat(NFA, itState, letter, i, automat, it);
        }
    }
    
    void fillTransition(const NFA& a, const NFA& b, DFA& DFA, State state,
                        std::map<State, std::pair <std::set<State>, std::set<State>>>& existState) {
        State i = 0;
        auto itState = existState.find(state);
        for(auto itAlph = DFA.m_Alphabet.begin(); itAlph != DFA.m_Alphabet.end(); ++itAlph) {
            prepFillAut(a, m_automatA, itState->second.first, m_startState.first, m_endState.first, i, itState, *itAlph);
            prepFillAut(b, m_automatB, itState->second.second, m_startState.second, m_endState.second, i, itState, *itAlph);
            i++;
        }
        
//        if(m_startState.first == true && m_startState.second == true) {
//            DFA.m_InitialState = state;
//        }
        if(itState->second.first.size() == 1 && itState->second.second.size() == 1) {
            if(*itState->second.first.begin() == a.m_InitialState && *itState->second.second.begin() == b.m_InitialState) {
                DFA.m_InitialState = state;
            }
        }
        
        if(m_intersect == true && m_endState.first == true && m_endState.second == true) {
            DFA.m_FinalStates.insert(state);
        } else if(m_intersect == false && (m_endState.first == true || m_endState.second == true)) {
            DFA.m_FinalStates.insert(state);
        }
    }
};

void removeUselessStates(DFA& DFA, std::map<State, CTransition>& Tran, std::set<State>& usefulState) {
    std::queue<State> que;
    for(auto itEnd = DFA.m_FinalStates.begin(); itEnd != DFA.m_FinalStates.end(); ++itEnd) {
        usefulState.insert({*itEnd, 0});
        que.push(*itEnd);
    }
    
    while(!que.empty()) {
        State curState = que.front();
        que.pop();
        for(size_t j = 0; j < Tran.size(); j++) {
            auto itTran = Tran.find((unsigned int)j);
            for(size_t t = 0; t < itTran->second.getTransitionTo().size(); t++) {
                if(itTran->second.getTransitionTo()[t] == curState &&
                   itTran->first != itTran->second.getTransitionTo()[t]) {
                    size_t sizeUseState = usefulState.size();
                    usefulState.insert(itTran->first);
                    if(usefulState.size() != sizeUseState) {
                        que.push(itTran->first);
                        break;
                    }
                }
            }
        }
    }
}

//rename States for new DFA automation
void renameStates(DFA& resDFA, std::map<State, CTransition> infoTransitions) {
    std::set<State> usefulState;
    removeUselessStates(resDFA, infoTransitions, usefulState);

    for(auto itState = usefulState.begin(); itState != usefulState.end(); ++itState) {
        resDFA.m_States.insert(*itState);
        auto it = infoTransitions.find(*itState);
        it->second.addTransitionInDFA(resDFA, *itState, usefulState);
    }
    //std::cout << "Stop!" << std::endl;
}

//fill automat all alphabet which will be in result DFA
void fillAlph (const NFA& a, const NFA& b, DFA& resDFA) {
    for(auto it = a.m_Alphabet.begin(); it != a.m_Alphabet.end(); ++it) {
        resDFA.m_Alphabet.insert(*it);
    }
    for(auto it = b.m_Alphabet.begin(); it != b.m_Alphabet.end(); ++it) {
        resDFA.m_Alphabet.insert(*it);
    }
}

//preparing new State for DFA automation
void fillState (const NFA& a, const NFA& b, DFA& resDFA, std::map<State, CTransition>& infoTransitions, State operation) {
    std::map<State, std::pair <std::set<State>, std::set<State>>> existState;
    std::map<std::pair <std::set<State>, std::set<State>>, State> elemOfStages;
    std::queue<State> que;
    que.push(0);
    
    elemOfStages.insert({{{0}, {0}}, 0});
    existState.insert({0, elemOfStages.begin()->first});
    while(!que.empty()) {
        State curState = que.front();
        que.pop();
        
        infoTransitions.insert({curState, CTransition(a, b, resDFA, que, curState, existState, elemOfStages, operation)});
    }
    //std::cout << "Stop!" << std::endl;
}

NFA fullCondition(const NFA& nfa) {
    if(nfa.m_States.size() * nfa.m_Alphabet.size() == nfa.m_Transitions.size()) {
        return nfa;
    }
    
    NFA fullNfa;
    fullNfa.m_InitialState = nfa.m_InitialState;
    for(auto it = nfa.m_FinalStates.begin(); it != nfa.m_FinalStates.end(); ++it) {
        fullNfa.m_FinalStates.insert(*it);
    }
    
    for(auto it = nfa.m_Alphabet.begin(); it != nfa.m_Alphabet.end(); ++it) {
        fullNfa.m_Alphabet.insert(*it);
    }
    
    for(auto it = nfa.m_States.begin(); it != nfa.m_States.end(); ++it) {
        fullNfa.m_States.insert(*it);
    }
    
    std::set<State> newState = {(unsigned int)nfa.m_States.size()};
    fullNfa.m_States.insert((unsigned int)nfa.m_States.size());
 
    for(size_t i = 0; i != fullNfa.m_States.size(); ++i) {
        for(auto it = fullNfa.m_Alphabet.begin(); it != fullNfa.m_Alphabet.end(); ++it) {
            auto itCurState = nfa.m_Transitions.find({i, *it});
            if(itCurState != nfa.m_Transitions.end()) {
                fullNfa.m_Transitions.insert({{i, *it}, itCurState->second});
            } else {
                fullNfa.m_Transitions.insert({{i, *it}, newState});
            }
        }
    }
    
    return fullNfa;
}

std::map<State, State> fillEndAndNotEndState(DFA& dfa) {
    std::map<State, State> splitState;

    for(auto it = dfa.m_States.begin(); it != dfa.m_States.end(); ++it) {
        auto itEnd = dfa.m_FinalStates.find(*it);
        if(itEnd == dfa.m_FinalStates.end()) {
            splitState.insert({*it, 0});
        } else {
            splitState.insert({*it, 1});
        }
    }

    return splitState;
}

bool controlEqualState(std::vector<State> newState, std::vector<std::pair<std::vector<State>, State>> newOrNotState,
                       std::map<State, State>::iterator& itState) {
    State i = 0;
    for(auto it = newOrNotState.begin(); it != newOrNotState.end(); ++it, ++i) {
        if(it->first == newState) {
            if(it->second == itState->second) {
                it->second = i;
                itState->second = it->second;
                return true;
            }
        }
    }
    return false;
}

std::vector<std::pair<std::vector<State>, State>> createNewTable(DFA& dfa, std::map<State, State>& splitState) {
    DFA x;
    
    for(auto it = dfa.m_Transitions.begin(); it != dfa.m_Transitions.end(); ++it) {
        auto itNextState = splitState.find(it->second);
        x.m_Transitions.insert({{it->first}, itNextState->second});
        //it->second = itNextState->second;
    }
    
    std::vector<std::pair<std::vector<State>, State>> newOrNotState;
    State i = 0;
    auto itState = x.m_Transitions.begin();
    for(auto it = splitState.begin(); it != splitState.end(); ++it, ++i) {
        
        std::vector<State> newState;
        for(size_t i = 0; i < dfa.m_Alphabet.size(); ++i) {
            if(it->first == itState->first.first) {
                newState.push_back(itState->second);
                itState++;
            } else {
                newState.push_back(IntMax);
            }
        }

        if(controlEqualState(newState, newOrNotState, it) == false) {
            newOrNotState.push_back({newState, it->second});
            it->second = (unsigned int)newOrNotState.size() - 1;
        }
    }

    return newOrNotState;
}

DFA createResAutomata(DFA& dfa, std::map<State, State>& splitState, std::vector<std::pair<std::vector<State>, State>>& newOrNotState) {
    DFA resDFA;
    
    auto itStart = splitState.find(dfa.m_InitialState);
    resDFA.m_InitialState = itStart->second;
    
    for(auto it = dfa.m_Alphabet.begin(); it != dfa.m_Alphabet.end(); ++it) {
        resDFA.m_Alphabet.insert(*it);
    }
    
    for(size_t i = 0; i < newOrNotState.size(); ++i) {
        resDFA.m_States.insert((unsigned int)i);
        auto itAlph = resDFA.m_Alphabet.begin();
        for(size_t j = 0; j < newOrNotState[i].first.size(); ++j, ++itAlph) {
            if(newOrNotState[i].first[j] != IntMax) {
                resDFA.m_Transitions.insert({{i, *itAlph}, newOrNotState[i].first[j]});
            }
        }
    }
    
    for(auto it = dfa.m_FinalStates.begin(); it != dfa.m_FinalStates.end(); ++it) {
        auto itEndState = splitState.find(*it);
        resDFA.m_FinalStates.insert(itEndState->second);
    }
    
    
    
    return resDFA;
}

DFA minDKA(DFA& dfa) {
    std::map<State, State> splitState = fillEndAndNotEndState(dfa);
    std::map<State, State> tmpSplitState;
    std::vector<std::pair<std::vector<State>, State>> newOrNotState;
    
    while(tmpSplitState != splitState) {
        tmpSplitState = splitState;
       newOrNotState = createNewTable(dfa, splitState);
    }
    return createResAutomata(dfa, splitState, newOrNotState);
}


DFA unify(const NFA& a, const NFA& b) {
    NFA fullA = fullCondition(a);
    NFA fullB = fullCondition(b);
    DFA DFA;
    std::set<State> endState;
    std::map<State, CTransition> infoTransitions;

    fillAlph(fullA, fullB, DFA);
    fillState(fullA, fullB, DFA, infoTransitions, 1);
    renameStates(DFA, infoTransitions);
    //minDKA(resDFA);
    
    return minDKA(DFA);
}

DFA intersect(const NFA& a, const NFA& b) {
    DFA DFA;
    std::set<State> endState;
    std::map<State, CTransition> infoTransitions;
    fillAlph(a, b, DFA);
    fillState(a, b, DFA, infoTransitions, 2);
    renameStates(DFA, infoTransitions);
    if(DFA.m_Transitions.size() == 0) {
        DFA.m_States.insert(DFA.m_InitialState);
    }
    //minDKA(resDFA);
    
    return minDKA(DFA);
}

#ifndef __PROGTEST__

// You may need to update this function or the sample data if your state naming strategy differs.
bool operator==(const DFA& a, const DFA& b)
{
    return std::tie(a.m_States, a.m_Alphabet, a.m_Transitions, a.m_InitialState, a.m_FinalStates) == std::tie(b.m_States, b.m_Alphabet, b.m_Transitions, b.m_InitialState, b.m_FinalStates);
}

int main()
{
    NFA a1{
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
    NFA a2{
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
    DFA a{
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

    NFA b1{
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
    NFA b2{
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
    DFA b{
        {0, 1, 2, 3, 4, 5, 6, 7, 8},
        {'a', 'b'},
        {
            {{0, 'a'}, {1}},
            {{0, 'b'}, {2}},
            {{2, 'a'}, {3}},
            {{2, 'b'}, {4}},
            {{3, 'a'}, {5}},
            {{3, 'b'}, {6}},
            {{4, 'a'}, {7}},
            {{4, 'b'}, {4}},
            {{5, 'a'}, {5}},
            {{5, 'b'}, {4}},
            {{6, 'a'}, {8}},
            {{6, 'b'}, {4}},
            {{7, 'a'}, {5}},
            {{7, 'b'}, {4}},
            {{8, 'a'}, {8}},
            {{8, 'b'}, {8}},
        },
        0,
        {1, 5, 8},
    };
    assert(unify(b1, b2) == b);

    NFA c1{
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
    NFA c2{
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
    DFA c{
        {0},
        {'a', 'b'},
        {},
        0,
        {},
    };
    assert(intersect(c1, c2) == c);

    NFA d1{
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
    NFA d2{
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
    DFA d{
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
