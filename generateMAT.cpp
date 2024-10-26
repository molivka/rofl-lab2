#include "automaton.h"

std::vector<Automaton> automatons;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Проверка наличия путей в финальные вершины и хотя бы одного пути из начальной вершины
bool isValid(const Automaton& automaton) {
    std::unordered_set<int> visited;
    std::stack<int> toVisit;
    
    toVisit.push(automaton.start);
    visited.insert(automaton.start);
    
    // Проводим обход автомата в глубину, чтобы отметить все достижимые состояния
    while (!toVisit.empty()) {
        int currentState = toVisit.top();
        toVisit.pop();
        
        // Обходим все возможные переходы из текущего состояния
        const auto& transitions1 = automaton.states[currentState].transitions1;
        for (const auto& transition : transitions1) {
            int nextState = transition.second;
            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                toVisit.push(nextState);
            }
        }
    }
    
    // Проверяем, что все финальные состояния достижимы
    for (const int final : automaton.finals) {
        if (visited.find(final) == visited.end()) {
            return false;
        }
    }
    
    return true;
}

// Объединение автоматов
Automaton unionAutomaton(const Automaton& A1, const Automaton& A2) {
    std::vector<State> new_states = A1.states; // Копируем состояния первого автомата
    int offset = A1.states.size(); // Смещение для состояний второго автомата

    // Переименовываем состояния второго автомата и добавляем их в новый вектор
    for (const auto& state : A2.states) {
        std::multimap<int, int> new_transitions1;
        for (const auto& transition : state.transitions1) {
            new_transitions1.insert({transition.first, transition.second + offset});
        }
        new_states.push_back(State(state.name + offset, new_transitions1, {}));
    }

    // Создаем новое начальное состояние, которое переходит в начальные состояния обоих автоматов
    int new_start = new_states.size();
    std::unordered_map<int, int> emptyTransitions;
    new_states.emplace_back(new_start, std::multimap<int, int>{
        {-1, A1.start}, 
        {-1, A2.start + offset} // epsilon переход к началу A2
    }, emptyTransitions);

    for (State i : new_states) {
        i.print();
    }
    
    // Объединяем финальные состояния
    std::unordered_set<int> new_finals = A1.finals; // Копируем финальные состояния первого автомата
    for (int final_state : A2.finals) {
        new_finals.insert(final_state + offset); // Переименовываем финальные состояния второго автомата
    }

    return Automaton(new_states, new_start, new_finals, A1.alphabet, A1.type);
}

// Функция генерации автомата для конкретной лексемы
Automaton generateLexeme(LexemeType type, const std::vector<int>& alphabet) {
    Automaton automaton;
    do {
        std::vector<State> states;
        int numStates = getRandomNumber(1, 15);  // Ограничиваем число состояний

        for (int i = 0; i < numStates; ++i) {
            std::multimap<int, int> transitions1;
            std::set<int> usedSymbols; // Множество для отслеживания использованных символов

            int numtransitions1 = getRandomNumber(1, alphabet.size());

            for (int j = 0; j < numtransitions1; ++j) {
                int symbol = alphabet[getRandomNumber(0, alphabet.size() - 1)];

                if (usedSymbols.find(symbol) == usedSymbols.end()) {
                    int nextState = getRandomNumber(0, numStates - 1);
                    transitions1.insert({symbol, nextState});
                    usedSymbols.insert(symbol); // Добавляем символ в множество использованных
                } else {
                    j--;
                }
            }

            std::unordered_map<int, int> emptyTransitions;
            states.emplace_back(i, transitions1, emptyTransitions);
        }

        int startState = getRandomNumber(0, numStates - 1);
        std::unordered_set<int> finalStates;

        int numFinalStates = getRandomNumber(1, numStates);
        for (int i = 0; i < numFinalStates; ++i) {
            finalStates.insert(getRandomNumber(0, numStates - 1));
        }

        automaton = Automaton(states, startState, finalStates, alphabet, type);
    } while (!isValid(automaton));

    return automaton;
}

