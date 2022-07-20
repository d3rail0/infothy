#include "Huffman.hpp"

using namespace tpp;

void tpp::HuffmanCode::createTree(const sfd& symProb)
{

	_huffmanTreeRoot = nullptr;

	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeCompare> minheap;

	// Create leave nodes
	for (const auto& item : symProb)
		minheap.push(Node::create(item.first, item.second));


	std::shared_ptr<Node> left, right, temp;

	while (minheap.size() != 1) {


		// Get two nodes with lowest frequencies

		left = minheap.top();
		minheap.pop();

		right = minheap.top();
		minheap.pop();

		// Create a brand new node with the frequencies summed up

		temp = Node::create(0, left->frequency + right->frequency);
		temp->left = left;
		temp->right = right;

		minheap.push(temp);
	}

	_huffmanTreeRoot = minheap.top();

}

void tpp::HuffmanCode::createSymbolTable(std::shared_ptr<Node> currNode, std::string code)
{
	if (!currNode)
		return;

	if (currNode->isInternal() == false) {
		_symbolTable[currNode->symbol] = code;
		return;
	}

	createSymbolTable(currNode->left, code + "0");
	createSymbolTable(currNode->right, code + "1");
}

sfd tpp::HuffmanCode::convertFreqToProb(const sf& symbolFreq) const
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

std::string tpp::HuffmanCode::encode(const std::string& text)
{

	std::unordered_map<char, int> freqTable {};

	// Compute frequencies
	for (const auto& c : text)
		++freqTable[c];

	createTree(convertFreqToProb(freqTable));
	_symbolTable.clear();
	createSymbolTable(_huffmanTreeRoot, "");

	// Encode each char in original tex with the code
	std::string result = "";

	for (const auto& c : text)
		result += _symbolTable[c];

	return result;
}

void tpp::HuffmanCode::genSymbolTableFrom(const sf& symbolFreq)
{
	createTree(convertFreqToProb(symbolFreq));
	_symbolTable.clear();
	createSymbolTable(_huffmanTreeRoot, "");
}

void tpp::HuffmanCode::genSymbolTableFrom(const sfd& symProb)
{
	createTree(symProb);
	_symbolTable.clear();
	createSymbolTable(_huffmanTreeRoot, "");
}

std::string tpp::HuffmanCode::decode(const st& symbolTable, const std::string& text)
{
	return std::string();
}
