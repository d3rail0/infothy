#include "ShannonFano.hpp"

using namespace tpp;

void tpp::ShannonFano::createTreeFromQueue(std::shared_ptr<Node> parent, pyQueue secQueue)
{
	pyQueue primQueue {};

	double leftProbSum = 0.0;

	while (!secQueue.empty()) {

		if (std::abs(leftProbSum - (parent->probability - leftProbSum))
			< std::abs(leftProbSum + secQueue.top()->probability - (parent->probability - (leftProbSum + secQueue.top()->probability))))
			break;
		
		// Add node to left queue (i.e. zero queue)
		// and remove the node from the right queue
		leftProbSum += secQueue.top()->probability;
		primQueue.push(secQueue.top());
		secQueue.pop();

	}

	if (primQueue.size() == 1) {
		// There is only a single node in the "zeros" queue
		// Create a leaf node for it
		parent->left = primQueue.top();
	}
	else if(primQueue.size() > 1) {
		parent->left = Node::create(0, leftProbSum);
		createTreeFromQueue(parent->left, primQueue);
	}

	if (secQueue.size() == 1) {
		parent->right = secQueue.top();
	}
	else if (secQueue.size() > 1) {
		parent->right = Node::create(0, parent->probability - leftProbSum);
		createTreeFromQueue(parent->right, secQueue);
	}
}

void tpp::ShannonFano::createTree(const sfd& symProb)
{
	this->_inputProbs = symProb;
	pyQueue queue;

	_tree = Node::create(0, 1.0);

	for (const auto& item : symProb) {
		queue.push(Node::create(item.first, item.second));
	}

	createTreeFromQueue(_tree, queue);

}

void tpp::ShannonFano::createSymbolTable(std::shared_ptr<Node> currNode, std::string code)
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

std::string tpp::ShannonFano::encode(const std::string& text)
{
	return std::string();
}

std::string tpp::ShannonFano::decode(const st& symbolTable, const std::string& encodedStr)
{
	return std::string();
}

void tpp::ShannonFano::genSymbolTableFrom(const sf& symbolFreq)
{
}

void tpp::ShannonFano::genSymbolTableFrom(const sfd& symProb)
{
	createTree(symProb);
	_symbolTable.clear();
	createSymbolTable(_tree, "");
}


