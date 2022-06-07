#include "DMCSFileInputMenu.h"

using namespace tpp;
namespace fs = std::filesystem;

void tpp::DMCSFileInputMenu::listAllFiles()
{
    _isAllFilesListed = true;
	_menuText =
		"Choose a file\n"s
		+ "1 - Go back\n"
		+ "2 - Quit\n";
	

	std::string filename = "";
	size_t ctr = 3;
	std::stringstream ss;
	for (auto const& dir_entry : fs::recursive_directory_iterator("./input/"))
	{
		filename = fs::path(dir_entry).stem().string();
		_foundFiles.push_back(filename);
		ss << ctr++ << " - " << filename << '\n';
	}

	if (_foundFiles.size() == 0) {
		_menuText += "<No files found>\n";
	}
	else {
		_menuText += ss.str();
	}

}

std::unique_ptr<BaseMenu> tpp::DMCSFileInputMenu::getNextMenu(int option, bool& isQuit, bool& isBack)
{
	std::unique_ptr<BaseMenu> nextMenu = nullptr;

	if (_isAllFilesListed) {
		switch (option) {
		case 0:
			break;
		case 1:
			setStartingMenu();
			break;
		case 2:
			isQuit = true;
			break;
		default: {

			if (option > _foundFiles.size() + 2)
				break;
			
			// Load final stage with results

			break;
		}
		}
	}
	else {
		switch (option) {
			case 1:
				isBack = true;
				break;
			case 2:

				break;
			case 3:		
				listAllFiles();
				break;
			case 4:
				isQuit = true;
				break;
			default:
				break;
			}
	}


	return nextMenu;
}
