#pragma once

#include "BaseMenu.h"
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <filesystem>

namespace tpp {

	class DMCSFileInputMenu : public BaseMenu {
	private:

		bool _isAllFilesListed;

		void setStartingMenu() {
			_isAllFilesListed = false;
			_menuText =
				"Choose a file\n"s
				+ "1 - Go back\n"
				+ "2 - By name\n"
				+ "3 - List all files\n"
				+ "4 - Quit\n"
				+ "Option:";
			std::vector<std::string>().swap(_foundFiles);
		}

		void listAllFiles();

		std::vector<std::string> _foundFiles;

	public:

		DMCSFileInputMenu() {
			setStartingMenu();
		}

		std::unique_ptr<BaseMenu> getNextMenu(int option, bool& isQuit, bool& isBack) override;

	};

}