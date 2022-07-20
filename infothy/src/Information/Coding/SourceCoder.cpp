#include "SourceCoder.hpp"

using namespace tpp;

sfd tpp::ISourceCoder::convertFreqToProb(const sf& symbolFreq) const
{
	sfd symbolProb = {};

	int totalFreq = 0;

	for (const auto& item : symbolFreq) {
		totalFreq += item.second;
	}

	for (const auto& item : symbolFreq) {
		symbolProb[item.first] = static_cast<double>(item.second) / totalFreq;
	}

	return symbolProb;
}

double tpp::ISourceCoder::getWeightedPathLen() const
{
	auto term = [this](double a, const std::pair<char, double>& b)
	{
		return a + b.second * _symbolTable.at(b.first).size();
	};
	return std::accumulate(_inputProbs.begin(), _inputProbs.end(), 0.0, term);
}

double tpp::ISourceCoder::getTransmissionSpeed(double symbols_per_sec) const
{
	return getWeightedPathLen() * symbols_per_sec;
}

double tpp::ISourceCoder::getSingleSymbolDuration(double symbols_per_sec) const
{
	return 1.0 / getTransmissionSpeed(symbols_per_sec);
}


