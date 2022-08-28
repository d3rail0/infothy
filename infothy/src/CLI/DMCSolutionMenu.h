#pragma once

#include "BaseMenu.h"
#include "../DMCSolver.h"

namespace tpp {

	class DMCSolutionMenu : public BaseMenu {
	private:

		std::unique_ptr<DMCSolver> _solver;
		std::string _inputFileName;

		bool _choosingUnit;

		void setDefaultMenu();
		void setChooseUnitMenu();

		void printIOVec();
		void printDistributionMat();
		void solveFromInput(int option);


	public:

		DMCSolutionMenu(const std::string& inputFileName);

		std::unique_ptr<BaseMenu> getNextMenu(int option, bool& isQuit, bool& isBack) override;

	};

}