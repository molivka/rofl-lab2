#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <queue>
#include <utility>
#include <functional>
#include <memory>

enum LexemeType { EOL, ATOM, LBR, RBR, DOT };

// Класс для представления состояния автомата
class State {
public:
    int name;  // Имя состояния
    std::multimap<int, int> transitions1;  // Переходы: символ -> следующее состояние (с учетом эпсилон)
    std::unordered_map<int, int> transitions;

    State(const int& name, const std::multimap<int, int>& transitions1, const std::unordered_map<int, int>& transitions)
        : name(name), transitions1(transitions1), transitions(transitions) {}

    void print() const {
        std::cout << "State " << name << " transitions:\n";
        
        if (transitions.empty()) {
            for (const auto& transition : transitions1) {
                std::cout << "  " << name << " -- \"" << transition.first << "\" --> " << transition.second << "\n";
            }
        } else {
            for (const auto& transition : transitions) {
                std::cout << "  " << name << " -- \"" << transition.first << "\" --> " << transition.second << "\n";
            }
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
    LexemeType type;  // Тип лексемы

    Automaton(const std::vector<State>& states, const int& start, 
              const std::unordered_set<int>& finals, const std::vector<int>& alphabet, LexemeType type)
        : states(states), start(start), finals(finals), alphabet(alphabet), type(type) {}

    Automaton() {
    }

    // Метод для клонирования автомата
    Automaton clone() const {
        return Automaton(states, start, finals, alphabet, type);
    }

    // Метод для повторения автомата
    Automaton repeat(int minRepeats = 0) const {
        Automaton repeated_automaton = clone();

        for (int final_state : finals) {
            repeated_automaton.states[final_state].transitions1.insert({-1, start});
        }

        if (minRepeats == 0) {
            int new_start = repeated_automaton.states.size();
            repeated_automaton.states.push_back(State(new_start, {{-1, start}}, {}));
            return Automaton(repeated_automaton.states, new_start, finals, alphabet, type);
        }

        return repeated_automaton;
    }

    void print() const {
        std::cout << "Lexeme type: " << type << "\n";
        std::cout << "Start state: " << start << "\n";
        std::cout << "Final states: ";
        for (const auto& fin : finals) {
            std::cout << fin << " ";
        }
        std::cout << "\nStates and transitions1:\n";
        for (const auto& state : states) {
            state.print();
        }
    }
};

#endif
