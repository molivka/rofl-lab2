from FAdo.fa import NFA, DFA,Epsilon
nfa = NFA()
nfa.addInitial(0)
nfa.addFinal(5)
nfa.addState(0)
nfa.addTransition(0,Epsilon , 1)
nfa.addTransition(0,Epsilon , 2)
nfa.addState(1)
nfa.addTransition(1, 2, 3)
nfa.addState(2)
nfa.addTransition(2, 3, 4)
nfa.addState(3)
nfa.addTransition(3,Epsilon , 5)
nfa.addState(4)
nfa.addTransition(4,Epsilon , 5)
nfa.addState(5)
dfa = nfa.elimEpsilon()
trim = nfa.trim()
dfa = trim.toDFA()
print(dfa.Initial)
print(len(dfa.Final))
for x in dfa.Final:
    print(x)

transitions = nfa.transitions()
states = nfa.States
symbols = set()
for transition in transitions:
    symbols.add(transition[1])
    state_from = transition[0]
    symbol = transition[1]
    state_to = transition[2]
    print(state_from, symbol, state_to)
