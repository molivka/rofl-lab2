#include <iostream>
#include <vector>
#include <map>
#include <string>

// Класс для представления состояния автомата
class State {
public:
    int name;  // Имя состояния
    std::map<int, int> transitions;  // Переходы: символ -> следующее состояние

    State(const int& name, const std::map<int, int>& transitions)
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
    std::vector<int> finals;  // Финальные состояния
    std::vector<int> alphabet;  // Алфавит автомата

    Automaton(const std::vector<State>& states, const int& start, 
              const std::vector<int>& finals, const std::vector<int>& alphabet)
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

int main() {
    State q0(0, {{0, 1}, {1, 0}});
    State q1(1, {{0, 0}, {5, 2}});
    State q2(2, {{8, 2}, {1, 2}});

    std::vector<State> states = {q0, q1, q2};

    int start = 0;
    std::vector<int> finals = {2};
    std::vector<int> alphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Automaton automaton(states, start, finals, alphabet);

    automaton.print();

    return 0;
}
