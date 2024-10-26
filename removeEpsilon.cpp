#include "automaton.h"
#include <iostream> 
using namespace std;
void removeEpsilonTransitions(Automaton& automaton) { 
    unordered_map<int, multimap<int, int>> newTransitions; 
    for (const auto& state : automaton.states) { 
        newTransitions[state.name] = {};
    } 
 
    // Рекурсивная функция для обработки эпсилон-переходов 
    function<void(int)> processEpsilon = [&](int current) { 
        auto range = automaton.states[current].transitions1.equal_range(-1); 
        
        for (auto it = range.first; it != range.second; ++it) { 
            int epsilonTarget = it->second; 
            for (const auto& t : automaton.states[epsilonTarget].transitions1) { 
                if (t.first != -1) {  
                    newTransitions[current].emplace(t.first, t.second);  
                } 
            } 
            processEpsilon(epsilonTarget); 
            // Добавляем финальные состояния
            if (automaton.finals.count(epsilonTarget)) {
                automaton.finals.insert(current); // Добавляем в finals, если current еще не там
            }
        } 
    }; 
 
    // Обработка всех состояний 
    for (const auto& state : automaton.states) {
        processEpsilon(state.name); 
    } 
    unordered_set<int> accessibleStates;
    // Обновление переходов в автомате 
    for (auto& state : automaton.states) {
        state.transitions1.clear(); 
        if (!newTransitions[state.name].empty()) {
            accessibleStates.insert(state.name);
            for (const auto& transition : newTransitions[state.name]) {
                state.transitions.insert(transition); 
                accessibleStates.insert(transition.second); 
            } 
        }
    }
    for (auto it = automaton.states.begin(); it != automaton.states.end();) {
        if (accessibleStates.find(it->name) == accessibleStates.end()) {
            it = automaton.states.erase(it);
        } else {
            ++it;
        }
    }
} 