#include "SolverTest.h"

using namespace tpp;

void tpp::testSolver1()
{
	std::cout << "Test solver 1" << std::endl;

	DMCSolver dmcs;

	std::ifstream fs("./input/z1.txt");

	if (!fs) {
		throw std::exception("File failed to load");
	}

	fs >> dmcs;

	std::cout << dmcs.getDistrMat() << std::endl;
	printVec(dmcs.getIOVec());
	std::cout << std::endl;

	std::cout << dmcs.solve() << std::endl;

}

void tpp::testSolver2()
{
	std::cout << "Test solver 2" << std::endl;

	DMCSolver dmcs;

	std::ifstream fs("./input/z2.txt");

	if (!fs) {
		throw std::exception("File failed to load");
	}

	fs >> dmcs;

	std::cout << dmcs.getDistrMat() << std::endl;
	printVec(dmcs.getIOVec());
	std::cout << std::endl;

	std::cout << dmcs.solve() << std::endl;

}
