#include "MainMenu.h"

using namespace tpp;

std::unique_ptr<BaseMenu> tpp::MainMenu::getNextMenu(int option, bool& isQuit, bool& isBack)
{
    std::unique_ptr<BaseMenu> menu = nullptr;

    switch (option) {
    case 1:
        menu = std::make_unique<DMCSolverMenu>();
        break;
    case 2:
        isQuit = true;
        break;
    default:
        break;
    }

    return menu;
}
