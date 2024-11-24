#include "automaton.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

bool isAccepted(Automaton& automate, std::string& expression) {
    
    int currentState = automate.start;
    for (char symbol : expression) {
        int symbolInt = symbol - '0';
        auto it = automate.states[currentState].transitions.find(symbolInt);
        if (it != automate.states[currentState].transitions.end()) {
            currentState = it->second;
        } else {
            return false;  
        }
    }
    if (automate.finals.find(currentState) != automate.finals.end()) {
        return true;
    } 
    return false;
};
