#include "CommChannel.h"

using namespace tpp;

double tpp::mutualInformation(const DistributionMatrix& dm, const Vec<double>& p, bool isFwdTransMatrix, const Unit unit)
{
	DistributionMatrix jointDistr{ dm };

	if (isFwdTransMatrix)
		jointDistr *= p;
	else {
		jointDistr.transpose();
		jointDistr *= p;
		jointDistr.transpose();
	}


	return mutualInformation(jointDistr);
}

double tpp::mutualInformation(const DistributionMatrix& X_Y, const Unit unit)
{
	Vec<double> srcProbVec = X_Y.getMarginalDistributionH();
	Vec<double> outProbVec = X_Y.getMarginalDistributionV();
	return shannonEntropy(srcProbVec, unit) + shannonEntropy(outProbVec, unit) - jointEntropyXY(X_Y, unit);
}
