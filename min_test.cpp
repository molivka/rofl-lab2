#include "min.cpp"
#include "automaton.h"

int main() {

	State s0(0, {}, {{0, 1}, {1, 0}});
    State s1(1, {}, {{0, 0}, {5, 2}});
    State s2(2, {}, {{8, 2}, {1, 2}});

    std::vector<State> states1 = {s0, s1, s2};

    int start1 = 0;
    std::unordered_set<int> finals1 = {2};
    std::vector<int> alphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Automaton automaton1(states1, start1, finals1, alphabet, EOL);

    automaton1.print();
    automaton1 = minimize(automaton1);
    automaton1.print();
    
    State q0(0, {}, {{7, 1}, {8, 4}});
    State q1(1, {}, {{7, 2}, {8, 3}});
    State q2(2, {}, {{7, 2}, {8, 3}});
    State q3(3, {}, {{7, 2}, {8, 3}});
    State q4(4, {}, {{7, 6}, {8, 5}});
    State q5(5, {}, {{7, 6}, {8, 5}});
    State q6(6, {}, {{7, 6}, {8, 5}});
    
    std::vector<State> states2 = {q0, q1, q2, q3, q4, q5, q6};

    int start2 = 0;
    std::unordered_set<int> finals2 = {0, 1, 2, 4, 5};
    
    Automaton automaton2(states2, start2, finals2, alphabet, EOL);
    automaton2.print();
    automaton2 = minimize(automaton2);
    automaton2.print();
}
