#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "automaton.h"
using namespace std;
void Visualize(Automaton& automaton) {
    cout << "digraph {" << '\n';
    // Указываем начальное состояни
    cout << "\trankdir = LR\n";
    cout << "\tstart [ shape = point ];" << '\n';
    cout << "\tstart -> " << automaton.start << ";" << '\n';
    // Узлы и переходы
    for (const auto& state : automaton.states) {
        string shape = automaton.finals.count(state.name) ? "doublecircle" : "circle";
        cout << "\t" << state.name << " [ shape = " << shape << " ];" << '\n';

        // Генерируем переходы
        for (const auto& transition : state.transitions) {
            cout << "\t" << state.name << " -> " << transition.second << " [ label = " << transition.first << " ];" << std::endl;
        }
    }
    cout << "}" << std::endl;
}
// https://www.devtoolsdaily.com/graphviz/ - визуализация в dot