#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void push_to_file(){
    ofstream out; 
    out.open("mat_dialog.txt");
    if (out.is_open()){
        out << "some text"; // изменить под нужный формат
    }
    out.close();
}

string pull_from_file(){
    ifstream in;
    string line;
    vector<string> answer;
    in.open("mat_dialog.txt");
    if (in.is_open()){
        while (getline(in, line)){
            answer.push_back(line);
        }
    }
    in.close();
    return line;
}

string MAT_equivalence_test(vector<string> main_prefixes, vector<string> non_main_prefixes, vector<string> suffixes, vector<int> table_for_mat){
    // will be smth
}

int MAT_check(string w){
    // will be smth
}