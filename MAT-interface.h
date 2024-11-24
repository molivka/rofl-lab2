#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

void push_matrix_to_file(map<int, string> S, map<int, string> E, map<pair<int, int>, int> table, int hand_case){
    if (hand_case){
        cout << "check dka" << endl;
        cout << S.size() << ' ' << 1 << endl;
        for (int i = 0; i < S.size(); ++i){
            cout << S[i] << ' ' << table[{i, 0}] << endl;
        }
    }
    else{
        ofstream fout; 
        fout.open("mat_dialog.txt");
        if (fout.is_open()){
            fout << "check automat\n";
            fout << S.size() << endl;
            fout << E.size() << endl;
            for (int i = 0; i < S.size(); ++i){
                for (int j = 0; j < E.size(); ++j){
                    fout << table[{i, j}] << ' ';
                }
            }
        }
        fout.close();
    }
}

void push_word_to_file(string s, int hand_case){
    if (hand_case){
        cout << "check word" << endl;
        cout << s << endl;
    }
    else{
        ofstream fout; 
        fout.open("mat_dialog.txt");

        if (fout.is_open()){
            fout << "check word" << endl;
            fout << s << endl;
        }
        fout.close();
    }
}

string pull_from_file(int hand_case){
    string answer;
    if (hand_case){
        cin >> answer;
    }
    else{
        ifstream fin;
        string line;
        fin.open("mat_dialog.txt");
        if (fin.is_open()){
            while (getline(fin, line)){
                answer = line;
            }
        }
        fin.close();
    }
    return answer;
}

string MAT_equivalence(map<int, string> S, map<int, string> E, map<pair<int, int>, int> table, int hand_case, int sec_wait=20){
    push_matrix_to_file(S, E, table, hand_case);
    if (!hand_case){
        std::chrono::milliseconds timespan(sec_wait * 1000);
        std::this_thread::sleep_for(timespan);
    }
    string answer = pull_from_file(hand_case);

    return answer;
}

int MAT_check(string w, int hand_case, int sec_wait=20){
    push_word_to_file(w, hand_case);
    if (!hand_case){
        std::chrono::milliseconds timespan(sec_wait * 1000);
        std::this_thread::sleep_for(timespan);
    }

    string answer = pull_from_file(hand_case);
    if (answer == "0"){
        return 0;
    }

    return 1;
}
