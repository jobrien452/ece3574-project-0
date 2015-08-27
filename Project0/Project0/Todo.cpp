#include "todo.h"

todo::todo(int argc, char *argv[]) { //default constuctor
	file = "todo.txt";
	length = 0;
	done = 0;
	std::string line;
	for (auto &argv : line) {
		args.push_back(line);
	}
	if (args[1] == "-f") {
		file = args[1];
	}
}

void todo::addit(std::string ins) {//adds string to file
	std::regex e ("\".*\"");
	if (regex_match(ins, e)) {//check if string has prentheses 
		ins = ins.substr(1, ins.length() - 2);
	}
	std::string line = ":[ ] " + ins;
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

void todo::list(void) { //lists file
	infile.open(file.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	std::string temp;
	while (infile >> temp) {
		std::cout << temp << std::endl;
	}
	infile.close();
}

void todo::doit(int i) { //if number for do is correct and isn't an already done task
	std::string line;		 //doit updates vector then writes to file
	if (i < done && i > 0) {
		line = mem[i - 1];
		line.replace(2, 1, "X");
		mem.insert(mem.begin() + (done - 1), line);
		mem.erase(mem.begin() + (i - 1));
		done--;
		write();
	}
}

void todo::load(void) {
	std::string line;
	std::regex e("^\d:\[X\]");//regex for done check
	infile.open(file.c_str(), std::fstream::in);
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
	remove(file.c_str());
}

void todo::write(void) { //clears file then rewrites with new data
	infile.open(file.c_str(), std::fstream::trunc);
	infile.close();
	int x = 1;
	infile.open(file.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	for (auto &pline : mem) {
		infile << x << pline << std::endl;
		x++;
	}
	infile.close();
}

void todo::parse(void) {

}

int main(int argc, char *argv[]) {//Main driver for program
	todo driver(argc, argv);
	if (std::string(argv[1]) == "-f") { //case if -f switch is used
		std::string argthree = std::string(argv[3]);
		if (argthree != "add" && argc > 5) {
			std::cerr << "Too many args!1" << std::endl;
			return 0;
		}
		else if (argthree == "add" && argc > 5) {
			std::string temp = std::string(argv[4]);
			for (int x = 4; x < argc; x++) {
				temp = temp + " " + argv[x];
			}
			driver.addit(temp);
		}
		else if (argthree == "do" && argc == 5) {
			driver.doit(std::stoi(std::string(argv[4])));
		}
		else if (argc == 5) {
			std::cerr << "Too many args!2" << std::endl;
			return 0;
		}
		else if (argthree == "list") {
			driver.list();
		}
		else {
			std::cerr << "Incorrect Usage! Usage: todo [-f file] command" << std::endl;
			return 0;
		}
	}
	else { //case used if default file is chosen
		std::string argone = std::string(argv[1]);
		if (argone != "add"  && argc > 2) {
			std::cerr << "Too many args!3" << argv[1] << std::endl;
			return 0;
		}
		else if (argone == "add" && argc > 2) {
			std::string temp = std::string(argv[2]);
			for (int x = 3; x < argc; x++) {
				temp = temp + " " + argv[x];
			}
			driver.addit(temp);
		}
		else if (argone == "do" && argc == 3) {
			driver.doit(std::stoi(std::string(argv[2])));
		}
		else if (argc == 3) {
			std::cerr << "Too many args!4" << std::endl;
			return 0;
		}
		else if (argone == "list") {
			driver.list();
		}
		else {
			std::cerr << "Incorrect Usage! Usage: todo [-f file] command" << std::endl;
			return 0;
		}
	}
	return 0;
}