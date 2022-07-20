#pragma once
#include <memory>

namespace tpp {

	struct Node : std::enable_shared_from_this<Node> {

		std::shared_ptr<Node> getptr() {
			return shared_from_this();
		}

		[[nodiscard]] static std::shared_ptr<Node> create(char symbol, double freq) {
			return std::shared_ptr<Node>(new Node(symbol, freq));
		}

		// Can turn this into variant
		char symbol;
		double probability;

		std::shared_ptr<Node> left, right;

		void addNodeLeft(char symbol, double freq) {
			left = Node::create(symbol, freq);
		}

		void addNodeRight(char symbol, double freq) {
			right = Node::create(symbol, freq);
		}

		bool isInternal() const {
			return left || right;
		}

	private:
		Node(char symbol, double freq)
			: symbol{ symbol }, probability{ freq }, left(nullptr), right(nullptr) {}
	};

}