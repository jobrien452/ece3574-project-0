#include <cxxtest/TestSuite.h>
#include "todo.h"

class mytest : public CxxTest::TestSuite {


public:

	void testAddit(void) {
		char * argv[] = { "todo" };
		int argc = 1;
		std::string teststr = "Test me \":D\"";
		todo driver(argc, argv);
		driver.addit(teststr);
		TS_ASSERT_EQUALS(driver.getList().front(), "1:[ ] " + teststr);
	}

	void testList(void) {
		TS_SKIP("1");
	}

	void testDoit(void) {
		TS_SKIP("1");
	}

	void testLoad(void) {
		TS_SKIP("1");
	}
};
