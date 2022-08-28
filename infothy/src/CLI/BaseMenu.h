#pragma once

#include <iostream>
#include <string>
#include <memory>

namespace tpp {

	using namespace std::string_literals;

	class BaseMenu {
	protected:
		std::string _menuText;

		BaseMenu() {}

	public:

		virtual ~BaseMenu() {}

		virtual std::unique_ptr<BaseMenu> getNextMenu(int choice, bool& isQuit, bool& isBack) = 0;

		virtual void printText() {
			std::cout << _menuText << std::endl;
		}

	};

}