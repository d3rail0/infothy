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

namespace tpp {

	using st = std::unordered_map<char, std::string>;
	using sf = std::unordered_map<char, int>;
	using sfd = std::unordered_map<char, double>;

	class HuffmanCode {
	private:

		struct NodeCompare {

			bool operator()(std::shared_ptr<Node> l, std::shared_ptr<Node> r)
			{
				return l->frequency > r->frequency;
			}
		};

		std::shared_ptr<Node> _huffmanTreeRoot;
		st _symbolTable;

		/*
			Creates a huffman tree and assigns the root node
			to _huffmanTreeRoot.
		*/
		void createTree(const sfd& symProb);


		/*
			Creates a Symbol -> Code map and assigns it
			to _symbolTable.
		*/
		void createSymbolTable(std::shared_ptr<Node> currNode, std::string code);

		sfd convertFreqToProb(const sf& symbolFreq) const;

	public:

		HuffmanCode() : _symbolTable{}, _huffmanTreeRoot{ nullptr } {}

		std::string encode(const std::string& text);

		void genSymbolTableFrom(const sf& symbolFreq);
		void genSymbolTableFrom(const sfd& symProb);
		
		std::string decode(const st& symbolTable, const std::string& text);

		const st& getSymbolTable() const {
			return _symbolTable;
		}

		// Computes average length of a codeword
		double getWeightedPathLen() const;

		// Computes average amount of bits per second 
		// that get transfered through the channel 
		// given the average amount of symbols per second.
		double getTransmissionSpeed(double symbols_per_sec) const;


	};

}