#pragma once

#include "DMCSolutionMenu.h"
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <filesystem>
#include <limits>

namespace tpp {

	class DMCSFileInputMenu : public BaseMenu {
	private:

		bool _isAllFilesListed;

		void setStartingMenu();
		void listAllFiles();
		void loadAllFiles();

		std::vector<std::string> _foundFiles;

	public:

		DMCSFileInputMenu() {
			setStartingMenu();
		}

		std::unique_ptr<BaseMenu> getNextMenu(int option, bool& isQuit, bool& isBack) override;

	};

}