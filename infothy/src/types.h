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
		NITS,
		BANS
	};

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

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const tpp::Vec<T>& vec) {
	std::copy(std::cbegin(vec), std::cend(vec), std::ostream_iterator<T>{ os, ", " });
	return os;
}