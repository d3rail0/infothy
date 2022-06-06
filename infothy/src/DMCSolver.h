#pragma once
#include <vector>
#include "DistrMatrix.h"

namespace tpp {

	class DMCSolver {
	private:

		// P(X,Y) or P(X|Y) or P(Y|X) matrix
		DistributionMatrix _mat;

		// Input/Output probability distribution vector
		Vec<double> _p;

		bool _isFwdTransMat = false;
		bool _isJointDistrMat = false;

	public:

		DMCSolver() {}

		/*
			Initializes the solver with source probability distribution 
			and forward transition matrix
		*/
		DMCSolver(const Vec<double>& ioDistr, const DistributionMatrix& distrMat, bool isFwdTransMat) {
			initialize(ioDistr, distrMat, isFwdTransMat);
		}

		/*
			Initializes the solver with joint probability distribution
		*/
		DMCSolver(const DistributionMatrix& jointDistr) {
			initialize(jointDistr);
		}


		void initialize(const Vec<double>& ioDistr, const DistributionMatrix& distrMat, bool isFwdTransMat);

		void initialize(const DistributionMatrix& jointDistr);


		bool isFwdTransMat() const {
			return _isFwdTransMat;
		}

		bool isJointDistrMat() const {
			return _isJointDistrMat;
		}

		const Vec<double>& getIOVec() const {
			return _p;
		}

		const DistributionMatrix& getDistrMat() const {
			return _mat;
		}

		friend std::ifstream& operator>>(std::ifstream& ifs, DMCSolver& solver);

	};

	std::ifstream& operator>>(std::ifstream& ifs, DMCSolver& solver);

}