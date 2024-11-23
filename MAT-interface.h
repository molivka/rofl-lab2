#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

void push_matrix_to_file(map<int, string> S, map<int, string> E, map<pair<int, int>, int> table){
    // ofstream out; 
    // out.open("mat_dialog.txt");

    // if (out.is_open()){
    //     out << S.size() << endl;
    //     out << E.size() << endl;
    //     for (int i = 0; i < S.size(); ++i){
    //         for (int j = 0; j < E.size(); ++j){
    //             cout << table[{i, j}] << ' ';
    //         }
    //         cout << endl;
    //     }
    // }
    // out.close();
    cout << "check dka" << endl;
    cout << S.size() << ' ' << 1 << endl;
    for (int i = 0; i < S.size(); ++i){
        cout << S[i] << ' ' << table[{i, 0}] << endl;
    }
}

void push_word_to_file(string s){
    // ofstream out; 
    // out.open("mat_dialog.txt");

    // if (out.is_open()){
    //     out << s << endl;
    // }
    // out.close();
    cout << "check word" << endl;
    cout << s << endl;
}

string pull_from_file(){
    // ifstream in;
    // string line;
    // vector<string> answer;
    // in.open("mat_dialog.txt");
    // if (in.is_open()){
    //     while (getline(in, line)){
    //         answer.push_back(line);
    //     }
    // }
    // in.close();
    string line;
    cin >> line;
    return line;
}

string MAT_equivalence(map<int, string> S, map<int, string> E, map<pair<int, int>, int> table){
    push_matrix_to_file(S, E, table);
    // std::chrono::milliseconds timespan(11176576);
    // std::this_thread::sleep_for(timespan);
    string answer = pull_from_file();

    return answer;
}

int MAT_check(string w){
    push_word_to_file(w);
    // заглушка 
    // std::chrono::milliseconds timespan(11176576);
    // std::this_thread::sleep_for(timespan);

    string answer = pull_from_file();
    if (answer == "0"){
        return 0;
    }

    return 1;
}
