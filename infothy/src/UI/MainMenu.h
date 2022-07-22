#pragma once

#include "BaseMenu.h"
#include "DMCSolverMenu.h"
#include "SourceCodingMenu.hpp"

namespace tpp {

	class MainMenu : public BaseMenu {
	public:
		MainMenu() {
			_menuText = "# Main Menu\n"s
				+ "Choose solver mode\n"
				+ "1 - Discrete memoryless channel solver\n"
				+ "2 - Source coding\n"
				+ "3 - Quit\n"
				+ "Option:";				
		}

		std::unique_ptr<BaseMenu> getNextMenu(int option, bool& isQuit, bool& isBack) override;

	};

}