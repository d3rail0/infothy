#pragma once
#include <vector>
#include "DistrMatrix.h"
#include "Information/Entropy.h"
#include "Information/DMCCapacity.h"

namespace tpp {

	struct DMCSolution {

		Unit unit = Unit::BITS;

		// Amount of information per symbol
		// Self-information
		Vec<double> _srcSelfInfo;
		Vec<double> _outSelfInfo;

		// Entropies
		double H_X   = 0.0;
		double H_Y   = 0.0;
		double H_Y_X = 0.0;
		double H_X_Y = 0.0;
		double H_XY  = 0.0;

		// Mutual information
		double I_XY = 0.0;

		// Capacity
		double C = 0.0;

		// Source information speed
		double Rx = 0.0;
	};

	class DMCSolver {
	private:

		// P(X,Y) or P(X|Y) or P(Y|X) matrix
		DistributionMatrix _mat;

		// Input/Output probability distribution vector
		Vec<double> _p;

		bool _isFwdTransMat	  = false;
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

		DMCSolution solve(const Unit unit = Unit::BITS) const;

		friend std::ifstream& operator>>(std::ifstream& ifs, DMCSolver& solver);

	};

	std::ifstream& operator>>(std::ifstream& ifs, DMCSolver& solver);
	std::ostream& operator<<(std::ostream& os, const DMCSolution& s);
}