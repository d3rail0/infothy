#include "SourceCodingMenu.hpp"

using namespace tpp;

void tpp::SourceCodingMenu::handleCodingMenu(int option)
{
    
    switch (option) {
    case 1:
        setDefaultMenu();
        return;
    case 2: {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter text: ";
        std::string input;
        std::getline(std::cin, input);

        _sc->encode(input);
 
        break;
    }
    case 3: {
        std::cout << "## Enter symbols and their frequencies" << std::endl;
        _sc->genSymbolTableFrom(encodeFromTableInput<int>());
        break;
    }
    case 4: {
        std::cout << "## Enter symbols and their probabilites" << std::endl;
        _sc->genSymbolTableFrom(encodeFromTableInput<double>());
        break;
    }
    default:
        return;       
    }

    setResultInfoMenu();
}

void h_ShowSymbolTable(const SourceCoder& sc) {

    std::cout << "-------------" << std::endl;

    for (const auto& item : sc.getSymbolTable()) 
        std::cout << item.first << " -> " << item.second << std::endl;

    std::cout << "-------------" << std::endl;
    
}

void h_ShowTransmissionSpeed(const SourceCoder& sc) {
    std::cout << "Enter number of symbols / sec: ";
    double sypsec;
    std::cin >> sypsec;
    std::cout << sc.getTransmissionSpeed(sypsec);
}

void h_ShowSymbolRate(const SourceCoder& sc) {
    std::cout << "Enter number of symbols / sec: ";
    double sypsec;
    std::cin >> sypsec;
    std::cout << sc.getSingleSymbolDuration(sypsec);
}

void tpp::SourceCodingMenu::handleResultInfoMenu(int option)
{

    switch (option) {
    case 1:
        setCodingMenu();
        break;
    case 2:
        h_ShowSymbolTable(*_sc);
        break;
    case 3:
        std::cout << "L = " << _sc->getWeightedPathLen() << std::endl;
        break;
    case 4:
        std::cout << "H(X) = " << _sc->getSourceEntropy() << std::endl;
        break;
    case 5:
        std::cout << "Code efficacy = " << _sc->getCodeEfficacy() * 100 << " %" << std::endl;
        break;
    case 6:
        h_ShowTransmissionSpeed(*_sc);
        break;
    case 7:
        h_ShowSymbolRate(*_sc);
        break;
    case 8:
        h_ShowSymbolTable(*_sc);
        std::cout << "L = " << _sc->getWeightedPathLen() << std::endl;
        std::cout << "H(X) = " << _sc->getSourceEntropy() << std::endl;
        std::cout << "Code efficacy = " << _sc->getCodeEfficacy() * 100 << " %" << std::endl;
        break;
    default:
        break;
    }

}

std::unique_ptr<BaseMenu> tpp::SourceCodingMenu::getNextMenu(int option, bool& isQuit, bool& isBack)
{
    std::unique_ptr<BaseMenu> menu = nullptr;

    switch (_state) {
        case MenuState::INPUT:
            handleCodingMenu(option);
            return nullptr;
            break;
        case MenuState::RESULTS:
            handleResultInfoMenu(option);
            return nullptr;
            break;
        default:
            break;
    }

    switch (option) {
    case 1:
        isBack = true;
        break;
    case 2:
        _sc = std::make_unique<HuffmanCode>();
        setCodingMenu();
        break;
    case 3:
        _sc = std::make_unique<ShannonFano>();
        setCodingMenu();
        break;
    case 4:
        isQuit = true;
        break;
    default:
        break;
    }

    return menu;
}
