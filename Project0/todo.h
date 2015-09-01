#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stdio.h>

class todo {//class construct
public:
	todo(int argc, char * argv[]);
	void addit(std::string);
	void list(void);
	void doit(int);
	void parse(void);
	std::vector<std::string> getList(void);
private:
	void load(void);
	void write(void);
	std::fstream infile;
	std::vector<std::string> mem, args;
	std::string file;
	int length, done;

};
