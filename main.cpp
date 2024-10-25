#include "automaton.h"
#include "generateMAT.cpp"
#include "InclusionRequest.cpp"
#include "Visualisation.cpp"
#include "CanonNum.cpp"
int main() {
    std::srand(std::time(0)); //необходимо для корректной работы рандома
    
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
    
    // Create complex example
    State state0(1, {{1, 2}, {6, 5}});
    State state1(2, {{0, 2}, {7, 5}, {8, 0}});
    State state2(5, {{0, 5}});
    State state3(0, {{7, 3}, {3, 4}});
    State state4(3, {});
    State state5(4, {});

    std::vector<State> states2 = {state0, state1, state2,state3,state4,state5};
    int start2 = 1;
    std::unordered_set<int> finals2 = {3,4,5};
    Automaton automaton2(states2, start2, finals2, alphabet);

    // Visualize Automaton
    Visualize(automaton2);

    // Canonical Numbering 
    std::vector<int> canonicalOrder = canonicalNumbering(automaton2);

    // Выводим каноническую нумерацию
    std::cout << "Canonical Numering: " << std::endl;
    for (size_t i = 0; i < canonicalOrder.size(); ++i) {
        std::cout << "State " << canonicalOrder[i] << " -> Number " << i << std::endl;
    }
    
    Visualize(automaton2);

    Automaton result = generateMAT();
    result.print();
    Visualize(result);
    
    return 0;
}
