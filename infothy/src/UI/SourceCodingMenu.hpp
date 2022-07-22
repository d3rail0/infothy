#pragma once

#include "../Information/Coding/Huffman.hpp"
#include "../Information/Coding/ShannonFano.hpp"
#include "BaseMenu.h"

namespace tpp {

	class SourceCodingMenu : public BaseMenu {
	private:

		enum class MenuState {
			DEFAULT,
			INPUT,
			RESULTS
		};

		MenuState _state;
		std::unique_ptr<SourceCoder> _sc = nullptr;

		void setDefaultMenu() {
			_state = MenuState::DEFAULT;
			_menuText = "# Source coding menu\n"s
				+ "Select the algorithm\n"
				+ "1 - Go back\n"
				+ "2 - Huffman\n"
				+ "3 - Shannon-Fano\n"
				+ "4 - Quit\n"
				+ "Option:";
		}

		void setCodingMenu() {
			_state = MenuState::INPUT;
			_menuText = "# Source coding menu\n"s
				+ "Set input to encode\n"
				+ "1 - Go back\n"
				+ "2 - Text\n"
				+ "3 - Frequency table\n"
				+ "4 - Probability table\n"
				+ "Option:";
		}

		void setResultInfoMenu() {
			_state = MenuState::RESULTS;
			_menuText = "# Source coding menu\n"s
				+ "Results menu\n"
				+ "1 - Go back\n"
				+ "2 - Show symbol table\n"
				+ "3 - Weighted path length\n"
				+ "4 - Source entropy\n"
				+ "5 - Code efficacy\n"
				+ "6 - Get transmission speed\n"
				+ "7 - Symbol rate\n"
				+ "8 - Display all at once\n"
				+ "Option:";
		}

		void handleCodingMenu(int option);
		void handleResultInfoMenu(int option);

		template<typename T>
		requires (std::is_arithmetic<T>::value)
		std::unordered_map<char, T> encodeFromTableInput() {
			int symbolCount = 0;

			std::cout << "How many symbols do you want to enter: ";
			std::cin >> symbolCount;

			if (symbolCount < 1) 
				throw std::runtime_error("Symbol count cannot be less than 1");
			

			char ch;
			T fp;
			std::unordered_map<char, T> table;

			for (size_t i = 1; i <= symbolCount; ++i) {
				std::cout << "Symbol " << i << ": ";
				std::cin >> ch;
				std::cout << "Frequency: ";
				std::cin >> fp;

				if constexpr (std::is_floating_point<T>::value) {
					if (fp < .0 || fp > 1.0)
						std::cin.setstate(std::ios_base::failbit);					
				}
				else {
					if (fp < 0) 
						std::cin.setstate(std::ios_base::failbit);					
				}

				if (!std::cin) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					--i;
					continue;
				}

				table[ch] = fp;
			}

			return table;
		}

	public:
		SourceCodingMenu() {
			setDefaultMenu();
		}

		std::unique_ptr<BaseMenu> getNextMenu(int option, bool& isQuit, bool& isBack) override;

	};

}