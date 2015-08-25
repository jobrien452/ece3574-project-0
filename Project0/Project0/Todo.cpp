#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Todo {
	istream *inputstream;
	ifstream infile;
public:
	Todo();
	Todo(string);
	void addit(string);
	string list(void);
	void doit(int);

};
Todo::Todo() {

}

Todo::Todo(string fname) {
	
}

int main(int argc, char* argv[]) {
	if (argc > 4) {
		cerr << "Too many args!" << endl;
		return 0;
	}
	else if (argc == 4) {

	}
}