#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <regex>
#include "test_sem.cpp"
#include "MAT.cpp"

using namespace std;

#define endl '\n'


map<int, string> S; // строки таблицы = классы эквивалентности
map<int, string> E; // столбцы таблицы = различающие суффиксы 
map<pair<int, int>, int> table; // таблица входимости
map<int, int> is_main; // хранит флаг принадлежности к основной части, 1 - основная часть, 0 - доп часть

vector<string> alphabet = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}; // алфавит языка

set<string> all_clases; // набор всех слов-классов
int closed = 0; // является ли таблица полной
int consist = 0; // является ли таблица непротиворечивой
int test_case = 1; // 0 - просто, 1 - с семинара

map<string, int> testing_check;
map<string, string> testing_equivalence;

// вывод основных сущностей
void print(){
    cout << "prefixes: " << endl;
    for (int i = 0; i < S.size(); ++i){
        cout << S[i] << ' ';
    }
    cout << endl;
    cout << "suffixes: " << endl;
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
    for (auto i: all_clases){
        cout << i << ' ';
    }
    cout << endl;
}

// запрос к мату на принадлежность
int check(string w){
    int ans;
    if (test_case){
        ans = MAT_check_test(w);
    }
    else{
        ans = MAT_check(w);
    }

    return ans;
}

// запрос к мату на эквивалентность
string equivalence(){
    string status;
    vector<string> to_mat; // классы эквивалентности, которые отправляем мату 
    for (auto i: S){
        string word = i.second;
        to_mat.push_back(word);
    }
    if (test_case){
        status = MAT_equivalence_test(to_mat);
    }
    else{
        vector<string> main_prefixes, non_main_prefixes, suffixes;
        vector<int> table_for_mat;
        for (int i = 0; i < S.size(); ++i){
            if (is_main[i]){
                main_prefixes.push_back(S[i]);
            }
            else{
                non_main_prefixes.push_back(S[i]);
            }
            table_for_mat.push_back(table[{i, 0}]);
        }
        for (int i = 0; i < E.size(); ++i){
            suffixes.push_back(E[i]);
        }
        status = MAT_equivalence_test(main_prefixes, non_main_prefixes, suffixes, table_for_mat);
    }
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
void add_to_suff(string w){
    string w_rev = ""; //чтобы не было O(n^2)
    for (int i = w.size() - 1; i >= 0; --i){
        string wi = "";
        wi.push_back(w[i]); // цыганские фокусы
        w_rev = concat(wi, w_rev);
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
void all_check(){
    for (int i = 0; i < S.size(); ++i){
        for (int j = 0; j < E.size(); ++j){
            string new_str = concat(S[i], E[j]);
            int f = check(new_str); // проверка принадлежности слова
            table[{i, j}] = f; // записали принадлежит ли слово S[i] + E[j] языку
        }
    }
}

// строим дополнительную часть
void build(){
    int n = S.size(); // тк в процесса изменяется
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < alphabet.size(); ++j){
            if (is_main[i] != 1){
                continue; // если слово не в главной части - скип
            }
            string new_str = concat(S[i], alphabet[j]);
            if (all_clases.find(new_str) != all_clases.end()){ // если мы получали уже это слово
                continue;
            }
            S[S.size()] = new_str; // получили новое слово путём конкатенации
            is_main[S.size()] = 0; // нужно, тк в мапе не было до этого значений
            all_clases.insert(new_str); // тк сет, то пофиг, но это действительно новое слово
        }
    }
}

// проверка таблицы на полноту
int fullness(){
    int is_closed = 1; // полна ли таблица на этой итерации
    set<string> statuses; // строки-статусы, которые отражают принадлежность
    for (int i = 0; i < S.size(); ++i){
        string row = get_status(i);
        if (is_main[i] == 1){ // если это основная часть, то чекать не нужно
            statuses.insert(row);
        }  
        else{
            if (statuses.find(row) == statuses.end()){ // если в доп части есть новая строка - сохраняем
                is_closed = 0; // обновили таблицу => она не была полной
                statuses.insert(row);
                is_main[i] = 1; // переносим её в основную
            }
        }
    }
    return is_closed;
}

// проверка на непротиворечивость
int consistent(){
    int is_consist = 1;
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
                    for (string al: alphabet){
                        int f1 = check((S[i] + al + E[k]));
                        int f2 = check((S[j] + al + E[k]));
                        // проблемс
                        if (f1 != f2){
                            add_to_suff((al + E[k]));
                            is_consist = 0;
                        }
                    }
                }
            }
        }
    }
    return is_consist;
}

// доведение таблицы до состояния, когда можно делать запрос мату
void fill_table(){
    while (!consist){
        while (!closed){
            build(); // достариваем таблицу, всё ок, тк при исполнении polnota() мы добавили новую строку
            all_check(); // проверяем каждый статус
            closed = fullness(); // проверяем на полноту
            print();
        }
        consist = consistent(); // проверка на противоречивость
    }
}

int main(){
    if (test_case){
        alphabet = {"a", "b"};
    }

    int win = 0;
    S[0] = "e";
    E[0] = "e"; // e - пустое слово

    all_clases.insert("e");
    is_main[0] = 1; // сразу ставим 1, тк изначально что-то говорим про пустое слово

    while (!win){
        fill_table();
        string w = equivalence();
        if (w == "ok"){
            win = 1;
        }
        else{
            add_to_suff(w);
            print();
        }
    }

    return 0;
}
