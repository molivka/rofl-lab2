#include "automaton.h"
//создание строки string из строки 0 и 1 для удобства сравнения
std::string arrayToString(const std::vector<int>& arr) {
  std::string result;
  for (int value : arr) {
    result += std::to_string(value);
  }
  return result;
};

//нахождение уникальных строк с минимальными по длине именами 
std::vector<std::string> findMinimalNames(const std::vector<std::string>& rows, const std::vector<std::string>& names) {
  std::unordered_map<std::string, std::string> rowToMin; //текущая самая короткая строка
  std::vector<std::string> minimalNames; //список состояний

  // проходим по строкам созданным из таблицы
  for (size_t i = 0; i < rows.size(); ++i) {
    std::string row = rows[i];
    std::string word = names[i];
    std::string name = names[i];
    if (name == "ε") {
    	name = "";
    }

    // если строка уже была
    if (auto it = rowToMin.find(row); it != rowToMin.end()) {
      // сравниваем с самой короткой на данный момент
      if (name.length() < (*it).second.length()) {
        rowToMin[row] = name;
      }
    } else {
      // если впервые, то просто сохраняем
      rowToMin[row] = name;
    }
  }
  
	for (auto mins : rowToMin) {
		minimalNames.push_back(rowToMin[mins.first]);
	}
  return minimalNames;
}

Automaton transform(std::vector<std::vector<int>>& table, std::vector<std::string>& names) {

	std::vector<std::string> rows; //список строк из таблицы
	std::unordered_map<std::string, std::string> nameToRow; //соответствие строки к имени
	for (int i = 0; i < names.size(); i++) {
		std::string str = arrayToString(table[i]);
		rows.push_back(str);
		if (names[i] == "ε") { //если это эпсилон - заменяем на пустую строку
			nameToRow[""] = str;
		} else {
			nameToRow[names[i]] = str;
		}
	}
	std::vector<std::string> minimalNames = findMinimalNames(rows, names); //находим список состояний
	std::unordered_map<std::string, std::unordered_map<int, int>> nameToState; //создаем мапу состояние - переходы
	
	std::unordered_set<int> finals; //смотрим, если в первом столбце 1 - значит финальное
	for (int i = 0; i < rows.size(); i++) {
		if (table[i][0] == 1) {
			if (find(minimalNames.begin(), minimalNames.end(), names[i]) != minimalNames.end()) {
				finals.insert(std::stoi(names[i]));
			}
		}
	}

	//основная часть алгоритма. проходим по состояниям и для каждого строим переходы в другие состояния по парсингу имени, а так же находим все эквивалентные строки в таблице и по правилу "Если ay = a' (т.е. aу и a' соответствуют одинаковым строчкам в таблице), то (a, y) - a' добавляется в ДКА как переход."
	for (int i = 0; i < minimalNames.size(); i++) {
		for (int j = 0; j < rows.size(); j++) {
			if (names[j]==minimalNames[i]) {
				continue;
			}
			auto word = find(minimalNames.begin(), minimalNames.end(), names[j]);
			if (word != minimalNames.end()) { //если строка соответствует строке состояния
				if (names[j].find(minimalNames[i]) == 0) {
      				std::string symbol = names[j].substr(minimalNames[i].length()); //ищем, какое другое имя состояния начинается с этого
      				if (symbol.length() == 1) { //переход из состояния в другое производится по одному символу, поэтому проверяем
      					int target;
				    	if (names[j] == "") {
				    		target = -1;
				    	} else {
				    		target = std::stoi(names[j]);
				    	}
      					nameToState[minimalNames[i]][std::stoi(symbol)] = target;
      				}
      			}
      		} else { //если строка не соответствует строке состояния
      			if (nameToRow[minimalNames[i]] == rows[j]) { //строки одинаковые
      				for (auto state : minimalNames) {
      					if (names[j].find(state) == 0) {//ищем, какое состояние является началом этого
      						std::string symbol = names[j].substr(state.length()); //отделяем символ перехода
      						if (symbol.length() == 1) {
      							int target;
						    	if (minimalNames[i] == "") {
						    		target = -1;
						    	} else {
						    		target = std::stoi(minimalNames[i]);
						    	}
      							nameToState[state][std::stoi(symbol)] = target;
      						}
      					}
      				}
      			}
      		}
      	}
    }
    std::vector<State> states;
    for (auto state : nameToState) { //создаем состояния
    	std::multimap<int, int> transitions1;
    	int name;
    	if (state.first == "") {
    		name = -1;
    	} else {
    		name = std::stoi(state.first);
    	}
    	State newState(name, transitions1, state.second);
    	states.push_back(newState);
    }
    std::vector<int> alphabet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int start = -1;
    return Automaton(states, start, finals, alphabet, EOL);
};
