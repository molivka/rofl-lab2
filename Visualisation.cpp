#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "automaton.h"
#include <iostream>
#include <fstream>
using namespace std;
void Visualize(Automaton& automaton,ostream& out) {
    out<<"digraph {" << '\n';
    // Указываем начальное состояни
    out << "\trankdir = LR\n";
    out << "\tstart [ shape = point ];" << '\n';
    out << "\tstart -> " << automaton.start << ";" << '\n';
    // Узлы и переходы
    for (const auto& state : automaton.states) {
        string shape = automaton.finals.count(state.name) ? "doublecircle" : "circle";
        out << "\t" << state.name << " [ shape = " << shape << " ];" << '\n';

        // Генерируем переходы
        for (const auto& transition : state.transitions) {
            out << "\t" << state.name << " -> " << transition.second << " [ label = " << transition.first << " ];" << std::endl;
        }
    }
    out << "}" << std::endl;
}
// https://www.devtoolsdaily.com/graphviz/ - визуализация в dot