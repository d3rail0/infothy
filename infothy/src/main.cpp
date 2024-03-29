#include <iostream>
#include <string>
#include <stack>
#include "DMCSolver.h"
#include "UI/MainMenu.h"

int main(int argc, char* argv[]) {

	if (argc < 2) {
		// Arguments were expected
		// return 1;
	}

	// Improve performance, since we arne't using C-style I/O (printf, scanf)
	std::ios_base::sync_with_stdio(false);

	std::cout << "infothy v0.1" << std::endl;
	std::cout << "=======================\n\n";

	std::stack<std::unique_ptr<tpp::BaseMenu>> menus;
	menus.push(std::make_unique<tpp::MainMenu>());

	bool shouldQuit = false;
	bool isGoBack = false;

	while (!shouldQuit && !menus.empty()) {

		menus.top()->printText();

		int choice = 0;

		if (std::cin >> choice) {
			
			try {
				auto newMenu = menus.top()->getNextMenu(choice, shouldQuit, isGoBack);

				if (isGoBack) {
					menus.pop();
					isGoBack = false;
				}
				else if (newMenu != nullptr)
					menus.push(std::move(newMenu));
			}
			catch (std::exception& ex) {
				std::cout << "There was an error: " << ex.what() << std::endl;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << std::endl;
	}


	return 0;
}