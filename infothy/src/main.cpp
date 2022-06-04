#include <iostream>
#include <string>
#include "Information/commchannel.h"

void printVec(const tpp::Vec<double>& vec) {
	std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<double>{ std::cout, ", " });
	std::cout << std::endl;
}

void test1() {
	std::cout << tpp::shannonEntropy({ 0.1, 0.2, 0.3, 0.4 }) << std::endl;
}

void test2() {
	// Tests for DistributionMatrix
	tpp::DistributionMatrix dm;

	tpp::Vec2D<double> distr = {
		{0.2, 0.2},
		{0.4, 0.2}
	};

	dm.setDistribution(distr);

	std::cout << dm << std::endl;
	
	//dm /= {10, 100};
	dm /= 10;

	std::cout << dm << std::endl;

	
	tpp::Vec<double> h = dm.getMarginalDistributionH();
	tpp::Vec<double> v = dm.getMarginalDistributionV();


	h *= 2;
	v *= 10;

	std::cout << h << std::endl;
	std::cout << v << std::endl;

	//printVec(dm.getMarginalDistributionH());

	//printVec(dm.getMarginalDistributionV());

}

void test3() {
	tpp::Vec2D<double> distr = {
		{2./9, 1./9},
		{1. / 15, 3./5}
	};

	tpp::DistributionMatrix dm(distr);

	std::cout << "H(Y|X) = " << tpp::conditionalEntropyYX(dm) << std::endl;
	std::cout << "H(Y|x = 0) = " << tpp::conditionedEntropyYx(dm, 0) << std::endl;
	std::cout << "H(Y|x = 1) = " << tpp::conditionedEntropyYx(dm, 1) << std::endl << std::endl;

	std::cout << "H(X|Y) = " << tpp::conditionalEntropyXY(dm) << std::endl;
	std::cout << "H(X, Y) = " << tpp::jointEntropyXY(dm) << std::endl << std::endl;

	std::cout << "I(X;Y) = H(X) + H(Y) - H(X,Y) = " << tpp::mutualInformation(dm) << std::endl;

	/*
	std::cout << "I(X;Y) = H(X) - H(X|Y) = " << tpp::mutualInformationXY(dm, {}) << std::endl;
	std::cout << "I(X;Y) = H(Y) - H(Y|X) = " << tpp::mutualInformation(dm) << std::endl;*/
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		// Arguments were expected
		// return 1;
	}
	
	// Improve performance, since we arne't using C-style I/O (printf, scanf)
	std::ios_base::sync_with_stdio(false);

	test1();
	test2();
	test3();
}