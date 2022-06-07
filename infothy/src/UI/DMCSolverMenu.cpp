#include "DMCSolverMenu.h"

using namespace tpp;

std::unique_ptr<BaseMenu> tpp::DMCSolverMenu::getNextMenu(int option, bool& isQuit, bool &isBack) {
	std::unique_ptr<BaseMenu> nextMenu = nullptr;

	switch (option) {
	case 1:
		isBack = true;
		break;
	case 2:
		nextMenu = std::make_unique<DMCSFileInputMenu>();
		break;
	case 3:
		break;
	case 4:
		isQuit = true;
		break;
	default:
		break;
	}

	return nextMenu;
}
