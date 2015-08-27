#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stdio.h>
using namespace std;

class Todo {//class construct
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

Todo::Todo() { //default constuctor
	Todo("todo.txt");
}
//overloaded constructor
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
		if (regex_match(line.substr(0, 5), e)) {//checks if line is done using regex
			done = length;
		}
	}
	infile.close();
}

void Todo::addit(string ins) {//adds string to file
	regex e ("\".*\"");
	if (regex_match(ins, e)) {//check if string has prentheses 
		ins = ins.substr(1, ins.length() - 2);
	}
	string line = ":[ ] " + ins;
	if (done == 0) { //if no done tasks adds to end
		mem.push_back(line);
	}
	else { //else adds to one before last finished
		mem.insert(mem.begin()+(done - 1), line);
		done++;
	}
	length++;
	write(); //writes to file
}

void Todo::list(void) { //lists file
	infile.open(file, fstream::in | fstream::out | fstream::app);
	string temp;
	while (infile >> temp) {
		cout << temp << endl;
	}
}

void Todo::doit(int i) { //if number for do is correct and isn't an already done task
	string line;		 //doit updates vector then writes to file
	if (i < done && i > 0) {
		line = mem[i - 1];
		line.replace(2, 1, "X");
		mem.insert(mem.begin() + (done - 1), line);
		mem.erase(mem.begin() + (i - 1));
		done--;
		write();
	}
}

void Todo::write(void) { //clears file then rewrites with new data
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
	if (argv[1] == "-f") { //case if -f switch is used
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
	else { //case used if default file is chosen
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