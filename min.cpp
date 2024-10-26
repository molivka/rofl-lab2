#include "automaton.h"

// функция для проверки финальное ли состояние 
bool areStateFinal(int s, const Automaton& automaton) {
    return (automaton.finals.count(s) > 0);
}

// Функция для проверки по следующему правилу: Пометим все множества { qi, qj} такие, что существует символ а (qi ->(a) q1 & qj ->(a) q2, причем {q1, q2} - уже помеченная пара)
bool markTransitions(int s1, int s2, int symbol, const Automaton& automaton, std::vector<std::vector<bool>> &table) {
    auto it1 = automaton.states[s1].transitions.find(symbol);
    auto it2 = automaton.states[s2].transitions.find(symbol);

    if (it1 == automaton.states[s1].transitions.end() && it2 == automaton.states[s2].transitions.end()) {
        // Одно из состояний не имеет перехода по символу
        return false;
    }
    int state1 = it1->second;
    int state2 = it2->second;
    
    bool ok = table[state1][state2]; //проверка, помечено ли уже
    return ok;
}

Automaton minimize(const Automaton& automaton) {
    int n = automaton.states.size();
    std::vector<std::vector<bool>> table(n, std::vector<bool>(n, false));
	
//помечаем все пары, где одно из состояний финальное
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (areStateFinal(i, automaton) != areStateFinal(j, automaton)) {
                table[i][j] = true;
                table[j][i] = true;
            }
        }
    }
//помечаем остальные пары
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (!table[i][j]) {
                    for (int symbol : automaton.alphabet) {
                        if (markTransitions(i, j, symbol, automaton, table)) {
                            table[i][j] = true;
                            table[j][i] = true;
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }
    } while (changed);

//объединяем эквивалентные состояния
    std::vector<std::unordered_set<int>> partitions;
    std::vector<int> state_to_mainState(n, -1);
//проходим по строке состояния и собираем в группу эквивалентные ему 
    for (int i = 0; i < n; ++i) {
        if (state_to_mainState[i] == -1) {
        	int mainState = i; //назначаем состояние, в которое перейдут все эквивалентные
            std::unordered_set<int> current_partition;
            for (int j = i; j < n; ++j) {
                if (!table[i][j]) {
                    current_partition.insert(j);
                    state_to_mainState[j] = mainState;
                }
            }
            partitions.push_back(current_partition); //отправляем группу эквивалентных состояний в список групп
        }
    }
	std::cout << partitions.size();
    std::vector<State> new_states;
    
    for (const auto& partition : partitions) {
        std::unordered_map<int, int> new_transitions; //переходы для нового состояния

        for (const int& state : partition) {
            for (const auto& transition : automaton.states[state].transitions) {
                int symbol = transition.first;
                int target = transition.second;

                int new_target = state_to_mainState[target]; //найдем, в какое теперь состояние будет переход
                new_transitions[symbol] = new_target;
            }
        }
        int state_name = state_to_mainState[*partition.begin()];
        new_states.emplace_back(state_name, new_transitions);
    }

// начальное состояние нового автомата
    int new_start = state_to_mainState[automaton.start];
    
// финальные состояния нового автомата
    std::unordered_set<int> new_finals;
    for (const auto& partition : partitions) {
        for (const int& state : partition) {
            if (automaton.finals.count(state) > 0) {
                new_finals.insert(state_to_mainState[state]);
                break;
            }
        }
    }
    
    return Automaton(new_states, new_start, new_finals, automaton.alphabet);
}
