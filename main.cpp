#include "automaton.h"
#include "InclusionRequest.cpp"
int main() {
    State q0(0, {{0, 1}, {1, 0}});
    State q1(1, {{0, 0}, {5, 2}});
    State q2(2, {{8, 2}, {1, 2}});

    std::vector<State> states = {q0, q1, q2};

    int start = 0;
    std::unordered_set<int> finals = {2};
    std::vector<int> alphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Automaton automaton(states, start, finals, alphabet);
    
    //Print Automaton
    automaton.print();

    // Try function isAccepted()
    std::string str = "1105081";
    cout << "Is " << str << " accepted by automaton?: " << isAccepted(automaton,str)<< "\n";

    return 0;
}
