#include <iostream>
#include <string>
#include "Information/dmccapacity.h"
#include "Tests/channeltest.h"

int main(int argc, char* argv[]) {

	if (argc < 2) {
		// Arguments were expected
		// return 1;
	}
	
	// Improve performance, since we arne't using C-style I/O (printf, scanf)
	std::ios_base::sync_with_stdio(false);

	tpp::test1();
	tpp::test2();
	tpp::test3();
	tpp::test4();
	tpp::test5();
	tpp::test6();

	return 0;
}