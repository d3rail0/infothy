#pragma once

#include "../DMCSolver.h"
#include <string_view>

namespace tpp {

	// Input distribution vector and channel matrix
	void testSolver1();

	// Joint probability distribution
	void testSolver2();

	// 10x10 input vec & distr matrix
	void testSolver3();

	// Backward prob transition matrix and output
	// probability source distribution
	void testSolver4();

}