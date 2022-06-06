#pragma once

#include <cmath>
#include <limits>
#include "Types.h"

namespace tpp {

	inline bool AreSame(double a, double b, double e = std::numeric_limits<double>::epsilon()) {
		return std::fabs(a - b) < e;
	}

	inline bool IsZero(double a) {
		return AreSame(a, 0.0);
	}

	// Calculate log of 'arg' with base specified by 'unit'
	double myLog(const double arg, const Unit unit);

	// Convert unit to base
	double unitToBase(const Unit unit);
	
}