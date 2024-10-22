#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Класс для представления состояния автомата
class State {
public:
    int name;  // Имя состояния
    std::unordered_map<int, int> transitions;  // Переходы: символ -> следующее состояние

    State(const int& name, const std::unordered_map<int, int>& transitions)
        : name(name), transitions(transitions) {}

    void print() const {
        std::cout << "State " << name << " transitions:\n";
        for (const auto& transition : transitions) {
            std::cout << "  " << name << " -- " << transition.first << " --> " << transition.second << "\n";
        }
    }
};

// Класс для представления автомата
class Automaton {
public:
    std::vector<State> states;  // Список состояний (объекты State)
    int start;  // Начальное состояние
    std::unordered_set<int> finals;  // Финальные состояния
    std::vector<int> alphabet;  // Алфавит автомата

    Automaton(const std::vector<State>& states, const int& start, 
              const std::unordered_set<int>& finals, const std::vector<int>& alphabet)
        : states(states), start(start), finals(finals), alphabet(alphabet) {}

    void print() const {
        std::cout << "start state: " << start << "\n";
        std::cout << "Final states: ";
        for (const auto& fin : finals) {
            std::cout << fin << " ";
        }
        std::cout << "\nStates and transitions:\n";
        for (const auto& state : states) {
            state.print();
        }
    }
};

#endif
