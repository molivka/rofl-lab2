#include "automaton.h"

std::string arrayToString(const std::vector<int>& arr) {
  std::string result;
  for (int value : arr) {
    result += std::to_string(value);
  }
  return result;
};

std::vector<std::string> findMinimalNames(const std::vector<std::string>& rows, const std::vector<std::string>& names) {
  std::unordered_map<std::string, std::string> rowToMin;
  std::vector<std::string> minimalNames;
  std::vector<std::string> rowSet;
  std::unordered_map<std::string, std::unordered_set<std::string>> rowToNames;

  // Проходим по каждой строке и ее имени
  for (size_t i = 0; i < rows.size(); ++i) {
    std::string row = rows[i];
    std::string word = names[i];
    std::string name = names[i];
    if (name == "epsilon") {
    	name = "";
    }
    rowToNames[row].insert(name);

    // Если строка уже встречалась, сравниваем длины имен
    if (auto it = rowToMin.find(row); it != rowToMin.end()) {
      // Выбираем имя с минимальной длиной
      if (name.length() < (*it).second.length()) {
        rowToMin[row] = name;
      }
    } else {
      // Если строка встречается впервые, сохраняем ее имя
      rowToMin[row] = name;
    }
  }
	for (auto mins : rowToMin) {
		minimalNames.push_back(rowToMin[mins.first]);
	}
  return minimalNames;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> transform(std::vector<std::vector<int>>& table, std::vector<std::string>& names) {
	std::vector<std::string> rows;
	std::unordered_map<std::string, std::string> nameToRow;
	for (int i = 0; i < names.size(); i++) {
		std::string str = arrayToString(table[i]);
		rows.push_back(str);
		if (names[i] == "epsilon") {
			nameToRow[""] = str;
		} else {
			nameToRow[names[i]] = str;
		}
		
	}
	std::vector<std::string> minimalNames = findMinimalNames(rows, names);
	for (auto str : minimalNames) {
		std::cout << str << " o\n";
	}
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> nameToState;
	for (auto state : minimalNames) {
		std::unordered_map<std::string, std::string> transitions;
		nameToState[state] = transitions;
	}
		
	for (int i = 0; i < minimalNames.size(); i++) {
		for (int j = 0; j < rows.size(); j++) {
			if (names[j]==minimalNames[i]) {
				continue;
			}
			auto word = find(minimalNames.begin(), minimalNames.end(), names[j]);
			if (word != minimalNames.end()) {
				if (names[j].find(minimalNames[i]) == 0) {
      				std::string symbol = names[j].substr(minimalNames[i].length());
      				if (symbol.length() == 1) {
      					nameToState[minimalNames[i]][symbol] = names[j];
      				}
      			}
      		} else {
      			if (nameToRow[minimalNames[i]] == rows[j]) {
      				std::cout << minimalNames[i] << "        " << names[j] << "\n";
      				for (auto state : minimalNames) {
      					if (names[j].find(state) == 0) {
      						std::string symbol = names[j].substr(state.length());
      						if (symbol.length() == 1) {
      							nameToState[state][symbol] = minimalNames[i];
      						}
      					}
      				}
      			}
      		}
      	}
    }
    return nameToState;
};
