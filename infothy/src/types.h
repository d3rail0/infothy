#pragma once

#include <vector>
#include <valarray>
#include <algorithm>
#include <iostream>

namespace tpp {

	template<typename T>
	using Vec = std::vector<T>;

	template<typename T>
	using Vec2D = Vec<Vec<T>>;

	enum class Unit {
		BITS,
		NATS,
		BANS
	};

	template<typename T>
	void printVec(const Vec<T>& vec, std::ostream& os = std::cout) {
		std::copy(std::cbegin(vec), std::cend(vec), std::ostream_iterator<T>{ os, ", " });
		os << std::endl;
	}

	/*template<typename T>
	void printMatrix(const Vec2D<T>& mat, std::ostream& os = std::cout) {
	}*/

}


template<typename T>
inline tpp::Vec<T>& operator*=(tpp::Vec<T>& vec, double scalar) {
	std::transform(
		vec.begin(), vec.end(),
		vec.begin(), [&scalar](double p) -> double {
			return p * scalar;
		}
	);
	return vec;
}

template<typename T>
inline tpp::Vec<T>& operator/=(tpp::Vec<T>& vec, double scalar) {
	std::transform(
		vec.begin(), vec.end(),
		vec.begin(), [&scalar](double p) -> double {
			return p / scalar;
		}
	);
	return vec;
}