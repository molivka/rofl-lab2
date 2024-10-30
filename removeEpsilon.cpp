#include "automaton.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <functional>
using namespace std;

// Функция для вычисления эпсилон-замыкания
unordered_set<int> epsilonClosures(int state, const vector<State>& states) {
    unordered_set<int> closure;
    queue<int> q;
    q.push(state);
    closure.insert(state);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto range = states[current].transitions1.equal_range(-1);
        for (auto it = range.first; it != range.second; ++it) {
            int nextState = it->second;
            if (closure.find(nextState) == closure.end()) {
                closure.insert(nextState);
                q.push(nextState);
            }
        }
    }
    return closure;
}

// Функция для детерминизации автомата
Automaton determinize(const Automaton& nfa) {
    vector<State> states2;
    int start2;
    unordered_set<int> finals2;
    vector<int> alphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Automaton dfa(states2, start2, finals2, alphabet,EOL);
    // 1. Initialize the queue with the epsilon closure of the NFA's start state
    queue<unordered_set<int>> queue;
    unordered_set<int> startStateSet = epsilonClosures(nfa.start, nfa.states);
    queue.push(startStateSet);

    // 2. Track already processed states using a vector
    vector<unordered_set<int>> processedStates; 
    processedStates.push_back(startStateSet); // Start with the initial state

    // 3. Add the initial DFA state
    dfa.states.push_back(State(0, {}, {})); // Add the initial DFA state
    dfa.start = 0;
    // 4. Process states from the queue 
    while (!queue.empty()) {
        unordered_set<int> currentStateSet = queue.front();
        queue.pop();

        int currentStateId = find(processedStates.begin(), processedStates.end(), currentStateSet) - processedStates.begin(); 

        // 5. For each symbol in the alphabet:
        for (int symbol : dfa.alphabet) {
            // 6. Calculate the set of reachable states
            unordered_set<int> nextStateSet;
            for (int state : currentStateSet) {
                auto range = nfa.states[state].transitions1.equal_range(symbol);
                for (auto it = range.first; it != range.second; ++it) {
                    nextStateSet.insert(epsilonClosures(it->second, nfa.states).begin(),
                                       epsilonClosures(it->second, nfa.states).end());
                }
            }

            // 7. If the next state set is not empty:
            if (!nextStateSet.empty()) {
                // 8. Check if the next state set is already processed
                auto it = find(processedStates.begin(), processedStates.end(), nextStateSet);
                if (it == processedStates.end()) { // New state 
                    int nextStateId = dfa.states.size();
                    processedStates.push_back(nextStateSet);
                    dfa.states.push_back(State(nextStateId, {}, {}));
                    queue.push(nextStateSet);

                    // 9. Add a transition from the current state to the next state
                    dfa.states[currentStateId].transitions1.insert({symbol, nextStateId}); 
                } else {
                    // 10. If the next state set is already processed, add a transition
                    dfa.states[currentStateId].transitions1.insert({symbol, distance(processedStates.begin(), it)});
                }
            }
        }

        // 11. Mark the state as final if any of its constituent states are final in NFA
        for (int state : currentStateSet) {
            if (nfa.finals.find(state) != nfa.finals.end()) {
                dfa.finals.insert(currentStateId);
                break;
            }
        }
    }
    for (auto& state : dfa.states) {
        for (const auto& [symbol, nextState] : state.transitions1) {
            state.transitions[symbol] = nextState;
        }
    }
    return dfa;
    
}
// Функция для удаления эпсилон-переходов
void removeEpsilonTransitions(Automaton& automaton) {
    // 1. Создаем новый список состояний
    std::vector<State> newStates;
    newStates.reserve(automaton.states.size());

    // 2. Проходим по каждому состоянию исходного автомата
    for (const auto& state : automaton.states) {
        State newState(state.name, {}, {});  // Create a new state with empty transitions

        // 3. Для каждого символа (включая эпсилон) в transitions1:
        for (auto& [symbol, nextState] : state.transitions1) {
            // Если символ - эпсилон (-1), находим эпсилон-замыкание
            if (symbol == -1) {
                unordered_set<int> epsilonClosure = epsilonClosures(nextState, automaton.states);

                // 4. Перебираем состояния в эпсилон-замыкании
                for (int closureState : epsilonClosure) {
                    // 5. Для каждого состояния в эпсилон-замыкании:
                    //    - Проверяем transitions1 этого состояния
                    //    - Добавляем переходы в transitions1 нового состояния,
                    //      исключая эпсилон-переходы
                    for (const auto& [symbol2, nextState2] : automaton.states[closureState].transitions1) {
                        if (symbol2 != -1) {
                            newState.transitions1.insert({symbol2, nextState2});
                        }
                    }
                }
            } else {
                // 6. Если символ - не эпсилон, просто добавляем переход
                // Use unordered_map to ensure only one transition per symbol
                newState.transitions1.insert({symbol, nextState}); 
            }
        }

        // 7. Добавляем новое состояние в список
        newStates.push_back(newState);
    }

    // 8. Обновляем список состояний автомата
    automaton.states = newStates;

    // 9. Обновляем начальное состояние:
    //    - Находим эпсилон-замыкание начального состояния
    //    - Устанавливаем новое начальное состояние как первое состояние в эпсилон-замыкании
    std::unordered_set<int> epsilonClosure = epsilonClosures(automaton.start, automaton.states);
    automaton.start = *epsilonClosure.begin();

    // 10. Обновляем финальные состояния:
    //    - Проверяем, входят ли исходные финальные состояния в эпсилон-замыкание
    //    - Если да, добавляем эти состояния в список финальных
    std::unordered_set<int> newFinals;
    for (int finalState : automaton.finals) {
        unordered_set<int> epsilonClosure = epsilonClosures(finalState, automaton.states);
        newFinals.insert(epsilonClosure.begin(), epsilonClosure.end());
    }
    automaton.finals = newFinals;
}