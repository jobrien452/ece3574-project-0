#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

class Todo {
	fstream infile;
	vector<string> mem;
	int length, done;
public:
	Todo();
	Todo(string);
	void addit(string);
	string list(void);
	void doit(int);

};

Todo::Todo() {
	Todo("todo.txt");
}

Todo::Todo(string fname) {
	string line;
	regex e ("^\d:\[X\]");//regex for done check
	length = 0;
	infile.open(fname, fstream::in | fstream::out | fstream::app);
	while (!infile.eof()) {//read file and check where done tasks begin also measure length
		infile >> line;
		mem.push_back(line);
		length++;
		if (regex_match(line.substr(0, 5), e)) {
			done = length;
		}
	}
	infile.close();
}

void Todo::addit(string ins) {
	string line = ":[ ] " + ins + "\n";
	if (done == 0) {
		mem.push_back(line);
	}
	else {
		mem.insert(mem.begin()+(done - 1), line);
		done++;
	}
	length++;
	
}

int main(int argc, char* argv[]) {
	if (argc > 4 && strcmp(argv[3],"add") != 0) {
		cerr << "Too many args!" << endl;
		return 0;
	}
	else if (argc == 4) {

	}
}