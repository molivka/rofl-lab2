#include <iostream>
#include <vector>
#include <map> // unordered_map
#include <string>
#include <set>

using namespace std;

#define endl '\n'


map<int, string> S; // строки таблицы = классы эквивалентности
map<int, string> E; // столбцы таблицы = различающие суффиксы 
map<pair<int, int>, int> table; // таблица входимости
map<int, int> is_main; // хранит флаг принадлежности к основной части, 1 - основная часть, 0 - доп часть

vector<string> alpha = {"0", "1"}; // алфавит языка

set<string> in; // набор всех слов-классов
int poln = 0; // является ли таблица полной
int neprot = 0; // является ли таблица непротиворечивой

// вывод основных сущностей
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

// запрос к мату на принадлежность
int check(string w){
    return 1;
}

// запрос к мату на эквивалентность
string equivalence(){
    string status = "ok";
    status = "help";  // снова тест, но help это прям мне нужна!!!
    vector<string> to_mat; // классы эквивалентности, которые отправляем мату 
    for (auto i: S){
        string word = i.second;
        to_mat.push_back(word);
    }
    // cout << "we are push it to mat!!!" << endl;
    // for (string i: to_mat){
    //     cout << i << endl;
    // }
    return status;
}

// учитываем пустую строчку при конкатенации
string concat(string a, string b){
    if (a == "e"){
        return b;
    }
    if (b == "e"){
        return a;
    }
    return a + b;
}

// добавляем слово и его суффиксы в качестве столбцов
void add_to_suf(string w){
    string w_rev = ""; //чтобы не было O(n^2)
    for (int i = w.size() - 1; i >= 0; --i){
        w_rev = concat(to_string(w[i]), w_rev);
        E[E.size()] = w_rev;
    }
}

// строка со статусами принадлежности
string get_status(int ind){
    string row = "";
    for (int j = 0; j < E.size(); ++j){
        row = row + to_string(table[{ind, j}]); 
    }
    return row;
}

// заполнение таблицы принадлежности
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

// строим дополнительную часть
void build(){
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

// проверка таблицы на полноту
int polnota(){
    int is_poln = 1; // полна ли таблица на этой итерации
    set<string> pol; // строки-статусы, которые отражают принадлежность
    for (int i = 0; i < S.size(); ++i){
        string row = get_status(i);
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

// проверка на непротиворечивость
int neprotivor(){
    int is_neprot = 1;
    for (int i = 0; i < S.size(); ++i){
        if (!is_main[i]){
            continue; // cкипаем слово, если оно не в основной части
        }
        for (int j = i + 1; j < S.size(); ++j){
            if (!is_main[j]){
                continue; // cкипаем слово, если оно не в основной части
            }
            string status_1 = get_status(i);
            string status_2 = get_status(j);
            if (status_1 == status_2){ // если строчки одинаковые, то есть на всех суффиксах эти префиксы ведут себя одинаково
                for (int k = 0; k < E.size(); ++k){
                    for (string al: alpha){
                        int f1 = check((S[i] + al + E[k]));
                        int f2 = check((S[j] + al + E[k]));
                        // проблемс
                        if (f1 != f2){
                            add_to_suf((al + E[k]));
                            is_neprot = 0;
                        }
                    }
                }
            }
        }
    }
    return is_neprot;
}

// доведение таблицы до состояния, когда можно делать запрос мату
void fill_table(){
    while (!neprot){
        while (!poln){
            build(); // достариваем таблицу, всё ок, тк при исполнении polnota() мы добавили новую строку
            proverka(); // проверяем каждый статус
            poln = polnota(); // проверяем на полноту
            print();
        }
        neprot = neprotivor(); // проверка на противоречивость
    }
}

int main(){
    int win = 0;
    S[0] = "e";
    E[0] = "e"; // e - пустое слово

    in.insert("e");
    is_main[0] = 1; // сразу ставим 1, тк изначально что-то говорим про пустое слово

    while (!win){
        fill_table();
        string w = equivalence();
        if (w == "ok"){
            win = 1;
        }
        else{
            add_to_suf(w);
            print();
            win = 1; // снова заглушка
        }
    }

    return 0;
}

