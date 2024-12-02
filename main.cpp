#include "automaton.h"
#include "generateMAT.cpp"
#include "InclusionRequest.cpp"
#include "Visualisation.cpp"
#include "CanonNum.cpp"
#include "removeEpsilon.cpp"
#include "min.cpp"
#include "equal.cpp"
#include "transform.cpp"
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Automaton prepareForChecks(Automaton automaton) {
    deleteEps(automaton);
    automaton.print();
    Automaton minAutomaton = minimize(automaton);
    minAutomaton.print();
    auto canonicalOrder = canonicalNumbering(minAutomaton);
    minAutomaton.print();
    return minAutomaton;
}

void chating(Automaton automaton){
    Automaton MAT_Automaton = prepareForChecks(automaton);
    
    int good_learner = 0;
    ifstream fin; 
    ofstream fout; 
    string line; // считываемая строка
    while (!good_learner){
        fin.open("mat_dialog.txt");
        if (fin.is_open()){
            getline(fin, line);
            if (line == "check automat"){
                vector<string> strings; // считавшиеся строки
                vector<vector<int>> table; // таблица для transform
                vector<string> names; // названия классов
                int n, m; 

                getline(fin, line);
                n = stoi(line); // кол-во строк
                getline(fin, line);
                m = stoi(line); // кол-во столбцов

                while(getline(fin, line, ' ')){
                    strings.push_back(line);
                }   

                int cnt = 0;
                for (int i = 0; i < n; ++i){
                    vector<int> rows;
                    for (int j = 0; j < m; ++j){
                        if (j == 0){
                            names.push_back(strings[cnt]);
                            cnt += 1;
                            continue;
                        }
                        rows.push_back(stoi(strings[cnt]));
                        cnt += 1;
                    }
                    table.push_back(rows);
                }
                auto lerner_automat = transform(table, names);
                Automaton prepared_lerner_automat = prepareForChecks(lerner_automat);
                string is_equal = "FALSE";
                // здесь сравнить два автомата и записать в переменную is_equal
                Answer ans = equal(MAT_Automaton, prepared_lerner_automat);
                if (ans.ok) {
                    good_learner = 1;
                    is_equal = "TRUE";
                }
                fout.open("mat_dialog.txt");
                fout << is_equal;
                fout.close();
            }
            else if (line == "check word"){
                cout << "WORD\n";
                getline(fin, line);
                cout << "int ch word" << endl;
                bool is_accepted = isAccepted(MAT_Automaton, line);
                int answer_to_lerner = 0;
                if (is_accepted){
                    good_learner = 1;
                    answer_to_lerner = 1;
                }
                fout.open("mat_dialog.txt");
                fout << answer_to_lerner;
                fout.close();
            }
        }
        fin.close();
        std::chrono::milliseconds timespan(15000); // чтобы лёрнер успел считать
        std::this_thread::sleep_for(timespan);
    }
}

int main() {
    srand(time(0)); //необходимо для корректной работы рандома

    State q0(0, {}, {{0, 1}, {1, 0}});
    State q1(1,{}, {{0, 0}, {5, 2}});
    State q2(2,{}, {{8, 2}, {1, 2}});

    vector<State> states = {q0, q1, q2};

    int start = 0;
    unordered_set<int> finals = {2};
    vector<int> alphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Automaton automaton(states, start, finals, alphabet,EOL);
    
    //Print Automaton
    //automaton.print();

    // Создаем автомат transitions1 - filled. transitions - empty 
    State a0(0, {{-1, 1}, {-1, 2}}, {}); 
    State a1(1, {{2, 3}}, {}); 
    State a2(2, {{3, 4}}, {}); 
    State a3(3, {{-1, 5}}, {}); 
    State a4(4, {{-1, 5}}, {}); 
    State a5(5, {}, {}); 
 
    states = {a0, a1, a2, a3, a4, a5}; 
    start = 0; 
    finals = {5}; 
    Automaton automaton2(states, start, finals, alphabet, EOL); 
    // Удаляем эпсилон-переходы 
    deleteEps(automaton2); 
    Visualize(automaton2,cout);
    /*
    // Try function isAccepted()
    string str = "1105081";
    cout << "Is " << str << " accepted by automaton?: " << isAccepted(automaton, str)<< "\n";
    
    // Create complex example
    State state0(1,{}, {{1, 2}, {6, 5}});
    State state1(2,{},{{0, 2}, {7, 5}, {8, 0}});
    State state2(5,{},{{0, 5}});
    State state3(0,{},{{7, 3}, {3, 4}});
    State state4(3,{},{});
    State state5(4,{},{});

    vector<State> states2 = {state0, state1, state2,state3,state4,state5};
    int start2 = 1;
    unordered_set<int> finals2 = {3,4,5};
    Automaton automaton3(states2, start2, finals2, alphabet,EOL);

    // Visualize Automaton
    Visualize(automaton3,cout);

    // Canonical Numbering 
    vector<int> canonicalOrder = canonicalNumbering(automaton3);

    // Выводим каноническую нумерацию
    cout << "Canonical Numering: " << std::endl;
    for (size_t i = 0; i < canonicalOrder.size(); ++i) {
        cout << "State " << canonicalOrder[i] << " -> Number " << i << std::endl;
    }
    
    Visualize(automaton3,cout);
    */
    // Генерация автомата

    Automaton result = generateMAT();
    //deleteEps(result);
    result.print();
    //Automaton au1 = minimize(result);
    //au1.print();
    //canonicalOrder = canonicalNumbering(result);
    ofstream file("generatedAutomaton.txt");
    if (file.is_open()) {
        cout << "File Open Access \n";
        Visualize(result,file); // This should work now
        file.close();
    } else {
        cout << "Failed to open the file.\n";
    }

    file.close();

    chating(result);

    return 0;
}
