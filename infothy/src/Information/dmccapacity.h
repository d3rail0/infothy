#pragma once

#include "commchannel.h"

namespace tpp {

	class DMCChannelCapacity {
	private:

		// Forward probability transiton matrix
		DistributionMatrix _Q;

		// Capacity vector
		Vec<double> _c;

		// Source probability distribution
		Vec<double> _p;

		// Source symbol speed
		double _symbolSpeed;

		// Source information speed
		double _srcInfoSpeed;

		// Helper methods
		// ---------------------

		// Computes source information speed from
		// real source probability distribution
		void computeSourceInformationSpeed() {
			_srcInfoSpeed = _symbolSpeed * mutualInformation(_Q, _p, Unit::BANS);
		}

		// ---------------------

	public:

		DMCChannelCapacity(const DistributionMatrix& Q, const Vec<double>& px, double symbolSpeed) 
			: _symbolSpeed{ symbolSpeed } {
			setTransitionMatrix(Q, px);
		}

		void setTransitionMatrix(const DistributionMatrix& Q, const Vec<double>& px) {
			Vec<double>().swap(_c);
			Vec<double>().swap(_p);
			

			if (px.size() != Q.size())
				throw std::logic_error("Source probability distribution vector size not equal to amount of rows in transition matrix.");
			
			_c = Vec<double>(Q.size());
			_p = px;

			computeSourceInformationSpeed();

			// Create a uniform distribution for source
			std::transform(_p.begin(), _p.end(), _p.begin(), [&Q](double&) {
				return 1.0 / Q.size();
			});

		}

		const DistributionMatrix& getTransitionMatrix() const {
			return _Q;
		}

		const Vec<double>& getCapacityVector() const {
			return _c;
		}

		const Vec<double>& getSrcProbDistr() const {
			return _p;
		}

		double getSymbolSpeed() const {
			return _symbolSpeed;
		}

		double getSourceInformationSpeed() {
			return _srcInfoSpeed;
		}

	};

}