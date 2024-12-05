#include <stdio.h>
#include "HTTPRequest.hpp"
#include <stdlib.h>
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

string MAT_equivalence(map<int, string> S, map<int, string> E, map<pair<int, int>, int> table, int hand_case, map<int, int> is_main, int sec_wait=20){
    string answer;

    if (hand_case == 3){
        string main_prefixes, non_main_prefixes, suffixes, table_mat;
        for (int i = 0; i < S.size(); ++i){
            if (is_main[i]){
                main_prefixes = main_prefixes + S[i];
                main_prefixes = main_prefixes + " ";
            }
            else{
                non_main_prefixes = non_main_prefixes + S[i];
                non_main_prefixes = non_main_prefixes + " ";
            }
        }
        if (main_prefixes[main_prefixes.size() - 1] == ' '){
            main_prefixes.pop_back();
        }
        if (non_main_prefixes[non_main_prefixes.size() - 1] == ' '){
            non_main_prefixes.pop_back();
        }

        for (int i = 0; i < E.size(); ++i){
            suffixes = suffixes + E[i];
            suffixes = suffixes + " ";
        }
        if (suffixes[suffixes.size() - 1] == ' '){
            suffixes.pop_back();
        }

        for (int i = 0; i < S.size(); ++i){
            for (int j = 0; j < E.size(); ++j){
                if (!is_main[i]){
                    continue;
                }
                table_mat = table_mat + to_string(table[{i, j}]);
                table_mat = table_mat + " ";
            }
        }

        for (int i = 0; i < S.size(); ++i){
            for (int j = 0; j < E.size(); ++j){
                if (is_main[i]){
                    continue;
                }
                table_mat = table_mat + to_string(table[{i, j}]);
                table_mat = table_mat + " ";
            }
        }
        if (table_mat[table_mat.size() - 1] == ' '){
            table_mat.pop_back();
        }

        cout << "main_pref " << main_prefixes << endl;
        cout << "non_main_pref " << non_main_prefixes << endl;
        cout << "suff " << suffixes << endl;
        cout << "table " << table_mat << endl;

        try{
            http::Request request{"http://localhost:8098/checkTable"};
            const string body = "{\"main_prefixes\": \"" + main_prefixes + "\", \"non_main_prefixes\": \"" + non_main_prefixes + "\", \"suffixes\": \"" + suffixes + "\", \"table\": \"" + table_mat + "\"}";
            cout << body << endl;
            const auto response = request.send("POST", body, {
                {"Content-Type", "application/json"}
            });
            //response: Возвращает "true", если таблица соответсвует автомату или контрпример в противном случае.
            string ok = string{response.body.begin() + 12, response.body.end() - 1};
            answer = "";
            for (int i = 0; i < ok.size(); ++i){
                if (ok[i] == ','){
                    break;
                } else if (ok[i] == '"'){
                    continue;
                }
                answer = answer + ok[i];
            }
        }
        catch (const std::exception& e){
            cerr << "Request failed, error: " << e.what() << '\n';
        }
    }
    else{
        push_matrix_to_file(S, E, table, hand_case);
        if (!hand_case){
            chrono::milliseconds timespan(sec_wait * 1000);
            this_thread::sleep_for(timespan);
        }
        answer = pull_from_file(hand_case);
    }

    return answer;
}

int MAT_check(string w, int hand_case, int sec_wait=20){
    string answer;
    if (hand_case == 3){
        try{
            http::Request request{"http://localhost:8098/checkWord"};
            const string body = "{\"word\": \"" + w + "\"}";
            cout << body << endl;
            const auto response = request.send("POST", body, {
                {"Content-Type", "application/json"}
            });
            string ok = string{response.body.begin() + 13, response.body.end() - 1};
            // cout << "CHECK " << ok << endl;
            answer = "";
            for (int i = 0; i < ok.size(); ++i){
                if (ok[i] == '"'){
                    break;;
                }
                answer = answer + ok[i];
            }
            // cout << "OK " << answer << endl;
            // std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; 
        }
        catch (const std::exception& e){
            cerr << "Request failed, error: " << e.what() << '\n';
        }
    }
    else{
        push_word_to_file(w, hand_case);
        if (!hand_case){
            std::chrono::milliseconds timespan(sec_wait * 1000);
            std::this_thread::sleep_for(timespan);
        }
        answer = pull_from_file(hand_case);
    }
    if (answer == "0"){
        return 0;
    }

    return 1;
}
