#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>
#include "../distrmtx.h"
#include "../utils.h"

#include <functional>

namespace tpp {

	// Calculate Shannon entropy from symbol sequence 'input' and 3
	// apply log with base specified by 'unit' on each step
	double shannonEntropy(const Vec<double>& input, 
		const Unit unit = tpp::Unit::BITS);

	// Computes conditioned entropy H(Y|x) given a joint distribution
	double conditionedEntropyYx(const DistributionMatrix& X_Y, size_t x, 
		const Unit unit = tpp::Unit::BITS);
	
	// Computes conditioned entropy H(X|y) given a joint distribution
	double conditionedEntropyXy(const DistributionMatrix& X_Y, size_t y, 
		const Unit unit = tpp::Unit::BITS);

	// Computes conditional entropy H(Y|X) given a joint distribution
	double conditionalEntropyYX(const DistributionMatrix& X_Y, 
		const Unit unit = tpp::Unit::BITS);

	// Computes conditional entropy H(X|Y) given a joint distribution
	double conditionalEntropyXY(const DistributionMatrix& X_Y, 
		const Unit unit = tpp::Unit::BITS);

	// Compute joint entropy H(X, Y) given a joint distribution
	double jointEntropyXY(const DistributionMatrix& X_Y, 
		const Unit unit = tpp::Unit::BITS);


	// Entropy computation without joint distribution

	// Computes H(Y|x) given a forward transition matrix
	double conditionedEntropyQYx(const DistributionMatrix& YX, size_t x,
		const Unit unit = tpp::Unit::BITS);

	// Computes H(Y|x) given a forward transition matrix
	double conditionedEntropyQXy(const DistributionMatrix& XY, size_t y,
		const Unit unit = tpp::Unit::BITS);

	// Computes H(Y|X) = Sum[ P(xi) * H (Y|xi) ]
	// Given forward transition matrix and source probability distribution
	double conditionalEntropyYX(const DistributionMatrix& YX, const Vec<double>& px,
		const Unit unit = tpp::Unit::BITS);

	// Computes H(X|Y) = Sum[ P(yj) * H (X|yj) ]
	// Given backward transition matrix and output probability distribution
	double conditionalEntropyXY(const DistributionMatrix& XY, const Vec<double>& py,
		const Unit unit = tpp::Unit::BITS);

}