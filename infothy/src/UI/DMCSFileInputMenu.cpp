#include "DMCSFileInputMenu.h"

using namespace tpp;
namespace fs = std::filesystem;

void tpp::DMCSFileInputMenu::setStartingMenu() {
	loadAllFiles();

	_isAllFilesListed = false;
	_menuText =
		"Choose a file\n"s
		+ "1 - Go back\n"
		+ "2 - By name\n"
		+ "3 - List all files\n"
		+ "4 - Quit\n"
		+ "Option:";
}

void tpp::DMCSFileInputMenu::listAllFiles()
{
	loadAllFiles();

    _isAllFilesListed = true;
	_menuText =
		"Choose a file\n"s
		+ "1 - Go back\n"
		+ "2 - Quit\n";
	

	std::stringstream ss;

	for (size_t i = 0; i < _foundFiles.size(); i++) {
		ss << i+3 << " - " << _foundFiles[i] << '\n';
	}

	if (_foundFiles.size() == 0) {
		_menuText += "<No files found>\n";
	}
	else {
		_menuText += ss.str();
	}

}

void tpp::DMCSFileInputMenu::loadAllFiles()
{
	std::vector<std::string>().swap(_foundFiles);
	for (auto const& dir_entry : fs::recursive_directory_iterator(this->INPUT_FOLDER_PATH))
		_foundFiles.push_back(fs::path(dir_entry).stem().string());
}

std::unique_ptr<BaseMenu> tpp::DMCSFileInputMenu::getNextMenu(int option, bool& isQuit, bool& isBack)
{
	std::unique_ptr<BaseMenu> nextMenu = nullptr;

	if (_isAllFilesListed) {
		switch (option) {
		case 1:
			setStartingMenu();
			break;
		case 2:
			isQuit = true;
			break;
		default: {

			if (option > _foundFiles.size() + 2 || option < 3)
				break;
			
			// Load final stage with results
			nextMenu = std::make_unique<DMCSolutionMenu>(this->INPUT_FOLDER_PATH + _foundFiles.at(option-3) + ".txt");

			break;
		}
		}
	}
	else {
		switch (option) {
			case 1:
				isBack = true;
				break;
			case 2: {
				std::string filename;

				std::cout << std::endl << "Enter input file name (without ext, Q - go back): ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, filename);
				auto it = std::find(_foundFiles.begin(), _foundFiles.end(), filename);

				if (it != _foundFiles.end()) {
					// Switch to final menu
					nextMenu = std::make_unique<DMCSolutionMenu>(this->INPUT_FOLDER_PATH + *it + ".txt");
				}
				else {
					std::cout << "File '" << filename << "' not found!" << std::endl;
				}

				break;
			}
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
