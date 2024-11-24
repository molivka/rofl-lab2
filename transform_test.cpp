#include "automaton.h"
#include "transform.cpp"
int main() {
	std::vector<std::vector<int>> table = {
	    {0, 0, 0, 1},
	    {1, 0, 0, 0},
	    {0, 0, 1, 0},
	    {0, 1, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 1},
	    {0, 1, 0, 0},
	    {1, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
  	};
  	std::vector<std::string> names = {"epsilon", "1", "2", "12", "11", "22", "21", "122", "121", "112", "111"};
  	Automaton res = transform(table, names);
  	res.print();
};