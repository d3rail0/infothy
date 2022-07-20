#pragma once

#include "SourceCoder.hpp"

namespace tpp {

	class HuffmanCode : public ISourceCoder{
	private:
		std::shared_ptr<Node> _huffmanTreeRoot;
		
		/*Creates a huffman tree and assigns the root node
		to _huffmanTreeRoot.*/
		void createTree(const sfd& symProb);

		/*Creates a Symbol -> Code map and assigns it
		to _symbolTable.*/	
		void createSymbolTable(std::shared_ptr<Node> currNode, std::string code);

	public:

		HuffmanCode() : ISourceCoder{}, _huffmanTreeRoot{ nullptr } {}

		std::string encode(const std::string& text) override;
		std::string decode(const st& symbolTable, const std::string& text) override;

		void genSymbolTableFrom(const sf& symbolFreq) override;
		void genSymbolTableFrom(const sfd& symProb) override;

	};

}