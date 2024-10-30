#include <iostream>
#include <vector>
#include <map> // unordered_map
#include <string>
#include <set>

using namespace std;

#define endl '\n'

int n; // кол-во строк в основной таблице
int n_dop; // кол-вл строк в доп таблице
int m; // кол-о столбцов

map<int, string> S; // основная часть таблицы
map<int, string> S_dop; // дополнительная часть таблицы
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

void proverka(){//заменить на итератор
    for (int i = 0; i < S.size(); ++i){
        for (int j = 0; j < E.size(); ++j){
            string new_str = concat(S[i], E[j]);
            in.insert(new_str);
            int f = check(new_str); // проверка принадлежности слова
            table[{i, j}] = f; // записали принадлежит ли слово S[i] + E[j] языку
        }
    }
}

void build(){
    // строим дополнительную часть
    n = S.size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < alpha.size(); ++j){
            if (is_main[i] != 1){
                continue; // если строка не в главной части - скип
            }
            string new_str = concat(S[i], alpha[j]);
            if (in.find(new_str) != in.end()){ // если мы получали уже это слово
                continue;
            }
            // а с индексами точно всё норм?
            S[n + 3 * i + j] = new_str; // получили новое слово путём конкатенации
            is_main[n + 3 * i + j] = 0; // нужно, тк в мапе не было до этого значений
            in.insert(new_str);
        }
    }
}

int polnota(){
    int is_poln = 1; // полна ли таблица на этой итерации
    set<string> pol;
    for (int i = 0; i < n; ++i){
        string row = "";
        for (int j = 0; j < n; ++j){
            row = row + to_string(table[{i, j}]); // накапливаем статусы строки 
        }
        if (is_main[i] == 1){ // если это осоновная часть, то просто сохраняем принадлежности слова
            pol.insert(row);
        }  
        else{
            if (pol.find(row) == pol.end()){ // то есть в доп части есть новая строка
                is_poln = 0; // обновили таблицу => она не была полной
                pol.insert(row);
                is_main[i] = 1; // переносим её в основную
            }
        }
    }
    return is_poln;
}

void print(){
    cout << "prefixs " << endl;
    for (int i = 0; i < S.size(); ++i){
        cout << S[i] << ' ';
    }
    cout << endl;
    cout << "suffs " << endl;
    for (int i = 0; i < E.size(); ++i){
        cout << E[i] << ' ';
    }
    cout << endl;
    cout << "table " << endl;
    for (int i = 0; i < S.size(); ++i){
        for (int j = 0; j < E.size(); ++j){
            cout << table[{i, j}] << ' ';
        }
        cout << endl;
    }
    cout << "words in table " << endl;
    for (auto i: in){
        cout << i << ' ';
    }
    cout << endl;
    cout << "is_main for strings " << endl;
    for (int i = 0; i < S.size(); ++i){
        cout << is_main[i] << ' ';
    }
    cout << endl;
}

int main(){
    S[0] = "e";
    E[0] = "e"; // e - пустое слово
    n = 1; 
    m = 1;
    in.insert("e");
    is_main[0] = 1; // мб сразу 1?
    build(); // строим доп часть
    proverka(); // записываем статусы
    is_main[1] = 1;// тестовая штука, потом убрать
    int is_poln = polnota(); // полна ли таблица
    print();
    // cout << "is_poln? " << is_poln << endl;

    build();
    proverka();
    is_poln = polnota();
    print();
    // cout << "is_poln? " << is_poln << endl;
    
    build();
    proverka();
    is_poln = polnota();

    return 0;
}

