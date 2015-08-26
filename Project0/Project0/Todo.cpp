#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Todo {
	istream *inputstream;
	fstream infile;
	vector<string> mem;
	int length;
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
	length = 0;
	inputstream = &cin;
	infile.open(fname, fstream::in | fstream::out | fstream::app);
	while (!infile.eof()) {
		infile >> line;
		mem.push_back(line);//regex
		length++;
	}
	infile.seekp(0, ios::end);
}

void Todo::addit(string ins) {
	infile << ":[ ] " << ins << endl;
}

int main(int argc, char* argv[]) {
	if (argc > 4) {
		cerr << "Too many args!" << endl;
		return 0;
	}
	else if (argc == 4) {

	}
}