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
class CTransition
{
public:
    CTransition(const NFA& a, const NFA& b, DFA& DFA, std::queue<State> & que, State state,
                 std::map<State, std::pair <std::set<State>, std::set<State>>>& existState,
                 std::map<std::pair <std::set<State>, std::set<State>>, State>& elemOfStages, State op, std::set<State>& endState) {
        if(op == 2) {
            m_intersect = true;
        } else {
            m_intersect = false;
        }
        
        fillTransition(a, b, DFA, state, existState, endState);
        
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
    
    bool usefulOrNotState (const std::map<State, State>& usefulState, State transition) {
        for(auto it = usefulState.begin(); it != usefulState.end(); ++it) {
            if(it->first == transition) {
                return true;
            }
        }
        return false;
    }
    
    void addTransitionInDFA(DFA& resDFA, std::map<State, State>::iterator state, const std::map<State, State>& usefulState) {
        size_t i = 0;
        for(auto itAlp = resDFA.m_Alphabet.begin(); i < m_transitionTo.size(); ++itAlp, ++i) {
            if(usefulOrNotState(usefulState, m_transitionTo[i]) == true) {
                auto newNameState = usefulState.find(m_transitionTo[i]);
                resDFA.m_Transitions.insert({std::make_pair(state->second, *itAlp), newNameState->second});
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
        if(curState == start && startState == false) {
            startState = true;
        }
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
                        std::map<State, std::pair <std::set<State>, std::set<State>>>& existState, std::set<State>& endState) {
        State i = 0;
        auto itState = existState.find(state);
        for(auto itAlph = DFA.m_Alphabet.begin(); itAlph != DFA.m_Alphabet.end(); ++itAlph) {
            prepFillAut(a, m_automatA, itState->second.first, m_startState.first, m_endState.first, i, itState, *itAlph);
            prepFillAut(b, m_automatB, itState->second.second, m_startState.second, m_endState.second, i, itState, *itAlph);
            i++;
        }
        
        if(m_startState.first == true && m_startState.second == true) {
            DFA.m_InitialState = state;
        }
        
        if(m_intersect == true && m_endState.first == true && m_endState.second == true) {
            endState.insert(state);
        } else if(m_intersect == false && (m_endState.first == true || m_endState.second == true)) {
            endState.insert(state);
        }
    }
};

void removeUselessStates(DFA& DFA, std::map<State, CTransition>& Tran, std::map<State, State>& usefulState, std::set<State> endState) {
    std::queue<State> que;
    for(auto itEnd = endState.begin(); itEnd != endState.end(); ++itEnd) {
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
                    usefulState.insert({itTran->first, 0});
                    if(usefulState.size() != sizeUseState) {
                        que.push(itTran->first);
                        break;
                    }
                }
            }
        }
    }
    
    State i = 0;
    auto itEndState = endState.begin();
    for(auto it = usefulState.begin(); it != usefulState.end(); ++it, ++i) {
        it->second = i;
        //change name InitialState
        if(it->first == DFA.m_InitialState) {
            DFA.m_InitialState = it->second;
        }
        //change name FinalState
        if(*itEndState == it->first) {
            DFA.m_FinalStates.insert(it->second);
            if(itEndState != endState.end()) {
                itEndState++;
            }
        }
    }
    
}

