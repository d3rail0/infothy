#pragma once

#include "SourceCoder.hpp"

namespace tpp {

	class ShannonFano : public ISourceCoder {
	private:

		using pyQueue = std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeCompare<false>>;

		std::shared_ptr<Node> _tree;

		void createTreeFromQueue(std::shared_ptr<Node> parent, pyQueue queue);

		/*Creates a shannon fano tree and assigns the root node
		to _tree.*/
		void createTree(const sfd& symProb);

		/*Creates a Symbol -> Code map and assigns it
		to _symbolTable.*/
		void createSymbolTable(std::shared_ptr<Node> currNode, std::string code);

	public:

		ShannonFano() : ISourceCoder{}, _tree{ nullptr } {}

		std::string encode(const std::string& text) override;
		std::string decode(const st& symbolTable, const std::string& encodedStr) override;

		void genSymbolTableFrom(const sf& symbolFreq) override;
		void genSymbolTableFrom(const sfd& symProb) override;

	};

}
/*
	0.25
	0.25
	0.125
	0.125
	0.125
	0.125

	lsum = 0.25 

	l: 0.25 -  (1 - 0.25) = 0.25 - 0.75 = -0.5 * -1 = 0.5
	d: 0.25 + 0.25 - (1 - (0.25 + 0.25)) = 0.5 - (1 - 0.5) = 0.5 - 0.5 = 0

	0.5 nije manje od 0

	lsum = 0.5 

	l: 0.5 - (1 - 0.5) = 0.5 - 0.5 = 0
	d: 0.5 + 0.125 - (1 - (0.5 + 0.125)) = 0.25

	0 < 0.25 --> Push to left queue
	

*/