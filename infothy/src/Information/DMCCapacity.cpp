#include "DMCCapacity.h"

using namespace tpp;

double tpp::DMCChannelCapacity::calc_Qkj_fract(size_t j, size_t k) {
	double sum = 0.0;
	for (size_t jj = 0; jj < _Q.size(); ++jj) {
		sum += _p[jj] * _Q[jj][k];
	}
	return _Q[j][k] / sum;
}

double tpp::DMCChannelCapacity::calc_cj_sum(size_t j) {
	double result = 0.0;
	for (size_t k = 0; k < _Q.sizeCols(); ++k) {
		result += TC(_Q[j][k], calc_Qkj_fract(j, k));
	}
	return result;
}

void tpp::DMCChannelCapacity::calcCapVec() {
	for (size_t j = 0; j < _c.size(); ++j) {
		_c[j] = std::exp(calc_cj_sum(j));
	}
}

double tpp::DMCChannelCapacity::calc_I_L() {
	double sum = 0.0;
	for (size_t j = 0; j < _Q.size(); ++j)
		sum += _p[j] * _c[j];

	// Avoid getting negative result
	sum = myLog(sum, TC.getUnit());
	return sum < 0.0 ? 0 : sum;
}

void tpp::DMCChannelCapacity::update_px() {
	double sum;
	for (size_t j = 0; j < _Q.size(); ++j) {
		sum = 0.0;

		for (size_t x = 0; x < _Q.size(); ++x)
			sum += _p[x] * _c[x];

		_p[j] *= _c[j] / sum;
	}
}

void tpp::DMCChannelCapacity::computeCapacity() {
	_c = Vec<double>(_Q.size());
	setSrcDistrUniform();
	double I_L = 0.0;
	for (size_t i = 0; i < _baConfig.maxIterations; ++i) {
		calcCapVec();

		if (calc_I_U() - (I_L = calc_I_L()) < _baConfig.epsilon) {
			_capacity = I_L / std::log(unitToBase(Unit::BITS));
			return;
		}

		update_px();

	}
}

void tpp::DMCChannelCapacity::setTransitionMatrix(const DistributionMatrix& Q, const Vec<double>& px) {
	if (px.size() != Q.size())
		throw std::logic_error("Source probability distribution vector size not equal to amount of rows in transition matrix.");

	_p = px;
	_capacity = -1.0;
	_Q = Q;

	computeSourceInformationSpeed();
}