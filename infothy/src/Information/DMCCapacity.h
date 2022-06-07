#pragma once

#include "CommChannel.h"

namespace tpp {

	// Blahut-Arimoto algorithm configuration
	struct BAConfig {
		size_t maxIterations = std::numeric_limits<size_t>::max();
		double epsilon = 1e-4;
	};

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

		// Max symbol speed through channel
		// also known as "Capacity"
		double _capacity = -1.0;

		// Blahut-Arimoto configuration
		BAConfig _baConfig;

		TermComputor TC{ Unit::NATS };
		Unit _outputUnit;

		// Helper methods
		// ---------------------

		// Computes source information speed from
		// real source probability distribution
		void computeSourceInformationSpeed() {
			_srcInfoSpeed = _symbolSpeed * shannonEntropy(_p, TC.getUnit());
			/*_srcInfoSpeed = _symbolSpeed * mutualInformation(_Q, _p, TC.getUnit());*/
		}

		// Initialize the prior uniformly
		void setSrcDistrUniform() {
			std::transform(_p.begin(), _p.end(), _p.begin(), [this](double&) {
				return 1.0 / this->_p.size();
			});
		}

		// Blahut-Arimoto algorithm
		// ----------------------------------
		
		// right most term in c_j
		double calc_Qkj_fract(size_t j, size_t k);

		double calc_cj_sum(size_t j);

		// Computes and updates capacity vector
		void calcCapVec();

		double calc_I_L();

		double calc_I_U() {
			return myLog(*std::max_element(_c.begin(), _c.end()), TC.getUnit());
		}

		// Update source probability distribution
		// to prepare it for the next iteration in the algorithm
		void update_px();

		void computeCapacity();

		// ----------------------------------

		// ---------------------

	public:

		DMCChannelCapacity(const DistributionMatrix& Q, const Vec<double>& px, double symbolSpeed, const Unit outputUnit)
			: _symbolSpeed{ symbolSpeed }, _outputUnit(outputUnit) {
			setTransitionMatrix(Q, px);
		}

		void setTransitionMatrix(const DistributionMatrix& Q, const Vec<double>& px);

		const DistributionMatrix& getTransitionMatrix() const {
			return _Q;
		}

		const Vec<double>& getCapacityVector() const {
			return _c;
		}

		const Vec<double>& getSrcProbDistr() const {
			return _p;
		}

		// Returns source symbol speed
		double getSymbolSpeed() const {
			return _symbolSpeed;
		}

		// Returns source information speed in specified output unit
		double getSourceInformationSpeed() {
			// Divide here in case user changes only output unit and then wants
			// to see result in the new unit.
			return _srcInfoSpeed / std::log(unitToBase(_outputUnit));
		}

		// Returns -1.0 if capacity hasn't been calculated yet
		// otherwise it will return a positive number
		double getChannelCapacity() const {
			return _capacity / std::log(unitToBase(_outputUnit));
		}

		// Executes algorithm for capacity computation
		// and returns channel capacity once it's done
		double computeChannelCapacity() {
			computeCapacity();
			return getChannelCapacity();
		}

		// Returns Blahut-Arimoto algorithm configuration
		// which can then be updated if needed before computing
		// the capacity again.
		BAConfig& getBAConfig() {
			return _baConfig;
		}

		Unit getOutputUnit() const {
			return _outputUnit;
		}

		void setOutputUnit(Unit unit) {
			_outputUnit = unit;
		}

	};

}