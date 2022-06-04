#pragma once

#include "entropy.h"

namespace tpp {
	
	// I(X;Y) = H(X) - H(X|Y)
	// Compute mutual information from forward probability transition matrix
	// and source probability distribution vector
	double mutualInformationXY(const DistributionMatrix& XY, 
		const Vec<double>& X, const Unit unit = tpp::Unit::BITS);

	// I(X;Y) = H(Y) - H(Y|X)
	// Compute mutual information from backward probability transition matrix
	// and output probability distribution vector
	double mutualInformationYX(const DistributionMatrix& YX, 
		const Vec<double>& Y, const Unit unit = tpp::Unit::BITS);

	// I(X;Y) = H(X) + H(Y) - H(X,Y)
	// Compute mutual information from a joint distribution X_Y
	double mutualInformation(const DistributionMatrix& X_Y, 
		const Unit unit = tpp::Unit::BITS);

	// Compute information speed of source or output

	// Compute channel capacity

}