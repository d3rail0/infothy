#pragma once

#include "SourceCoder.hpp"

namespace tpp {

	class HuffmanCode : public SourceCoder{
	private:
		std::shared_ptr<Node> _huffmanTreeRoot;
		
		/*Creates a huffman tree and assigns the root node
		to _huffmanTreeRoot.*/
		void createTree(const sfd& symProb);

		/*Creates a Symbol -> Code map and assigns it
		to _symbolTable.*/	
		void createSymbolTable(std::shared_ptr<Node> currNode, std::string code);

	public:

		HuffmanCode() : SourceCoder{}, _huffmanTreeRoot{ nullptr } {}

		std::string decode(const st& symbolTable, const std::string& encodedStr) override;

		void genSymbolTableFrom(const sf& symbolFreq) override;
		void genSymbolTableFrom(const sfd& symProb) override;

	};

}