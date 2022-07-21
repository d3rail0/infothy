#pragma once

#include "SourceCoder.hpp"

namespace tpp {

	class ShannonFano : public SourceCoder {
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

		ShannonFano() : SourceCoder{}, _tree{ nullptr } {}

		std::string decode(const st& symbolTable, const std::string& encodedStr) override;

		void genSymbolTableFrom(const sf& symbolFreq) override;
		void genSymbolTableFrom(const sfd& symProb) override;

	};

}