#include <iostream>
#include <string>
#include "Information/dmccapacity.h"
#include "Tests/channeltest.h"
#include "Tests/solvertest.h"

void runTests() {
	tpp::test1();
	tpp::test2();
	tpp::test3();
	tpp::test4();
	tpp::test5();
	tpp::test6();

	tpp::testSolver1();
	tpp::testSolver2();
	tpp::testSolver3();
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		// Arguments were expected
		// return 1;
	}
	
	// Improve performance, since we arne't using C-style I/O (printf, scanf)
	std::ios_base::sync_with_stdio(false);


	tpp::testSolver2();
	tpp::testSolver4();

	return 0;
}