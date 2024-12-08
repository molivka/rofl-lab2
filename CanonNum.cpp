#include "automaton.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;
// Функция для поиска состояния по имени
unordered_map<int, int> findStateByName(vector<State> states, int name) {
    for (auto& state : states) {
        if (state.name == name) {
            return state.transitions; // Возвращаем указатель на найденное состояние
        }
    }
    std::unordered_map<int, int> result;
    return result;
}

void dfs(const Automaton& automaton, int stateIndex, vector<int>& canonicalOrder, unordered_set<int>& visited) { 
    visited.insert(stateIndex); 
    // Добавляем состояние в порядок обхода
    canonicalOrder.push_back(stateIndex); 

    // Получаем переходы и сортируем их по символам  
    vector<pair<int, int>> transitions;
    unordered_map<int, int> foundTransitions;
    auto it = find_if(automaton.states.begin(), automaton.states.end(),
                           [&stateIndex](const State& state) { return state.name == stateIndex; });

    if (it != automaton.states.end()) {
        foundTransitions = it->transitions;
    } else {
        foundTransitions = {}; 
    }
    for (const auto& transition : foundTransitions) {
        transitions.emplace_back(transition.first, transition.second);
    }
    
    sort(transitions.begin(), transitions.end());
    
    // Рекурсивно обходим все переходы 
    for (const auto& transition : transitions) { 
        char symbol = transition.first; 
        int nextState = transition.second; 
        
        if (visited.find(nextState) == visited.end()) { 
            dfs(automaton, nextState, canonicalOrder, visited); 
        } 
    } 
}

void renameStates(Automaton& automaton, const std::vector<int>& canonicalOrder) {
    unordered_map<int, int> nameToCanonical; // Мапа для перевода исходных имен в канонические номера

    for (size_t i = 0; i < canonicalOrder.size(); ++i) {
        nameToCanonical[canonicalOrder[i]] = i;
    }

    // Переименовываем состояния
    for (auto& state : automaton.states) {
        state.name = nameToCanonical[state.name];

        unordered_map<int, int> newTransitions;
        for (const auto& transition : state.transitions) {
            newTransitions[transition.first] =nameToCanonical[transition.second]; 
        }
        state.transitions = newTransitions; 
    }
    std::unordered_set<int> new_finals;
    for (auto& state : automaton.finals) {
            new_finals.insert(nameToCanonical[state]);
    }
    automaton.start = nameToCanonical[automaton.start];
    automaton.finals = new_finals;
}

vector<int> canonicalNumbering(Automaton& automaton) {
    vector<int> canonicalOrder; 
    unordered_set<int> visited;

    dfs(automaton, automaton.start, canonicalOrder, visited);
    renameStates(automaton, canonicalOrder);
    return canonicalOrder;
}