#pragma once

#include "Entropy.h"

namespace tpp {
	
	/* 
		I(X; Y) = H(X) - H(X | Y)
		I(X;Y) = H(Y) - H(Y|X)
		Compute mutual information from transition probability matrix
		and I/O probability distribution vector.

		Note: You need to match forward transition matrix with 
		source probability distribution (px) and backward tranistion probability
		matrix with output probability distribution (py).
	*/
	double mutualInformation(const DistributionMatrix& dm,
		const Vec<double>& p, bool isFwdTransMatrix = true, const Unit unit = tpp::Unit::BITS);

	// I(X;Y) = H(X) + H(Y) - H(X,Y)
	// Compute mutual information from a joint distribution X_Y
	double mutualInformation(const DistributionMatrix& X_Y, 
		const Unit unit = tpp::Unit::BITS);

}