// Функция для конкатенации двух автоматов
Automaton concatenate(const Automaton& A1, const Automaton& A2) {
    // Переименовываем состояния второго автомата, чтобы не было конфликтов
    int state_offset = A1.states.size();  // Смещение для состояний второго автомата
    std::vector<State> new_states = A1.states;

    // Переименовываем состояния второго автомата
    for (const auto& state : A2.states) {
        std::multimap<int, int> new_transitions1;
        for (const auto& transition : state.transitions1) {
            new_transitions1.insert({transition.first, transition.second + state_offset});
        }
        new_states.push_back(State(state.name + state_offset, new_transitions1, {}));
    }

    // Создаем переходы из финальных состояний первого автомата в начальное состояние второго автомата
    for (int final_state : A1.finals) {
        new_states[final_state].transitions1.insert({-1, A2.start + state_offset});
    }

    // Финальные состояния нового автомата — это финальные состояния второго автомата с учетом смещения
    std::unordered_set<int> new_finals;
    for (int final_state : A2.finals) {
        new_finals.insert(final_state + state_offset);
    }

    // Возвращаем новый автомат
    return Automaton(new_states, A1.start, new_finals, A1.alphabet, A1.type);
}

bool hasIntersection(const Automaton& automaton1, const Automaton& automaton2) {
    std::queue<std::pair<int, int>> toVisit;
    std::unordered_set<std::pair<int, int>, pair_hash> visited;

    toVisit.push({automaton1.start, automaton2.start});
    visited.insert({automaton1.start, automaton2.start});

    // BFS
    while (!toVisit.empty()) {
        std::pair<int, int> current = toVisit.front();
        toVisit.pop();

        int state1 = current.first;
        int state2 = current.second;

        // Проверка, что оба состояния финальные
        if (automaton1.finals.find(state1) != automaton1.finals.end() &&
            automaton2.finals.find(state2) != automaton2.finals.end()) {
            return true;
        }

        // Все возможные переходы для каждого символа алфавита
        for (int symbol : automaton1.alphabet) {
            if (automaton1.states[state1].transitions1.count(symbol) &&
                automaton2.states[state2].transitions1.count(symbol)) {

                auto range1 = automaton1.states[state1].transitions1.equal_range(symbol);
                auto range2 = automaton2.states[state2].transitions1.equal_range(symbol);

                // Получение всех возможных переходов для current state1 и state2
                for (auto it1 = range1.first; it1 != range1.second; ++it1) {
                    int nextState1 = it1->second; // Получаем значение для состояния automaton1
                    
                    for (auto it2 = range2.first; it2 != range2.second; ++it2) {
                        int nextState2 = it2->second; // Получаем значение для состояния automaton2

                        std::pair<int, int> nextPair = {nextState1, nextState2};
                        if (visited.find(nextPair) == visited.end()) {
                            toVisit.push(nextPair);
                            visited.insert(nextPair);
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Функция проверки на бесконечный цикл с использованием DFS
bool hasInfiniteLoop(const Automaton& automaton) {
    std::unordered_set<int> visited;         // Множество посещенных состояний
    std::unordered_set<int> recursionStack;  // Стек рекурсии для текущих состояний

    // Вспомогательная функция DFS
    std::function<bool(int)> dfs = [&](int stateId) {
        // Если состояние уже в стеке рекурсии, значит мы нашли цикл
        if (recursionStack.count(stateId) > 0) {
            return true;
        }
        
        // Если состояние уже посещено, возвращаем false (избегаем повторного обхода)
        if (visited.count(stateId) > 0) {
            return false;
        }

        // Добавляем текущее состояние в посещенные и в стек рекурсии
        visited.insert(stateId);
        recursionStack.insert(stateId);

        // Обходим все переходы из текущего состояния
        auto it = automaton.states[stateId].transitions1.begin();
        while (it != automaton.states[stateId].transitions1.end()) {
            int nextState = it->second;
            if (dfs(nextState)) {
                return true;
            }
            ++it;
        }

        // Удаляем текущее состояние из стека рекурсии
        recursionStack.erase(stateId);
        return false;
    };

    // Запускаем DFS с начального состояния
    return dfs(automaton.start);
}

std::vector<Automaton> generateLexemes() {
    std::vector<int> Alphabet = {2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> eolAlphabet = {0, 1};
    
    Automaton atomAutomaton = generateLexeme(ATOM, Alphabet);
    while (!hasInfiniteLoop(atomAutomaton)) {
        atomAutomaton = generateLexeme(ATOM, Alphabet);
    }

    Automaton lbrAutomaton;
    Automaton rbrAutomaton;

    // Генерация автоматов для левых и правых скобок
    bool validBrackets = false;
    while (!validBrackets) {
        lbrAutomaton = generateLexeme(LBR, Alphabet);
        rbrAutomaton = generateLexeme(RBR, Alphabet);

        // Проверка на пересечения между скобочными автоматами и атомами
        bool lbrIntersectsAtom = hasIntersection(lbrAutomaton, atomAutomaton);
        bool rbrIntersectsAtom = hasIntersection(rbrAutomaton, atomAutomaton);
        bool bracketsIntersect = hasIntersection(lbrAutomaton, rbrAutomaton);

        // Проверка на пересечения при конкатенации
        bool concatenationValid = true;

        if (!bracketsIntersect) {
            // Проверяем конкатенацию левой скобки и атома
            if (concatenationValid) {
                Automaton concatLBRAtom = concatenate(lbrAutomaton, atomAutomaton);
                if (hasIntersection(concatLBRAtom, lbrAutomaton) || hasIntersection(concatLBRAtom, rbrAutomaton)) {
                    concatenationValid = false;
                }
            }

            // Проверяем конкатенацию правой скобки и атома
            if (concatenationValid) {
                Automaton concatRBRAtom = concatenate(atomAutomaton, rbrAutomaton);
                if (hasIntersection(concatRBRAtom, lbrAutomaton) || hasIntersection(concatRBRAtom, rbrAutomaton)) {
                    concatenationValid = false;
                }
            }

            // Пытаемся конкатенировать левые и правые скобки и проверяем пересечение
            if (concatenationValid) {
                Automaton concatenatedLBR = concatenate(lbrAutomaton, rbrAutomaton);
                if (hasIntersection(concatenatedLBR, lbrAutomaton) || hasIntersection(concatenatedLBR, rbrAutomaton)) {
                    concatenationValid = false;
                }
            }
        } else {
            concatenationValid = false;
        }

        // Условие валидности: ни одно из пересечений не должно происходить
        validBrackets = !lbrIntersectsAtom && !rbrIntersectsAtom && !bracketsIntersect && concatenationValid;
    }

    Automaton dotAutomaton = generateLexeme(DOT, Alphabet);
    while (hasIntersection(dotAutomaton, atomAutomaton)) {
        dotAutomaton = generateLexeme(DOT, Alphabet);
    }

    Automaton eolAutomaton = generateLexeme(EOL, eolAlphabet);

    return {eolAutomaton, atomAutomaton, lbrAutomaton, rbrAutomaton, dotAutomaton};
}


int maxDepth = 4; // Максимальная глубина вложенности скобок
Automaton genExpr(int depth);
Automaton genEolStarExprEolStar(int depth);

// Функция для построения автомата выражения с eol по бокам: [eol]*[expression][eol]*
Automaton genEolStarExprEolStar(int depth) {
    Automaton expr = genExpr(depth);
    Automaton eolStar = automatons[EOL].repeat();
    return concatenate(concatenate(eolStar, expr), eolStar);
}

// Функция для построения автомата списка: [list] ::= [lbr] [expression]+ [rbr]
Automaton genList(int depth) {
    Automaton lbr = automatons[LBR];
    Automaton exprPlus = genEolStarExprEolStar(depth + 1).repeat(1);
    Automaton rbr = automatons[RBR];
    return concatenate(concatenate(lbr, exprPlus), rbr);
}

// Функция для построения автомата выражения: [expr] ::= [atom] | [lbr][expression][dot][expression][rbr] | [list]
Automaton genExpr(int depth) {
    if (depth >= maxDepth) {
        return automatons[ATOM].clone();
    }

    std::vector<Automaton> lexemList;
    lexemList.push_back(automatons[ATOM].clone());

    // Создаем автомат для [lbr][expression][dot][expression][rbr]
    Automaton complexExprAutomaton = concatenate(concatenate(concatenate(concatenate(automatons[LBR].clone(),
    genEolStarExprEolStar(depth + 1)), 
    automatons[DOT].clone()), genEolStarExprEolStar(depth + 1)), 
    automatons[RBR].clone());
    lexemList.push_back(complexExprAutomaton);

    lexemList.push_back(genList(depth + 1));

    Automaton result = lexemList[0];
    for (size_t i = 1; i < lexemList.size(); ++i) {
        result = unionAutomaton(result, lexemList[i]);
    }
    return result;
}

// Функция для построения автомата для программы
Automaton genProgramm() {
    // Создаем автомат для [eol]*
    Automaton eolStar = automatons[EOL].repeat();
    
    // Создаем автомат для ([expression][eol]*)+
    Automaton expressionAutomaton = genEolStarExprEolStar(0);
    Automaton expressionEolStar = concatenate(expressionAutomaton, automatons[EOL].repeat());
    Automaton expressionEolPlus = expressionEolStar.repeat(1);

    return concatenate(eolStar, expressionEolPlus);
}

Automaton generateMAT() {
    automatons = generateLexemes();
    Automaton result = genProgramm();

    return result;
}
