#include "SrcCodingTest.h"

using namespace tpp;


void printSymbolTable(const ISourceCoder& sc) {

	std::cout << "============" << std::endl;

	for (const auto& item : sc.getSymbolTable()) {
		std::cout << item.first << " -> " << item.second << std::endl;
	}

	std::cout << "============" << std::endl;
}

void printCodingInfo(const ISourceCoder& sc) {
	
	printSymbolTable(sc);
	std::cout << "Weighted path length: " << sc.getWeightedPathLen() << " [bit/symbol]" << std::endl;
	std::cout << "Transmission speed (for 400 symbol/s): " << sc.getTransmissionSpeed(400) << " [bit/s]" << std::endl;
	std::cout << "Single symbol duration (for 400 symbol/s): " << sc.getSingleSymbolDuration(400) << " [s]" << std::endl;

	std::cout << std::endl;
}

void tpp::HuffmanTest1()
{
	std::cout << "Test 1" << std::endl;

	HuffmanCode hc;

	std::string encoded = hc.encode("AAAAABCCCCCCCCCCCCCCCCCCCCDEFGH");
	std::cout << "Encoded text: " << encoded << std::endl;

	printCodingInfo(hc);

}

void tpp::HuffmanTest2()
{

	std::cout << "Test 2" << std::endl;

	HuffmanCode hc;

	sf symFreqs = {};
	symFreqs['1'] = 42;
	symFreqs['2'] = 24;
	symFreqs['3'] = 12;
	symFreqs['4'] = 10;
	symFreqs['5'] = 10;
	symFreqs['6'] = 2;

	hc.genSymbolTableFrom(symFreqs);

	printCodingInfo(hc);

}

void tpp::HuffmanTest3()
{

	std::cout << "Test 3" << std::endl;

	HuffmanCode hc;

	sfd symFreqs = {};
	symFreqs['1'] = 0.42;
	symFreqs['2'] = 0.24;
	symFreqs['3'] = 0.12;
	symFreqs['4'] = 0.10;
	symFreqs['5'] = 0.10;
	symFreqs['6'] = 0.02;

	hc.genSymbolTableFrom(symFreqs);

	printCodingInfo(hc);

}
