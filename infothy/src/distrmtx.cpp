#include "distrmtx.h"

using namespace tpp;

tpp::DistributionMatrix::DistributionMatrix(const Vec2D<double>& distr)
{
	setDistribution(distr);
}

double tpp::DistributionMatrix::getMarginalProbabilityByCol(size_t col) const
{
	double result = 0.0;
	for (const auto& row : _distribution) {
		result += row[col];
	}
	return result;
}

double tpp::DistributionMatrix::getMarginalProbabilityByRow(size_t row) const 
{
	return std::accumulate(_distribution.at(row).begin(), _distribution.at(row).end(), 0.0);
}

void tpp::DistributionMatrix::setDistribution(const Vec2D<double>& newDistribution)
{
	if (newDistribution.size() > 0) 
		_colCount = newDistribution[0].size();
	else
		_colCount = 0;

	for (size_t i = 1; i < newDistribution.size(); i++) {
		if (newDistribution[i].size() != newDistribution[i - 1].size()) {
			throw std::logic_error("Two rows must not have different row sizes");
		}
	}

	_distribution = newDistribution;

}

Vec<double> tpp::DistributionMatrix::getMarginalDistributionH() const
{
	Vec<double> out(_distribution.size());

	for (size_t i = 0; i < _distribution.size(); ++i)
		out[i] = getMarginalProbabilityByRow(i);

	return out;
}

Vec<double> tpp::DistributionMatrix::getMarginalDistributionV() const
{
	Vec<double> out(_distribution[0].size());

	for (size_t i = 0; i < _distribution.size(); ++i)
		for (size_t j = 0; j < _distribution[i].size(); ++j)
			out[j] += _distribution[i][j];

	return out;
}

DistributionMatrix& tpp::DistributionMatrix::operator*=(const Vec<double>& px)
{
	if (size() != px.size()) 
		throw std::invalid_argument("Probability distribution vector must have same amount of elements as there are rows in probability distribution matrix");
	
	DistributionMatrix dm{ *this };

	for (size_t i = 0; i < size(); ++i) {
		dm._distribution[i] *= px[i];
	}

	return *this = std::move(dm);
}

DistributionMatrix& tpp::DistributionMatrix::operator*=(double scalar)
{
	for (auto& row : _distribution) {
		for (auto& p : row) {
			p *= scalar;
		}
	}
	return *this;
}

DistributionMatrix tpp::operator*(const DistributionMatrix& dm, const Vec<double>& px)
{
	DistributionMatrix ret(dm);
	ret *= px;
	return ret;
}

DistributionMatrix tpp::operator*(const Vec<double>& px, const DistributionMatrix& dm)
{
	return dm * px;
}

DistributionMatrix tpp::operator*(const DistributionMatrix& dm, double scalar)
{
	DistributionMatrix ret(dm);
	ret *= scalar;
	return ret;
}

DistributionMatrix tpp::operator*(double scalar, const DistributionMatrix& dm)
{
	return dm * scalar;
}

std::ostream& tpp::operator<<(std::ostream& os, const DistributionMatrix& dm)
{
	for (size_t i = 0; i < dm.size(); ++i) {		
		for (size_t j = 0; j < dm.sizeCols(); ++j) {
			os << dm(i, j) << " ";
		}
		os << std::endl;
	}

	return os;
}
