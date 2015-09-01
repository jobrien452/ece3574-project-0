#include "todo.h"
#include "gtest/gtest.h"

TEST(todo, ParseAdd) {
	char * argv[] = {"todo", "add", "\"t1\""};
	int argc = 3;
	todo e(argc,argv);
	e.parse();
	ASSERT_TRUE(":[ ] t1" == e.getList()[0]);
}


TEST(todo, ParseDo) {
	char * argv[] = {"todo", "do", "1"};
	int argc = 3;
	todo e(argc,argv);
	e.parse();
	ASSERT_TRUE(":[X] t1" == e.getList()[0]);
}