#include "utils.h"

using namespace tpp;


double tpp::myLog(const double arg, const Unit unit) {
	switch (unit) {
	case Unit::BITS:
		return std::log2(arg);
	case Unit::NITS:
		return std::log(arg);
	case Unit::BANS:
		return std::log10(arg);
	}
	throw std::exception("Unit specified not supported by myLog()");
}