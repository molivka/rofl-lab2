#include "automaton.h"
#include "example.cpp"
struct Answer
{
    bool ok;
    std::string example;
};

Answer equal(Automaton& automaton1, Automaton& automaton2) {
	Answer ans = {false, ""};
    //проверка на равенство алфавитов
    if (automaton1.alphabet != automaton2.alphabet) {
        ans.example = getExample(automaton1, automaton2);
        return ans;
    }

    //проверка на равенство количества состояний
    if (automaton1.states.size() != automaton2.states.size()) {
        ans.example = getExample(automaton1, automaton2);
        return ans;
    }

    //проверка на равенство конечных состояний
    if (automaton1.finals != automaton2.finals) {
        ans.example = getExample(automaton1, automaton2);
        return ans;
    }
    
    //проверка на равенство переходов
    for (int i = 0; i < automaton1.states.size(); ++i) {
        for (const auto& [symbol, toState1] : automaton1.states[i].transitions) {
            if (automaton2.states[i].transitions.find(symbol) == automaton2.states[i].transitions.end()) {
                ans.example = getExample(automaton1, automaton2);
                return ans; //переход отсутствует во втором автомате
            }
            //проверяем, что переход ведет в то же состояние
            if (automaton2.states[i].transitions[symbol] != toState1) {
                ans.example = getExample(automaton1, automaton2);
                return ans; //переход ведет в другое состояние
            }
        }
    }
	ans.ok = true;
    return ans;
}
