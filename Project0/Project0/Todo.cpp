#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stdio.h>
using namespace std;

class Todo {//class construct
public:
	Todo();
	Todo(string);
	void addit(string);
	void list(void);
	void doit(int);
private:
	void write(void);
	fstream infile;
	vector<string> mem;
	string file;
	int length, done;
	
};

Todo::Todo() { //default constuctor
	string line;
	file = "todo.txt";
	regex e("^\d:\[X\]");//regex for done check
	length = 0;
	done = 0;
	infile.open(file.c_str(), fstream::in);
	while (getline(infile, line)) {//read file and check where done tasks begin also measure length
		if (!line.empty()) {
			mem.push_back(line.substr(1, line.npos));
			length++;
			if (regex_match(line.substr(0, 5), e)) {//checks if line is done using regex
				done = length;
			}
		}
	}
	infile.close();
}
//overloaded constructor
Todo::Todo(string fname) : file(fname) {
	Todo();
	string line;
	regex e("^\d:\[X\]");//regex for done check
	infile.open(file.c_str(), fstream::in);
	while (getline(infile, line)) {//read file and check where done tasks begin also measure length
		if (!line.empty()) {
			mem.push_back(line.substr(1, line.npos));
			length++;
			if (regex_match(line.substr(0, 5), e)) {//checks if line is done using regex
				done = length;
			}
		}
	}
	infile.close();
}

void Todo::addit(string ins) {//adds string to file
	cout << file << "!" << endl;
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
	infile.open(file.c_str(), fstream::in | fstream::out | fstream::app);
	string temp;
	while (infile >> temp) {
		cout << temp << endl;
	}
	infile.close();
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
	infile.open(file.c_str(), fstream::trunc);
	infile.close();
	int x = 1;
	infile.open(file.c_str(), fstream::in | fstream::out | fstream::app);
	for (auto &pline : mem) {
		infile << x << pline << endl;
		x++;
	}
	infile.close();
}

int main(int argc, char* argv[]) {//Main driver for program
	if (string(argv[1]) == "-f") { //case if -f switch is used
		Todo driver(argv[2]);
		string argthree = string(argv[3]);
		if (argthree != "add" && argc > 5) {
			cerr << "Too many args!1" << endl;
			return 0;
		}
		else if (argthree == "add" && argc > 5) {
			string temp = string(argv[4]);
			for (int x = 4; x < argc; x++) {
				temp = temp + " " + argv[x];
			}
			driver.addit(temp);
		}
		else if (argthree == "do" && argc == 5) {
			driver.doit(stoi(string(argv[4])));
		}
		else if (argc == 5) {
			cerr << "Too many args!2" << endl;
			return 0;
		}
		else if (argthree == "list") {
			driver.list();
		}
		else {
			cerr << "Incorrect Usage! Usage: todo [-f file] command" << endl;
			return 0;
		}
	}
	else { //case used if default file is chosen
		Todo driver;
		string argone = string(argv[1]);
		if (argone != "add"  && argc > 2) {
			cerr << "Too many args!3" << argv[1] << endl;
			return 0;
		}
		else if (argone == "add" && argc > 2) {
			string temp = string(argv[2]);
			for (int x = 3; x < argc; x++) {
				temp = temp + " " + argv[x];
			}
			driver.addit(temp);
		}
		else if (argone == "do" && argc == 3) {
			driver.doit(stoi(string(argv[2])));
		}
		else if (argc == 3) {
			cerr << "Too many args!4" << endl;
			return 0;
		}
		else if (argone == "list") {
			driver.list();
		}
		else {
			cerr << "Incorrect Usage! Usage: todo [-f file] command" << endl;
			return 0;
		}
	}
	return 0;
}