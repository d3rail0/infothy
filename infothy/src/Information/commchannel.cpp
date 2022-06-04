#include "commchannel.h"

using namespace tpp;

double tpp::mutualInformationXY(const DistributionMatrix& XY, const Vec<double>& X, const Unit unit)
{
	return 0.0;
}

double tpp::mutualInformationYX(const DistributionMatrix& YX, const Vec<double>& Y, const Unit unit)
{
	return 0.0;
}

double tpp::mutualInformation(const DistributionMatrix& X_Y, const Unit unit)
{
	Vec<double> srcProbVec = X_Y.getMarginalDistributionH();
	Vec<double> outProbVec = X_Y.getMarginalDistributionV();
	return shannonEntropy(srcProbVec, unit) + shannonEntropy(outProbVec, unit) - jointEntropyXY(X_Y, unit);
}
