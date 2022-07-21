#include "SourceCoder.hpp"

using namespace tpp;

sfd tpp::SourceCoder::convertFreqToProb(const sf& symbolFreq) const
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

std::string tpp::SourceCoder::decode(const st& symbolTable, const std::string& encodedStr)
{
	std::string decoded{}, temp{};

	for (size_t i = 0; i < encodedStr.size(); ++i) {

		for (const auto& codewordItem : _symbolTable) {
			// Check if there is any codeword that matches 
			// current stream of symbols of length equal
			// to the codeword length.
			if (i + codewordItem.second.size() <= encodedStr.size()) {

				temp = encodedStr.substr(i, codewordItem.second.size());

				if (temp == codewordItem.second) {
					// The following code matches the codeword
					decoded += codewordItem.first;
					i += codewordItem.second.size() - 1;
					break;
				}

			}
		}

	}

	return decoded;
}

double tpp::SourceCoder::getWeightedPathLen() const
{
	auto term = [this](double a, const std::pair<char, double>& b)
	{
		return a + b.second * _symbolTable.at(b.first).size();
	};
	return std::accumulate(_inputProbs.begin(), _inputProbs.end(), 0.0, term);
}

double tpp::SourceCoder::getTransmissionSpeed(double symbols_per_sec) const
{
	return getWeightedPathLen() * symbols_per_sec;
}

double tpp::SourceCoder::getSingleSymbolDuration(double symbols_per_sec) const
{
	return 1.0 / getTransmissionSpeed(symbols_per_sec);
}

double tpp::SourceCoder::getSourceEntropy() const
{
	std::vector<double> probs{};
	std::transform(_inputProbs.begin(), _inputProbs.end(), std::back_inserter(probs), [](const std::pair<char, double>& item) {
		return item.second;
		});
	return shannonEntropy(probs);
}

double tpp::SourceCoder::getCodeEfficacy() const
{
	return getSourceEntropy() / getWeightedPathLen();
}

