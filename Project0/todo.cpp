#include "todo.h"
//todo class file
//
//Author: Jacob O'Brien (jakeo8@vt.edu)

todo::todo(int argc, char * argv[]) { //default constuctor
	file = "todo.txt";
	length = 0;
	done = 0;
	for (int x = 0; x < argc; x++) {
		args.push_back(argv[x]);
	}
	if (args[1] == "-f") {
		file = args[2];
	}
}

void todo::addit(std::string ins) {//adds string to file
	std::size_t found = ins.find("\""); //removed regex for compatibility
	while (found != std::string::npos) {
		ins.replace(found, 1, "");
		found = ins.find("\"");
	}
	/*std::regex e ("\"");
	while (regex_match(ins, e)) {//check if string has prentheses 
		std::regex_replace(ins, e, "");
	}*/
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

void todo::list() { //lists file
	infile.open(file.c_str(), std::fstream::in);
	std::string temp;
	while (getline(infile, temp)) {
		std::cout << temp << std::endl;
	}
	infile.close();
}

void todo::doit(int i) { //if number for do is correct and isn't an already done task
	std::string line;		 //doit updates vector then writes to file
	if (i < done && i > 0) {
		line = mem[i - 1];
		line.replace(2, 1, "X");
		mem.push_back(line);
		mem.erase(mem.begin() + (i - 1));
		done--;
		write();
	}
	else if (done == 0) {
		line = mem[i - 1];
		line.replace(2, 1, "X");
		mem.push_back(line);
		mem.erase(mem.begin() + (i - 1));
		done = length;
		write();
	}
	else if(i>length){
		std::cerr << "Cannot complete task " << i << ", It does not exist." << std::endl;
	}
}

void todo::load(void) {
	std::string line;
	std::string e = ":[X]";
	std::size_t found; //removed regex for compatibility
	//std::regex e("^[[:digit:]]:\\[X\\]");//regex for done check
	infile.open(file.c_str(), std::fstream::in);
	while (getline(infile, line)) {//read file and check where done tasks begin also measure length
		if (!line.empty()) {
			mem.push_back(line.substr(1, line.npos));
			length++;
			found = line.find(e);
			if(found != std::string::npos) {
			//if (regex_match(line.substr(0, 5), e) && done == 0) {//checks if line is done using regex
				done = length;
			}
		}
	}
	infile.close();
}

void todo::write(void) { //clears file then rewrites with new data
	remove(file.c_str());
	int x = 1;
	std::string line;
	infile.open(file.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	for (auto &line : mem) {
		infile << x << line << std::endl;
		x++;
	}
	infile.close();
}

void todo::parse(void) {
	load();
	if (file == "todo.txt") { //case if -f switch is used
		if (args[1] == "add") {
			std::string line = args[2];
			for (size_t x = 3; x < args.size(); x++){
				line = line + " " + args[x];
			}
			addit(line);
		}
		else if (args[1] == "list" && args.size() == 2) {
			list();
		}
		else if (args[1] == "do" && args.size() == 3) {
			doit(std::stoi(args[2]));
		}
		else if (args.size() > 3) {
			std::cerr << "Too many args!*" << std::endl;
			exit(0);
		}
		else {
			std::cerr << "Incorrect Usage! Usage: todo [-f file] command*" << std::endl;
			exit(0);
		}
	}
	else { //case used if default file is chosen
		if (args[3] == "add") {
			std::string line = args[4];
			for (size_t x = 5; x < args.size(); x++) {
				line = line + " " + args[x];
			}
			addit(line);
		}
		else if (args[3] == "list" && args.size() == 4) {
			list();
		}
		else if (args[3] == "do" && args.size() == 5) {
			doit(std::stoi(args[4]));
		}
		else if (args.size() > 5) {
			std::cerr << "Too many args!" << std::endl;
			exit(0);
		}
		else {
			std::cerr << "Incorrect Usage! Usage: todo [-f file] command" << std::endl;
			exit(0);
		}
	}
}

std::vector<std::string> todo::getList(void) {
	return mem;
}
