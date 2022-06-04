#pragma once

#include <cmath>
#include <limits>
#include "types.h"

namespace tpp {

	inline bool AreSame(double a, double b) {
		return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
	}

	inline bool IsZero(double a) {
		return AreSame(a, 0.0);
	}

	// Calculate log of 'arg' with base specified by 'unit'
	double myLog(const double arg, const Unit unit);
	
}