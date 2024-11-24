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

  	// auto res = transform(table, names);
  	// for (auto state : res) {
  	// 	std::string s = state.first;
  	// 		if (s == "") {
  	// 			s = "epsilon";
  	// 		}
  	// 	std::cout << s << " ";
  	// 	for (auto j : state.second) {
  	// 		std::string s1 = j.first;
  	// 		std::string s2 = j.second;
  	// 		if (s1 == "") {
  	// 			s1 = "epsilon";
  	// 		}
  	// 		if (s2 == "") {
  	// 			s2 = "epsilon";
  	// 		}
    //     	std::cout << s1 << " " << s2 << std::endl;
    //     }
    //     std::cout << " kkkkkkk ";
    // }
};