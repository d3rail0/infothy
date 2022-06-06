#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "Types.h"

namespace tpp {
	
	class DistributionMatrix {
	private:

		Vec2D<double> _distribution;
		size_t _colCount = 0;

		void testRowIndex(size_t row) const {
			if (row < 0 || row >= _distribution.size()) {
				throw std::out_of_range("Row index is out of range");
			}
		}

		void testColIndex(size_t col) const { 
			if (col < 0 || col >= sizeCols()) {
				throw std::out_of_range("Col index is out of range");
			}
		}


	public:

		DistributionMatrix() {}
		DistributionMatrix(const Vec2D<double>& distr);
		DistributionMatrix(size_t rowCount, size_t colCount) 
			: _distribution(rowCount, Vec<double>(colCount, 0.0)), 
			_colCount{ colCount } {}

		double getMarginalProbabilityByCol(size_t col) const;
		double getMarginalProbabilityByRow(size_t row) const;
		
		const Vec<double>& operator[](size_t row) const {
			testRowIndex(row);
			return _distribution[row];
		}

		const Vec<double>& operator()(size_t row) const {
			testRowIndex(row);
			return _distribution[row];
		}

		const double& operator()(size_t row, size_t col) const {
			testColIndex(col);
			return (*this)(row)[col];
		}
		
		double& operator()(size_t row, size_t col) {
			testRowIndex(row);
			testColIndex(col);
			return _distribution[row][col];
		}

		// Gets raw distribution matrix
		const Vec2D<double>& getDistribution() const {
			return _distribution;
		}

		// Sets raw distribution matrix
		void setDistribution(const Vec2D<double>& newDistribution);

		// Gets marginal distribution vector by each row (Horizontal)
		Vec<double> getMarginalDistributionH() const;

		// Geets marginal distribution vector by each column (Vertical)
		Vec<double> getMarginalDistributionV() const;

		size_t size() const {
			return _distribution.size();
		}

		// Returns total number of columns in the distribution
		size_t sizeCols() const {
			return _colCount;
		}

		void transpose();

		// Multiplies each row in matrix by scalar from px[i]
		// where "i" is equal to index of row that it is multiplying
		DistributionMatrix& operator*=(const Vec<double>& px);
		friend DistributionMatrix operator*(const DistributionMatrix& dm, const Vec<double>& px);
		friend DistributionMatrix operator*(const Vec<double>& px, const DistributionMatrix& dm);

		// Multiplies each cell by scalar
		DistributionMatrix& operator*=(double scalar);
		friend DistributionMatrix operator*(const DistributionMatrix& dm, double scalar);
		friend DistributionMatrix operator*(double scalar, const DistributionMatrix& dm);

		// Divide each row in matrix by scalar from px[i]
		// where "i" is equal to an index row that it is dividing
		DistributionMatrix& operator/=(const Vec<double>& px);
		friend DistributionMatrix operator/(const DistributionMatrix& dm, const Vec<double>& px);
		friend DistributionMatrix operator/(const Vec<double>& px, const DistributionMatrix& dm);

		// Divides each cell by scalar
		DistributionMatrix& operator/=(double scalar);
		friend DistributionMatrix operator/(const DistributionMatrix& dm, double scalar);
		friend DistributionMatrix operator/(double scalar, const DistributionMatrix& dm);

		// I/O
		friend std::ostream& operator<<(std::ostream& os, const DistributionMatrix& dm);

		friend std::ifstream& operator>>(std::ifstream& os, DistributionMatrix& dm);
	};

	tpp::DistributionMatrix operator*(const tpp::DistributionMatrix& dm, const tpp::Vec<double>& px);
	tpp::DistributionMatrix operator*(const tpp::Vec<double>& px, const tpp::DistributionMatrix& dm);
	tpp::DistributionMatrix operator*(const tpp::DistributionMatrix& dm, double scalar);
	tpp::DistributionMatrix operator*(double scalar, const tpp::DistributionMatrix& dm);

	DistributionMatrix operator/(const DistributionMatrix& dm, const Vec<double>& px);
	DistributionMatrix operator/(const Vec<double>& px, const DistributionMatrix& dm);
	DistributionMatrix operator/(const DistributionMatrix& dm, double scalar);
	DistributionMatrix operator/(double scalar, const DistributionMatrix& dm);

	std::ostream& operator<<(std::ostream& os, const tpp::DistributionMatrix& dm);
	std::ifstream& operator>>(std::ifstream& os, DistributionMatrix& dm);
}