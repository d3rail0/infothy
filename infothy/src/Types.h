#pragma once

#include <vector>
#include <valarray>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace tpp {

	template<typename T>
	using Vec = std::vector<T>;

	template<typename T>
	using Vec2D = Vec<Vec<T>>;

	enum class Unit {
		BITS = 0,
		NATS,
		BANS
	};

	static const char* UNIT_STR[] = { "BITS", "NATS", "BANS" };

	template<typename T>
	auto printVec(const Vec<T>& vec, std::ostream& os = std::cout) -> decltype(os) {
		os << '{';

		auto i = std::begin(vec);
		auto e = std::end(vec);

		if (i != e) {
			os << *i;
			while (++i != e)
				os << ", " << *i;
		}

		os << '}';
		return os;
	}

	/*template<typename T>
	void printMatrix(const Vec2D<T>& mat, std::ostream& os = std::cout) {
	}*/

	template <typename T>
	std::ifstream& operator>>(std::ifstream& ifs, Vec<T>& vec) {
		char ch;
		std::string line;

		// Read any string / vector name
		if (ifs >> line) {

			if (!(ifs >> ch && ch == '=')) {
				ifs.setstate(std::ios_base::failbit);
				return ifs;
			}

			// Read array of doubles
			std::getline(ifs, line);
			std::istringstream iss(line);

			T d;
			while (iss >> d) {
				vec.push_back(d);
			}

		}

		return ifs;
	}

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