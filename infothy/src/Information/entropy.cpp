#include "entropy.h"

using namespace tpp;

double tpp::shannonEntropy(const Vec<double>& input, const Unit unit) {
	double result = 0.0;
	for (const auto& p : input) {
		// Ensure that we don't compute log (0) --> (undefined)
		result += IsZero(p) ? 0 : p * myLog(p, unit);
	}
	return -result;
}

double tpp::conditionedEntropyYx(const DistributionMatrix& X_Y, size_t x, const Unit unit)
{
	//  H(Y|x) = Sum[ P(yj|x) * log (P(yj|x)) ]
	//	Where P(yj|x) = P(x, yj) / P(x)
	double result = 0.0;

	// We need marginal distribution for each column
	double marginalX = X_Y.getMarginalProbabilityByRow(x);

	if (IsZero(marginalX)) {
		// Marginal probability is zero, so
		// there is no point in iterating over each row
		return 0.0;
	}

	double p_Yx = 0.0;

	// Get distribution vector for x over all y
	auto row = X_Y[x];

	for (size_t i = 0; i < row.size(); ++i) {
		p_Yx = row[i] / marginalX;
		result += IsZero(p_Yx) ? 0 : p_Yx * myLog(p_Yx, unit);
	}

	return -result;
}

double tpp::conditionedEntropyXy(const DistributionMatrix& X_Y, size_t y, const Unit unit)
{
	//  H(X|y) = Sum[ P(xi|y) * log (P(xi|y)) ]
	//	Where P(xi|y) = P(xi, y) / P(y)
	double result = 0.0;

	// We need marginal distribution for each column
	double marginalY = X_Y.getMarginalProbabilityByCol(y);
	
	if (IsZero(marginalY)) {
		// Marginal probability is zero, so
		// there is no point in iterating over each row
		return 0.0;
	}

	double p_Xy = 0.0;
	for (const auto& row : X_Y.getDistribution()) {
		p_Xy = row[y] / marginalY;
		result += IsZero(p_Xy) ? 0 : p_Xy * myLog(p_Xy, unit);
	}

	return -result;
}

double tpp::conditionalEntropyYX(const DistributionMatrix& X_Y, const Unit unit)
{
	// H(Y|X) = Sum[ P(xi) * H(Y|xi) ]
	// Where H(Y|xi) is conditioned entropy
	double result = 0.0;

	// Compute marginal distribution vector over all y
	Vec<double> margX = X_Y.getMarginalDistributionH();

	for (size_t x = 0; x < X_Y.size(); ++x) {
		result += margX[x] * conditionedEntropyYx(X_Y, x, unit);
	}

	return result;
}

double tpp::conditionalEntropyXY(const DistributionMatrix& X_Y, const Unit unit)
{
	// H(X|Y) = Sum[ P(yj) * H(X|yj) ]
	// Where H(X|yj) is conditioned entropy
	double result = 0.0;

	// Compute marginal distribution vector over all x
	Vec<double> margY = X_Y.getMarginalDistributionV();
	
	for (size_t y = 0; y < X_Y.sizeCols(); ++y) {
		result += margY[y] * conditionedEntropyXy(X_Y, y, unit);
	}

	return result;
}

double tpp::jointEntropyXY(const DistributionMatrix& X_Y, const Unit unit)
{
	// H(X, Y) = Sum[ P(x,y) * log(P(x,y)) ]

	double result = 0.0;

	for (size_t x = 0; x < X_Y.size(); ++x) {
		for (size_t y = 0; y < X_Y[x].size(); ++y) {
			result += IsZero(X_Y[x][y]) ? 0 : X_Y[x][y] * myLog(X_Y[x][y], unit);
		}
	}

	return -result;
}

