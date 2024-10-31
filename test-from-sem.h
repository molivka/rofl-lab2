#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <regex>

using namespace std;

#define endl '\n'

vector<string> test = {"a", "b"};


int MAT_check_test(string w){
    int cnt_a = 0;
    int cnt_b = 0;
    for (char x: w){
        if (x == 'a'){
            cnt_a += 1;
        }
        if (x == 'b'){
            cnt_b += 1;
        }
    }
    if ((cnt_a % 2 == 0) && (cnt_b == 1)){
        return 1;
    }
    return 0;
}

string MAT_equivalence_test(vector<string> v){
    vector<string> correct = {"e", "a", "b", "ba", "bb"};
    sort(correct.begin(), correct.end());
    sort(v.begin(), v.end());
    string ok = "ok";
    for (int i = 0; i < v.size(); ++i){
        if (v[i] != correct[i]){
            return "aba";
        }
    }
    return ok;
}