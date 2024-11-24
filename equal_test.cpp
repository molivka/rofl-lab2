#include "automaton.h"
#include "equal.cpp"

int main() {
	State s00(0, {}, {{0, 1}});
    State s01(1, {}, {{0, 0}, {5, 2}});
    State s02(2, {}, {});

    std::vector<State> states1 = {s00, s01, s02};

    int start1 = 0;
    std::unordered_set<int> finals1 = {2};
    std::vector<int> alphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Automaton automaton1(states1, start1, finals1, alphabet, EOL);
    
    State s10(0, {}, {{0, 1}});
    State s11(1, {}, {{0, 0}, {5, 2}});
    State s12(2, {}, {{5, 3}});
    State s13(3, {}, {});

    std::vector<State> states2 = {s10, s11, s12, s13};

    int start2 = 0;
    std::unordered_set<int> finals2 = {3};

    Automaton automaton2(states2, start2, finals2, alphabet, EOL);
    
    Answer ans = equal(automaton1, automaton2);
    std::cout << ans.ok << " must be false\n" << ans.example <<  " must be string with one (5) in middle";
    return 0;
}