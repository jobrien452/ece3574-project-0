#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stdio.h>
using namespace std;

class Todo {
	fstream infile;
	vector<string> mem;
	string file;
	int length, done;
public:
	Todo();
	Todo(string);
	void addit(string);
	void list(void);
	void doit(int);
	void write(void);

};

Todo::Todo() {
	Todo("todo.txt");
}

Todo::Todo(string fname) {
	string line;
	file = fname;
	regex e ("^\d:\[X\]");//regex for done check
	length = 0;
	infile.open(file, fstream::in | fstream::out | fstream::app);
	while (!infile.eof()) {//read file and check where done tasks begin also measure length
		infile >> line;
		mem.push_back(line.substr(1,line.npos));
		length++;
		if (regex_match(line.substr(0, 5), e)) {
			done = length;
		}
	}
	infile.close();
}

void Todo::addit(string ins) {
	string line = ":[ ] " + ins;
	if (done == 0) {
		mem.push_back(line);
	}
	else {
		mem.insert(mem.begin()+(done - 1), line);
		done++;
	}
	length++;
	
}

void Todo::list(void) {
	
}

void Todo::doit(int i) {
	string line;
	if (i < done && i > 0) {
		line = mem[i - 1];
		line.replace(2, 1, "X");
		mem.insert(mem.begin() + (done - 1), line);
		mem.erase(mem.begin() + (i - 1));
		done--;
	}
}

void Todo::write(void) {
	remove(file.c_str);
	int x = 1;
	string temp;
	infile.open(file, fstream::in | fstream::out | fstream::app);
	for (auto &pline : mem) {
		infile << x << pline << endl;
	}
	infile.close();
}

int main(int argc, char* argv[]) {
	if (argc > 4 && strcmp(argv[3],"add") != 0) {
		cerr << "Too many args!" << endl;
		return 0;
	}
	else if (argc == 4) {

	}
}