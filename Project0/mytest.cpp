#include "todo.h"
#include "gtest/gtest.h"
// Copyright 2008 Google Inc.
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//Author: Jacob O'Brien (jakeo8@vt.edu)
std::string file = "todo.txt";

TEST(todo, ParseAdd) {
	remove(file.c_str());
	char * argv[] = {"todo", "add", "\"t1\""};
	int argc = 3;
	todo e(argc,argv);
	e.parse();
	ASSERT_TRUE(":[ ] t1" == e.getList()[0]);
}

TEST(todo, ParseDo) {
	//remove(file.c_str());
	char * argv[] = {"todo", "do", "1"};
	int argc = 3;
	todo e(argc,argv);
	e.parse();
	ASSERT_TRUE(":[X] t1" == e.getList()[0]);
}

TEST(todo, ParseList) {
	std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
	char * argv[] = {"todo", "list"};
	int argc = 2;
	todo e(argc,argv);
	e.parse();
	//e.list();
	std::cout.rdbuf(p_cout_streambuf);
	ASSERT_TRUE(oss.str() == "1:[X] t1\n");
	std::cout << oss.str();
}

TEST(todo, ParseUsage) {
	std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
	char * argv[] = {"todo", "-x"};
	int argc = 2;
	todo e(argc,argv);
	e.parse();
	//e.list();
	std::cout.rdbuf(p_cout_streambuf);
	ASSERT_TRUE(oss.str() == "Incorrect Usage! Usage: todo [-f file] command\n");
	std::cout << oss.str();
}

TEST(todo, ParseArgsFault) {
	std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
	char * argv[] = {"todo", "do", "2", "test"};
	int argc = 4;
	todo e(argc,argv);
	e.parse();
	//e.list();
	std::cout.rdbuf(p_cout_streambuf);
	ASSERT_TRUE(oss.str() == "Too many args!\n");
	std::cout << oss.str();
}
std::string wfile = "tfile.txt";

TEST(todo, ParseAddwFile) {
	remove(wfile.c_str());
	char * argv[] = {"todo", "-f", "tfile.txt" "add", "\"t1\""};
	int argc = 5;
	todo e(argc,argv);
	e.parse();
	ASSERT_TRUE(":[ ] t1" == e.getList()[0]);
}

TEST(todo, ParseDowFile) {
	//remove(file.c_str());
	char * argv[] = {"todo", "-f", "tfile.txt" "do", "1"};
	int argc = 5;
	todo e(argc,argv);
	e.parse();
	ASSERT_TRUE(":[X] t1" == e.getList()[0]);
}

TEST(todo, ParseListwFile) {
	std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
	char * argv[] = {"todo", "-f", "tfile.txt", "list"};
	int argc = 4;
	todo e(argc,argv);
	e.parse();
	//e.list();
	std::cout.rdbuf(p_cout_streambuf);
	ASSERT_TRUE(oss.str() == "1:[X] t1\n");
	std::cout << oss.str();
}

TEST(todo, ParseUsagewFile) {
	std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
	char * argv[] = {"todo", "-f", "tfile.txt", "-x"};
	int argc = 4;
	todo e(argc,argv);
	e.parse();
	//e.list();
	std::cout.rdbuf(p_cout_streambuf);
	ASSERT_TRUE(oss.str() == "Incorrect Usage! Usage: todo [-f file] command\n");
	std::cout << oss.str();
}

TEST(todo, ParseArgsFaultwFile) {
	std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
	char * argv[] = {"todo", "-f", "tfile.txt", "do", "2", "test"};
	int argc = 6;
	todo e(argc,argv);
	e.parse();
	//e.list();
	std::cout.rdbuf(p_cout_streambuf);
	ASSERT_TRUE(oss.str() == "Too many args!\n");
	std::cout << oss.str();
}

TEST(todo, AddIt) {
	remove(file.c_str());
	char * argv[] = {"todo"};
	int argc = 1;
	todo e(argc,argv);
	e.addit("new task");
	ASSERT_TRUE(":[ ] new task" == e.getList()[0]);
}

TEST(todo, DoIt) {
	remove(file.c_str());
	char * argv[] = {"todo", "add", "t1"};
	int argc = 3;
	todo e(argc,argv);
	e.parse();
	e.doit(1);
	ASSERT_TRUE(":[X] t1" == e.getList()[0]);
}

TEST(todo, List) {
	remove(file.c_str());
	std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
	char * argv[] = {"todo", "add", "new test"};
	int argc = 3;
	todo e(argc,argv);
	e.parse();
	e.list();
	std::cout.rdbuf(p_cout_streambuf);
	ASSERT_TRUE(oss.str() == "1:[ ] new test\n");
	std::cout << oss.str();
}