//rename States for new DFA automation
void renameStates(DFA& resDFA, std::map<State, CTransition> infoTransitions, std::set<State>& endState) {
    std::map<State, State> usefulState;
    removeUselessStates(resDFA, infoTransitions, usefulState, endState);

    for(auto itState = usefulState.begin(); itState != usefulState.end(); ++itState) {
        resDFA.m_States.insert(itState->second);
        auto it = infoTransitions.find(itState->first);
        it->second.addTransitionInDFA(resDFA, itState, usefulState);
    }
    //std::cout << "Stop!" << std::endl;
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
void fillState (const NFA& a, const NFA& b, DFA& resDFA, std::map<State, CTransition>& infoTransitions, State operation, std::set<State>& endState) {
    std::map<State, std::pair <std::set<State>, std::set<State>>> existState;
    std::map<std::pair <std::set<State>, std::set<State>>, State> elemOfStages;
    std::queue<State> que;
    que.push(0);
    
    elemOfStages.insert({{{0}, {0}}, 0});
    existState.insert({0, elemOfStages.begin()->first});
    while(!que.empty()) {
        State curState = que.front();
        que.pop();
        
        infoTransitions.insert({curState, CTransition(a, b, resDFA, que, curState, existState, elemOfStages, operation, endState)});
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

//void fillEndAndNotEndState(DFA& dfa, std::set<State>& notEndState, std::set<State>& endState) {
//    auto itEnd = dfa.m_FinalStates.begin();
//    for(auto itState = dfa.m_States.begin(); itState != dfa.m_States.end(); ++itState) {
//        if(*itEnd == *itState) {
//            endState.insert(*itEnd);
//            if(itEnd != dfa.m_FinalStates.end()) {
//                itEnd++;
//            }
//        } else {
//            notEndState.insert(*itState);
//        }
//    }
//}

std::map<State, State> fillEndAndNotEndState(DFA& dfa) {
    std::map<State, State> splitState;
    
    auto itEnd = dfa.m_FinalStates.begin();
    for(auto itState = dfa.m_States.begin(); itState != dfa.m_States.end(); ++itState) {
        if(*itEnd == *itState) {
            splitState.insert({*itEnd, 1});
            if(itEnd != dfa.m_FinalStates.end()) {
                itEnd++;
            }
        } else {
            splitState.insert({*itState, 0});
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
                return true;
            }
        }
    }
    
    return false;
}

void createNewTable(DFA& dfa, std::map<State, State>& splitState) {
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
        //newOrNotState.push_back(std::set<State>());
        std::vector<State> newState;
        while(it->first == itState->first.first) {
            newState.push_back(itState->second);
            itState++;
        }
        
        if(newOrNotState.size() < it->second + 1) {
            newOrNotState.push_back({newState, it->second});
            it->second = (unsigned int)newOrNotState.size() - 1;
        } else {
            //if(newState != newOrNotState[it->second]) {
            if(controlEqualState(newState, newOrNotState, it) == false) {
                newOrNotState.push_back({newState, it->second});
                it->second = (unsigned int)newOrNotState.size() - 1;
            }
        }
        
    }
    

}

void minDKA(DFA& dfa) {
    //DFA newDKA;
    
    //std::set<State> notEndState;
    //std::set<State> endState;
    std::map<State, State> splitState = fillEndAndNotEndState(dfa);
    //fillEndAndNotEndState(dfa, notEndState, endState);
    std::map<State, State> tmpSplitState;
    
    while(tmpSplitState != splitState) {
        tmpSplitState = splitState;
        createNewTable(dfa, splitState);
    }
    
}


DFA unify(const NFA& a, const NFA& b) {
    NFA fullA = fullCondition(a);
    NFA fullB = fullCondition(b);
    DFA resDFA;
    std::set<State> endState;
    std::map<State, CTransition> infoTransitions;

    fillAlph(fullA, fullB, resDFA);
    fillState(fullA, fullB, resDFA, infoTransitions, 1, endState);
    renameStates(resDFA, infoTransitions, endState);
    minDKA(resDFA);
    
    return resDFA;
}

DFA intersect(const NFA& a, const NFA& b) {
    DFA resDFA;
    std::set<State> endState;
    std::map<State, CTransition> infoTransitions;
    fillAlph(a, b, resDFA);
    fillState(a, b, resDFA, infoTransitions, 2, endState);
    renameStates(resDFA, infoTransitions, endState);
    //minDKA(resDFA);
    
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
