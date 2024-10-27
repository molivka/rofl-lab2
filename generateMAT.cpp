#include "automaton.h"

std::vector<Automaton> automatons;
std::mt19937 generator(std::random_device{}());

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

int getRandomNumber(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
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

Automaton unionAutomaton(const Automaton& automaton1, const Automaton& automaton2) {
    Automaton result = automaton1.clone();
    Automaton second_clone = automaton2.clone();

    // Смещаем состояния второго автомата
    int offset = result.states.size();
    for (auto& state : second_clone.states) {
        state.name += offset;

        std::multimap<int, int> updated_transitions1;
        for (const auto& transition : state.transitions1) {
            updated_transitions1.insert(std::make_pair(transition.first, transition.second + offset));
        }
        state.transitions1 = updated_transitions1;
    }

    int new_start = result.states.size() + second_clone.states.size();
    State start_state(new_start, {}, {});
    
    // Добавляем эпсилон-переходы от нового начального состояния к начальным состояниям обоих автоматов
    start_state.transitions1.insert(std::make_pair(-1, result.start));
    start_state.transitions1.insert(std::make_pair(-1, second_clone.start + offset));

    // Обновляем начальное состояние и добавляем новое состояние к результату
    result.start = new_start;
    result.states.push_back(start_state);

    // Добавляем состояния второго автомата к результату
    result.states.insert(result.states.end(), second_clone.states.begin(), second_clone.states.end());

    // Обновляем финальные состояния
    for (int final_state : second_clone.finals) {
        result.finals.insert(final_state + offset);
    }
    result.finals.insert(automaton1.finals.begin(), automaton1.finals.end());

    std::unordered_set<int> unique_alphabet(result.alphabet.begin(), result.alphabet.end());
    unique_alphabet.insert(second_clone.alphabet.begin(), second_clone.alphabet.end());
    result.alphabet.assign(unique_alphabet.begin(), unique_alphabet.end());

    return result;
}

Automaton concatenate(const Automaton& automaton1, const Automaton& automaton2) {
    Automaton result = automaton1.clone();
    Automaton second_clone = automaton2.clone();

    int offset = result.states.size();
    for (auto& state : second_clone.states) {
        state.name += offset;

        // Обновляем transitions1 с учетом нового offset
        std::multimap<int, int> updated_transitions1;
        for (auto transition = state.transitions1.begin(); transition != state.transitions1.end(); ++transition) {
            updated_transitions1.insert(std::make_pair(transition->first, transition->second + offset));
        }
        state.transitions1 = updated_transitions1;
    }

    // Подключаем финальные состояния первого автомата к начальному состоянию второго
    for (int final_state : result.finals) {
        result.states[final_state].transitions1.insert(std::make_pair(-1, second_clone.start + offset));
    }

    result.states.insert(result.states.end(), second_clone.states.begin(), second_clone.states.end());
    result.finals.clear();
    for (int final_state : second_clone.finals) {
        result.finals.insert(final_state + offset);
    }

    std::unordered_set<int> unique_alphabet(result.alphabet.begin(), result.alphabet.end());
    unique_alphabet.insert(second_clone.alphabet.begin(), second_clone.alphabet.end());
    result.alphabet.assign(unique_alphabet.begin(), unique_alphabet.end());

    return result;
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

    std::function<bool(int)> dfs = [&](int stateId) {
        if (recursionStack.count(stateId) > 0) {
            return true;
        }
        
        if (visited.count(stateId) > 0) {
            return false;
        }

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

        recursionStack.erase(stateId);
        return false;
    };

    // Запускаем DFS с начального состояния
    return dfs(automaton.start);
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

std::vector<Automaton> generateLexemes() {
    std::vector<int> commonAlphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> eolAlphabet;
    std::vector<int> Alphabet;

    std::shuffle(commonAlphabet.begin(), commonAlphabet.end(), generator);
    std::uniform_int_distribution<int> dist(2, 3);
    int eolSize = dist(generator);

    eolAlphabet.assign(commonAlphabet.begin(), commonAlphabet.begin() + eolSize);
    Alphabet.assign(commonAlphabet.begin() + eolSize, commonAlphabet.end());
    
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
