#include "automaton.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <sstream>

using namespace std;

string execute(const char* command) {
    string result;
    char buffer[128];

    // Открываем процесс с помощью popen и читаем вывод
    shared_ptr<FILE> pipe(popen(command, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    
    // Читаем данные из потока
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    return result;
}

void deleteEps(Automaton& automaton) { 
    automaton.exportToPython(); 
     
    string command = "python3 -u removeEps.py";  
    string dfa_output = execute(command.c_str()); 
    istringstream iss(dfa_output); 
    string line; 
    vector<vector<int>> results; 
 
    // Читаем каждую строку 
    while (getline(iss, line)) { 
        istringstream line_stream(line); 
        vector<int> numbers; 
        int number; 
 
        // Читаем числа из строки 
        while (line_stream >> number) { 
            numbers.push_back(number); 
        } 
 
        // Добавляем числа в общий вектор, если строка не пустая 
        if (!numbers.empty()) { 
            results.push_back(numbers); 
        } 
    } 
 
    Automaton automaton2; 
    automaton2.start = results[0][0];  // Первое состояние - старт 
    int numFinalStates = results[1][0]; // Количество финальных состояний 
 
    // Добавляем финальные состояния 
    for (int i = 0; i < numFinalStates; i++) { 
        automaton2.finals.insert(results[i + 2][0]); 
    } 
 
    // Используем unordered_map для хранения состояний 
    std::unordered_map<int, State*> stateMap; 
 
    // Добавляем состояния и переходы 
    for (size_t i = 2 + numFinalStates; i < results.size(); i++) { 
        int fromState = results[i][0]; 
 
        // Проверка на существование состояния 
        if (stateMap.find(fromState) == stateMap.end()) { 
            State state = State(fromState, {}, {}); 
            automaton2.states.emplace_back(state); 
            stateMap[fromState] = &automaton2.states.back(); // Сохраняем указатель на состояние 
        } 
 
        for (size_t j = 1; j < results[i].size(); j += 2) { 
            int symbol = results[i][j]; 
            int toState = results[i][j + 1]; 
 
            // Проверка на существование перехода 
            if (stateMap[fromState]->transitions.find(symbol) == stateMap[fromState]->transitions.end()) { 
                cout << "Adding transition from " << fromState << " to " << toState << " on symbol " << symbol << endl; 
                stateMap[fromState]->transitions[symbol] = toState; // Добавляем переход 
            } 
        } 
    } 
 
    automaton2.alphabet = automaton.alphabet; 
    automaton = automaton2; 
 
    // Формируем вывод 
    for (const auto& state : automaton.states) { 
        cout << state.name << " [ shape = " << (automaton2.finals.count(state.name) ? "doublecircle" : "circle") << " ];\n"; 
        for (const auto& transition : state.transitions) { 
            cout << state.name << " -> " << transition.second << " [ label = " << transition.first << " ];\n"; 
        } 
    } 
}