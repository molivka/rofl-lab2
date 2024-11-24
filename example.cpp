#include "automaton.h"
//функция создания переходов в ловушку
void devilStates( Automaton& automaton) {
    for (auto &state : automaton.states) {
        for (auto sym : automaton.alphabet) {
            if (state.transitions.find(sym) == state.transitions.end()) {
                state.transitions[sym] = -1;
            }
        }
    }
    std::multimap<int, int> transitions1;
    std::unordered_map<int, int> transitions;
    automaton.states.emplace_back(-1, transitions1, transitions); //создаем ловушку
}
//функция дополнения автомата
//меняем все финальные состояния на нефинальные
Automaton complementAutomaton(const Automaton& automaton) { 
    std::unordered_set<int> new_finals;
    for (int i = 0; i < automaton.states.size(); ++i) {
        if (automaton.finals.find(automaton.states[i].name) == automaton.finals.end()) {
            new_finals.insert(automaton.states[i].name);
        }
    }
    return Automaton(automaton.states, automaton.start, new_finals, automaton.alphabet, automaton.type);
}

//определяем хэш-функцию для пар, чтобы можно было их использовать в качестве ключа в map
namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };
}

//функция пересечения автомата
//действуем по следующему алгоритму: 
//1 - декартово умножение множества состояний 1 и 2 автомата
//2 - каждая пара будет задавать новое состояние
//3 - создаем переходы для каждого нового состояния по следующему принципу: 
//δ(⟨q1,q2⟩,c)=⟨δ1(q1,c),δ2(q2,c)⟩
//4 - финальные состояния - все те состояния, в которых оба состояния из соответствующей им пары были финальными в своем автомате
//5 - стартовое состояние - состояние, созданное парой стартовых состояний
Automaton intersect(const Automaton& a1, const Automaton& a2) {

    std::vector<State> intersectedStates;
    std::unordered_map<std::pair<int, int>, int> stateMapping;
    std::unordered_set<int> finalStates;
    int nextStateIndex = 0;

	for (size_t i = 0; i < a1.states.size(); ++i) {
        for (size_t j = 0; j < a2.states.size(); ++j) {
        	int newStateIndex = nextStateIndex++;
            stateMapping[{a1.states[i].name, a2.states[j].name}] = newStateIndex;
        }
    }
    
    for (size_t i = 0; i < a1.states.size(); ++i) {
        for (size_t j = 0; j < a2.states.size(); ++j) {
            std::unordered_map<int, int> newTransitions;
            for (int symbol : a1.alphabet) {
                auto it1 = a1.states[i].transitions.find(symbol);
                auto it2 = a2.states[j].transitions.find(symbol);
                if (it1 != a1.states[i].transitions.end() && it2 != a2.states[j].transitions.end()) {
                    newTransitions[symbol] = stateMapping[{it1->second, it2->second}];
                }
            }
            
			std::multimap<int, int> transitions1;
            intersectedStates.emplace_back(stateMapping[{a1.states[i].name, a2.states[j].name}], transitions1, newTransitions);

            if (a1.finals.count(a1.states[i].name) && a2.finals.count(a2.states[j].name)) {
                finalStates.insert(stateMapping[{a1.states[i].name, a2.states[j].name}]);
            }
        }
    }

    return Automaton(intersectedStates, stateMapping[{a1.start, a2.start}], finalStates, a1.alphabet, a1.type);
}

//генерация случайной строки в автомате с помощью обхода в ширину
std::string generateAcceptedString(const Automaton& a) {
		std::unordered_map<int, State> nameToState;
		for (auto state : a.states) {
			nameToState.emplace(state.name, state); 
		}
		
        std::queue<std::pair<int, std::string>> q;
        q.push({a.start, ""});

        std::unordered_set<int> visited;
		
        while (!q.empty()) {
            int currentStateName = q.front().first;
            
            State currentState = {-1, {}, {}};
            auto it = nameToState.find(currentStateName);
            if (it != nameToState.end()) {
            	currentState = it->second;
            }
            
            std::string currentString = q.front().second;
            q.pop();

            if (visited.count(currentStateName)) continue;
            visited.insert(currentStateName);

            if (a.finals.count(currentStateName)) {
                return currentString;
            }
            
            for (const auto& transition : currentState.transitions) {
                q.push({transition.second, currentString + std::to_string(transition.first)});
            }
        }

        return "";
    }
//соберем теперь все вместе
//автомат1 - пример, автомат2 - тот кто хочет быть как пример
//генерируется пример строки, которая обрабатывается автоматом1, но не обрабатывается автоматом2
std::string getExample(Automaton& a1, Automaton& a2) {
    devilStates(a2); //создаем переходы в ловушку
    Automaton a3 = complementAutomaton(a2); //дополнение автомата
    Automaton a4 = intersect(a1, a3); //пересечение автоматов
    std::string example = generateAcceptedString(a4); //генерация примера
    return example;
}
