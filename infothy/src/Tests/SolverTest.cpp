#include "SolverTest.h"

using namespace tpp;

namespace {
	DMCSolver getSolverForFile(std::string_view filename) {
		DMCSolver dmcs;

		std::ifstream fs(filename.data());

		if (!fs) {
			throw std::exception("File failed to load");
		}

		fs >> dmcs;
		return dmcs;
	}

	void showSolution(const DMCSolver& dmcs) {
		std::cout << dmcs.getDistrMat() << std::endl;
		printVec(dmcs.getIOVec());
		std::cout << std::endl;
		std::cout << dmcs.solve() << std::endl;
	}
}

void tpp::testSolver1()
{
	std::cout << "Test solver 1" << std::endl;
	auto dmcs = getSolverForFile("./input/z1.txt");
	showSolution(dmcs);
}

void tpp::testSolver2()
{
	std::cout << "Test solver 2" << std::endl;
	auto dmcs = getSolverForFile("./input/z2.txt");
	showSolution(dmcs);
}

void tpp::testSolver3()
{
	std::cout << "Test solver 3" << std::endl;
	auto dmcs = getSolverForFile("./input/z3.txt");
	showSolution(dmcs);
}

void tpp::testSolver4()
{
	std::cout << "Test solver 4" << std::endl;
	auto dmcs = getSolverForFile("./input/z4.txt");
	showSolution(dmcs);
	std::cout << "Valid txn matrix: " << std::boolalpha << dmcs.isValidTransitionMatrix() << std::endl;
}
