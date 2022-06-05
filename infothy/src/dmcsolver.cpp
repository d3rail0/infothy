#include "dmcsolver.h"

using namespace tpp;

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