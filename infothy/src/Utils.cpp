#include "Utils.h"

using namespace tpp;


double tpp::myLog(const double arg, const Unit unit) {
	switch (unit) {
	case Unit::BITS:
		return std::log2(arg);
	case Unit::NATS:
		return std::log(arg);
	case Unit::BANS:
		return std::log10(arg);
	}
	throw std::exception("Unit specified not supported by myLog()");
}

double tpp::unitToBase(const Unit unit)
{
	switch (unit) {
	case Unit::BITS:
		return 2;
	case Unit::NATS:
		return std::exp(1);
	case Unit::BANS:
		return 10;
	}
	return 0;
}
