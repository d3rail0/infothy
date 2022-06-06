#include "DMCSolver.h"

using namespace tpp;


namespace {

	Vec<double> calcSelfInfoVec(Vec<double> vec, const Unit unit) {
		std::transform(vec.begin(), vec.end(), vec.begin(),
			[unit](double p) {
				return tpp::selfInformation(p, unit);
			});

		return vec;
	}

}

void tpp::DMCSolver::initialize(const Vec<double>& ioDistr, const DistributionMatrix& distrMat, bool isFwdTransMat) {
	if (distrMat.size() != ioDistr.size())
		throw std::domain_error("Input probability distributions doesn't cover all source symbols from a given distribution matrix");

	_mat = distrMat;
	_p = ioDistr;
	_isFwdTransMat = isFwdTransMat;
	_isJointDistrMat = false;
}

void tpp::DMCSolver::initialize(const DistributionMatrix& jointDistr) {
	_mat = jointDistr;
	Vec<double>().swap(_p);
	_isFwdTransMat = false;
	_isJointDistrMat = true;
}

bool tpp::DMCSolver::isValidTransitionMatrix() const
{
	if (_isJointDistrMat)
		return false;

	if (_isFwdTransMat) {
		// Check whether sum per each row is equal to 1
		for (const auto& px : _mat.getMarginalDistributionH())
			if (!AreSame(px, 1.0, 1e-4))
				return false;
	}
	else {
		// Check whether sum per each col is equal to 1
		for (const auto& py : _mat.getMarginalDistributionV())
			if (!AreSame(py, 1.0, 1e-4))
				return false;
	}

	return true;
}

DMCSolution tpp::DMCSolver::solve(const Unit unit) const
{
	DMCSolution solution;

	DistributionMatrix dmTemp{ _mat };

	// Convert transition matrix to joint distribution matrix
	if (!_isJointDistrMat) {
		if (!_isFwdTransMat) {
			// It's a backward transition matrix
			dmTemp.transpose();
			dmTemp *= _p;
			dmTemp.transpose();
		}
		else {
			dmTemp *= _p;
		}
	}

	solution.unit = unit;
	
	// From joint distribution matrix we can find all necessary values
	Vec<double> srcProbVec = dmTemp.getMarginalDistributionH();
	Vec<double> outProbVec = dmTemp.getMarginalDistributionV();
	
	// Self-information
	solution._srcSelfInfo = calcSelfInfoVec(srcProbVec, unit);
	solution._outSelfInfo = calcSelfInfoVec(outProbVec, unit);

	// Entropies
	solution.H_X   = tpp::shannonEntropy(srcProbVec, unit);
	solution.H_Y   = tpp::shannonEntropy(outProbVec, unit);
	solution.H_XY  = tpp::jointEntropyXY(dmTemp, unit);
	solution.H_Y_X = tpp::conditionalEntropyYX(dmTemp, unit);
	solution.H_X_Y = solution.H_XY - solution.H_Y;
	
	// Mutual info
	solution.I_XY = solution.H_Y - solution.H_Y_X;

	if (solution.I_XY < 0.0)
		solution.I_XY = 0.0;

	// Capacity
	DMCChannelCapacity cap(dmTemp / srcProbVec, srcProbVec, 1.0);
	solution.C = cap.computeChannelCapacity();

	// Source information speed
	solution.Rx = cap.getSourceInformationSpeed();

	return solution;
}

std::ifstream& tpp::operator>>(std::ifstream& ifs, DMCSolver& solver) {

	char ch;
	std::string line;
	Vec<double> p;
	DistributionMatrix dm;

	bool isFwd = false;

	while (ifs.good()) {
		ch = ifs.peek();
		if (ch == '#') {
			// It's a comment, skip this line
			std::getline(ifs, line);
			continue;
		}

		// it's an I/O distribution
		// read the following vector
		if (ch == 'I' || ch == 'i') {
			isFwd = true;
			ifs >> p;
		} else if (ch == 'O' || ch == 'o') {
			isFwd = false;
			ifs >> p;
		}
		
		ifs >> ch;

		if (std::isdigit(ch)) {
			// Read the distribution matrix
			ifs.unget();
			ifs >> dm;
		}
		else // Empty line probably, skip it.
			std::getline(ifs, line);
		
	}

	if (p.empty()) 
		solver.initialize(dm);
	else 
		solver.initialize(p, dm, isFwd);
	
	return ifs;
}

std::ostream& tpp::operator<<(std::ostream& os, const DMCSolution& s)
{

	std::string_view mUnit { ENTROPY_UNIT[static_cast<size_t>(s.unit)] };

	os << "Unit: " << UNIT_STR[static_cast<size_t>(s.unit)] << std::endl;
	os << "I(X) = "; printVec(s._srcSelfInfo, os) << std::endl;
	os << "I(Y) = "; printVec(s._outSelfInfo, os) << std::endl;

	os  << "H(X) = "	<< s.H_X	<< " " << mUnit << std::endl
		<< "H(Y) = "	<< s.H_Y	<< " " << mUnit << std::endl
		<< "H(Y|X) = "	<< s.H_Y_X	<< " " << mUnit << std::endl
		<< "H(X|Y) = "	<< s.H_X_Y	<< " " << mUnit << std::endl
		<< "H(X,Y) = "	<< s.H_XY	<< " " << mUnit << std::endl
		<< "I(X;Y) = "	<< s.I_XY	<< " " << mUnit << std::endl
		<< "C = "		<< s.C		<< " " << mUnit << "/cu" << std::endl
		<< "Rx = "		<< s.Rx		<< " " << mUnit << "/s";
 
	return os;
}
