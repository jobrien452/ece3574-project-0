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
private:
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
	while (!infile.eof() && file != "todo.txt") {//read file and check where done tasks begin also measure length
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
	regex e ("\".*\"");
	if (regex_match(ins, e)) {
		ins = ins.substr(1, ins.length() - 2);
	}
	string line = ":[ ] " + ins;
	if (done == 0) {
		mem.push_back(line);
	}
	else {
		mem.insert(mem.begin()+(done - 1), line);
		done++;
	}
	length++;
	write();
}

void Todo::list(void) {
	infile.open(file, fstream::in | fstream::out | fstream::app);
	string temp;
	while (infile >> temp) {
		cout << temp << endl;
	}
}

void Todo::doit(int i) {
	string line;
	if (i < done && i > 0) {
		line = mem[i - 1];
		line.replace(2, 1, "X");
		mem.insert(mem.begin() + (done - 1), line);
		mem.erase(mem.begin() + (i - 1));
		done--;
		write();
	}
}

void Todo::write(void) {
	remove(file.c_str());
	int x = 1;
	string temp;
	infile.open(file, fstream::in | fstream::out | fstream::app);
	for (auto &pline : mem) {
		infile << x << pline << endl;
	}
	infile.close();
}

int main(int argc, char* argv[]) {
	if (argv[1] == "-f") {
		Todo driver(argv[2]);
		if (argv[3] != "add" && argc > 5) {
			cerr << "Too many args!1" << endl;
			return 0;
		}
		else if (argv[3] == "add" && argc > 5) {
			string temp = argv[4];
			for (int x = 4; x < argc; x++) {
				temp = temp + " " + argv[x];
			}
			driver.addit(argv[4]);
		}
		else if (argv[3] == "do" && argc == 5) {
			driver.doit(stoi(argv[4]));
		}
		else if (argc == 5) {
			cerr << "Too many args!2" << endl;
			return 0;
		}
		else if (argv[3] == "list") {
			driver.list();
		}
		else {
			cerr << "Incorrect Usage! Usage: todo [-f file] command" << endl;
			return 0;
		}
	}
	else {
		Todo driver;
		if (argv[1] != "add" && argc > 3) {
			cerr << "Too many args!3" << endl;
			return 0;
		}
		else if (argv[1] == "add" && argc > 3) {
			string temp = argv[4];
			for (int x = 4; x < argc; x++) {
				temp = temp + " " + argv[x];
			}
			driver.addit(argv[4]);
		}
		else if (argv[1] == "do" && argc == 3) {
			driver.doit(stoi(argv[4]));
		}
		else if (argc == 3) {
			cerr << "Too many args!4" << endl;
			return 0;
		}
		else if (argv[1] == "list") {
			driver.list();
		}
		else {
			cerr << "Incorrect Usage! Usage: todo [-f file] command" << endl;
			return 0;
		}
	}
}