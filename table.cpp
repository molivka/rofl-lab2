#include <iostream>
#include <vector>
#include <map> // unordered_map
#include <string>
#include <set>

using namespace std;

#define endl '\n'


map<int, string> S; // основная часть таблицы
map<int, string> E; // столбцы таблицы = суффиксы
map<pair<int, int>, int> table; // таблица принадлежностей 
map<int, int> is_main; // хранит флаг принадлежности к основной части, 0 - доп, 1 - основная

vector<string> alpha = {"0", "1"};

set<string> statuses;
set<string> in;


int check(string w){
    // делаем запрос мату
    return 1;
}

string concat(string a, string b){
    if (a == "e"){
        return b;
    }
    if (b == "e"){
        return a;
    }
    return a + b;
}

void proverka(){
    for (int i = 0; i < S.size(); ++i){
        for (int j = 0; j < E.size(); ++j){
            string new_str = concat(S[i], E[j]);
            // cout << "s: " << S[i] << " E " << E[j] << " new str " << new_str << ' ';
            int f = check(new_str); // проверка принадлежности слова
            table[{i, j}] = f; // записали принадлежит ли слово S[i] + E[j] языку
        }
    }
}

void build(){
    // строим дополнительную часть
    int n = S.size(); // тк в процесса изменяется
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < alpha.size(); ++j){
            if (is_main[i] != 1){
                continue; // если слово не в главной части - скип
            }
            string new_str = concat(S[i], alpha[j]);
            // cout << "s: " << S[i] << " alpha " << alpha[j] << " new str " << new_str << ' ';
            if (in.find(new_str) != in.end()){ // если мы получали уже это слово
                continue;
            }
            // cout << "in " << S.size() << " add " << new_str;
            S[S.size()] = new_str; // получили новое слово путём конкатенации
            is_main[S.size()] = 0; // нужно, тк в мапе не было до этого значений
            in.insert(new_str); // тк сет, то пофиг, но это действительно новое слово
            // cout << endl;
        }
    }
}

int polnota(){
    int is_poln = 1; // полна ли таблица на этой итерации
    set<string> pol; // строки-статусы, которые отражают принадлежность
    for (int i = 0; i < S.size(); ++i){
        string row = ""; // строка со статусами
        for (int j = 0; j < E.size(); ++j){
            row = row + to_string(table[{i, j}]); // накапливаем статусы строки 
        }
        if (is_main[i] == 1){ // если это основная часть, то чекать не нужно
            // cout << "not main: " << i << endl;
            pol.insert(row);
        }  
        else{
            // row = "0"; // test again
            if (pol.find(row) == pol.end()){ // если в доп части есть новая строка - сохраняем
                is_poln = 0; // обновили таблицу => она не была полной
                // cout << "add in main: " << i << endl;
                pol.insert(row);
                is_main[i] = 1; // переносим её в основную
            }
        }
    }
    return is_poln;
}

void print(){
    cout << "pref: " << endl;
    for (int i = 0; i < S.size(); ++i){
        cout << S[i] << ' ';
    }
    cout << endl;
    cout << "suff: " << endl;
    for (int i = 0; i < E.size(); ++i){
        cout << E[i] << ' ';
    }
    cout << endl;
    cout << "table: " << endl;
    for (int i = 0; i < S.size(); ++i){
        for (int j = 0; j < E.size(); ++j){
            cout << table[{i, j}] << ' ';
        }
        cout << endl;
    }
    cout << "words in both parts of table: " << endl;
    for (auto i: in){
        cout << i << ' ';
    }
    cout << endl;
    cout << "words in main part: " << endl;
    for (int i = 0; i < S.size(); ++i){
        cout << "word: " << S[i] << " status: " << is_main[i] << endl;
    }
}

int main(){
    int poln = 0;
    S[0] = "e";
    E[0] = "e"; // e - пустое слово

    in.insert("e");
    is_main[0] = 1; // сразу ставим 1, тк изначально что-то говорим про пустое слово

    // как делаем?
    // строим дополнительную часть
    // проверяем каждое слово
    // проверяем на полноту, то есть нужно ли добавить ещё строки
    // если полнота = 1, то делаем запрос к мату, иначе всё по новой
    while (!poln){
        build(); // достариваем таблицу
        proverka(); // проверяем каждый статус
        poln = polnota(); // проверяем на полноту
        print();
    }
    return 0;
}

