#pragma once
#include <vector>
#include "distrmtx.h"

namespace tpp {

	class DMCSolver {
	private:

		// Joint distribution
		DistributionMatrix _P_xy;

		// Forward transition matrix
		DistributionMatrix _Q;

		// Source probability distribution
		Vec<double> _p = {};

		// Output probability distribution
		Vec<double> _q = {};

		// Source symbol speed
		double Rs = 0.0;

	public:

		DMCSolver() {}

		/*
			Initializes the solver with source probability distribution 
			and forward transition matrix
		*/
		DMCSolver(const Vec<double>& srcProbDistr, const Vec2D<double>& transitionMat) 
			: _p{ srcProbDistr }, _Q{ transitionMat } {}

		/*
			Initializes the solver with joint probability distribution
		*/
		DMCSolver(const Vec2D<double>& jointDistr) : _P_xy(jointDistr) {}




	};

}