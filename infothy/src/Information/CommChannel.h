#pragma once

#include "Entropy.h"

namespace tpp {
	
	// I(X;Y) = H(X) - H(X|Y)
	// I(X;Y) = H(Y) - H(Y|X)
	// Compute mutual information from probability transition matrix
	// and I/O probability distribution vector
	double mutualInformation(const DistributionMatrix& dm, 
		const Vec<double>& p, const Unit unit = tpp::Unit::BITS);

	// I(X;Y) = H(X) + H(Y) - H(X,Y)
	// Compute mutual information from a joint distribution X_Y
	double mutualInformation(const DistributionMatrix& X_Y, 
		const Unit unit = tpp::Unit::BITS);

}