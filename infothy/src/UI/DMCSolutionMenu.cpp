#include "DMCSolutionMenu.h"

using namespace tpp;

void tpp::DMCSolutionMenu::setDefaultMenu()
{

	_choosingUnit = false;

	_menuText =
		"DMC Solution Menu\n"s
		+ "# Active file: " + _inputFileName + "\n"
		+ "-------\n"
		+ "1 - Go back\n"
		+ "2 - Print I/O vector\n"
		+ "3 - Print distribution matrix\n"
		+ "4 - Solve from input\n"
		+ "Option:";

}

void tpp::DMCSolutionMenu::setChooseUnitMenu()
{
	_choosingUnit = true;
	
	_menuText = "Choose unit:\n"s;

	std::stringstream ss;
	for (size_t i = 0; i < sizeof(UNIT_STR)/sizeof(char*); ++i)
		ss << i + 1 << " - " << UNIT_STR[i] << std::endl;
	ss << "Option: ";

	_menuText += ss.str();
}



void tpp::DMCSolutionMenu::printIOVec()
{
	char vecName = '*';

	if (!_solver->isJointDistrMat()) {
		if (_solver->isFwdTransMat()) {
			vecName = 'X';
		}
		else {
			vecName = 'Y';
		}
	}
	else {
		std::cout << "I/O vector was not found!" << std::endl;
		return;
	}

	std::cout << std::endl;
	std::cout << vecName << " = ";
	printVec(_solver->getIOVec());
	std::cout << std::endl;
}

void tpp::DMCSolutionMenu::printDistributionMat()
{

	std::string matType = "P(X,Y)";

	if (!_solver->isJointDistrMat()) {
		if (_solver->isFwdTransMat()) {
			matType = "P(Y|X)";
		}
		else {
			matType = "P(X|Y)";
		}
	}

	std::cout << std::endl;
	std::cout << "# " << matType << std::endl;
	std::cout << std::string(25, '-') << std::endl;
	std::cout << _solver->getDistrMat();
	std::cout << std::string(25, '-') << std::endl;
}

void tpp::DMCSolutionMenu::solveFromInput(int option)
{

	if (!_choosingUnit) {
		setChooseUnitMenu();
		return;
	}

	if (option < 1 || option > sizeof(UNIT_STR) / sizeof(char*))
		return;
	
	auto chosenUnit = static_cast<Unit>(option - 1);

	DMCSolution solution = _solver->solve(chosenUnit);
	std::cout << std::endl;
	std::cout << std::string(25, '*') << std::endl;
	std::cout << solution << std::endl;
	std::cout << std::string(25, '*') << std::endl;

	setDefaultMenu();
	
}

tpp::DMCSolutionMenu::DMCSolutionMenu(const std::string& inputFileName)
{
	_inputFileName = inputFileName;
	setDefaultMenu();
	
	std::ifstream ifs(inputFileName);

	if (!ifs) {
		throw std::exception("File failed to load");
	}

	_solver = std::make_unique<DMCSolver>();
	ifs >> *_solver;
}

std::unique_ptr<BaseMenu> tpp::DMCSolutionMenu::getNextMenu(int option, bool& isQuit, bool& isBack)
{

	if (_choosingUnit) {
		solveFromInput(option);
		return nullptr;
	}

	switch (option) {
	case 1:
		isBack = true;
		break;
	case 2: 
		printIOVec();
		break;
	case 3:
		printDistributionMat();
		break;
	case 4:
		solveFromInput(option);
		break;
	default:
		break;
	}

	// There are no following menus, so we just return nullptr;
	return nullptr;
}
