#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include "TreeNode.hpp"
#include <stdexcept>
#include <queue>
#include <algorithm>
#include <numeric>
#include <functional>

namespace tpp {

	using st = std::unordered_map<char, std::string>;
	using sf = std::unordered_map<char, int>;
	using sfd = std::unordered_map<char, double>;

	class ISourceCoder {
	protected:
		
		struct NodeCompare {

			bool operator()(std::shared_ptr<Node> l, std::shared_ptr<Node> r)
			{
				return l->probability > r->probability;
			}
		};

		ISourceCoder() {}

		// Converts integer frequencies to decimal probabilities 0 <= p(x) <= 1
		sfd convertFreqToProb(const sf& symbolFreq) const;

		st _symbolTable;
		sfd _inputProbs;

	public:

		virtual ~ISourceCoder() {}

		virtual std::string encode(const std::string& text) = 0;
		virtual std::string decode(const st& symbolTable, const std::string& text) = 0;

		virtual void genSymbolTableFrom(const sf& symbolFreq) = 0;
		virtual void genSymbolTableFrom(const sfd& symProb) = 0;

		const st& getSymbolTable() const {
			return _symbolTable;
		}

		const sfd& getInputProbabilites() const {
			return _inputProbs;
		}

		// Computes average length of a codeword
		double getWeightedPathLen() const;

		// Computes average amount of bits per second 
		// that get transfered through the channel 
		// given the average amount of symbols per second.
		double getTransmissionSpeed(double symbols_per_sec) const;

		double getSingleSymbolDuration(double symbols_per_sec) const;

	};

}