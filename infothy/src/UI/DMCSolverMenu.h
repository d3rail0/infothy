#pragma once

#include "DMCSFileInputMenu.h"

namespace tpp {

	class DMCSolverMenu : public BaseMenu {
	public:

		DMCSolverMenu() {
			_menuText =
				"# DMC Solver Menu\n"s
				+ "1 - Go back\n"
				+ "2 - Read input probabilites from a file\n"
				+ "3 - Enter input manually\n"
				+ "4 - Quit\n"
				+ "Option:";
		}

		std::unique_ptr<BaseMenu> getNextMenu(int option, bool& isQuit, bool& isBack) override;

	};

}