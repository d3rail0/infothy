#include "channeltest.h"

using namespace tpp;

void tpp::test1() {
	std::cout << tpp::shannonEntropy({ 0.1, 0.2, 0.3, 0.4 }) << std::endl;
}

void tpp::test2() {
	// tpp::tests for DistributionMatrix
	DistributionMatrix dm;

	Vec2D<double> distr = {
		{0.2, 0.2},
		{0.4, 0.2}
	};

	dm.setDistribution(distr);

	std::cout << dm << std::endl;

	//dm /= {10, 100};
	dm /= 10;

	std::cout << dm << std::endl;


	Vec<double> h = dm.getMarginalDistributionH();
	Vec<double> v = dm.getMarginalDistributionV();


	h *= 2;
	v *= 10;

	printVec(h);
	printVec(v);

}

void tpp::test3() {
	tpp::Vec2D<double> distr = {
		{2. / 9, 1. / 9},
		{1. / 15, 3. / 5}
	};

	tpp::DistributionMatrix dm(distr);

	tpp::Vec<double> px1 = dm.getMarginalDistributionH();

	std::cout << "H(X) = " << tpp::shannonEntropy(px1) << std::endl;
	std::cout << "H(Y|X) = " << tpp::conditionalEntropyYX(dm) << std::endl;
	std::cout << "H(Y|x = 0) = " << tpp::conditionedEntropyYx(dm, 0) << std::endl;
	std::cout << "H(Y|x = 1) = " << tpp::conditionedEntropyYx(dm, 1) << std::endl << std::endl;

	std::cout << "H(X|Y) = " << tpp::conditionalEntropyXY(dm) << std::endl;
	std::cout << "H(X, Y) = " << tpp::jointEntropyXY(dm) << std::endl << std::endl;

	std::cout << "I(X;Y) = H(X) + H(Y) - H(X,Y) = " << tpp::mutualInformation(dm) << std::endl;

	tpp::Vec2D<double> Q = {
		{2. / 3, 1. / 3},
		{1. / 10, 9. / 10}
	};

	tpp::Vec<double> px = { 1. / 3, 2. / 3 };
	tpp::Vec<double> py = { 13. / 45, 32. / 45 };

	tpp::DistributionMatrix txDm(Q);

	std::cout << "I(X;Y) = H(Y) - H(Y|X) = " << tpp::mutualInformation(txDm, px) << std::endl;

	tpp::DistributionMatrix txDmBackward{ dm / py };

	std::cout << "I(X;Y) = H(X) - H(X|Y) = " << tpp::mutualInformation(txDmBackward, py) << std::endl;


	std::cout << std::endl << "Entropies without join distribution" << std::endl;



	std::cout << "H(Y|X) = " << tpp::conditionalEntropyYX(Q, px) << std::endl;


}

void tpp::test4() {
	tpp::Vec2D<double> Q = {
		{2. / 3, 1. / 3},
		{1. / 10, 9. / 10}
	};

	tpp::Vec<double> px = { 1. / 3, 2. / 3 };

	// Forward probability transition matrix
	tpp::DistributionMatrix dm{ Q };

	tpp::DMCChannelCapacity cap{ dm, px, 1 };

	std::cout << std::endl;
	std::cout << "C = " << cap.computeChannelCapacity() << std::endl;
	std::cout << "Rx = " << cap.getSourceInformationSpeed() << std::endl;

}

// BSC
void tpp::test5() {
	double e = 0.2;

	tpp::Vec2D<double> Q = {
		{1 - e, e},
		{e, 1 - e}
	};

	tpp::Vec<double> px = { 0.3, 0.7 };

	// Forward probability transition matrix
	tpp::DistributionMatrix dm{ Q };

	tpp::DMCChannelCapacity cap{ dm, px, 1 };

	std::cout << "[BSC] C = " << cap.computeChannelCapacity() << std::endl;
	std::cout << "[BSC] Rx = " << cap.getSourceInformationSpeed() << std::endl;
}

// BEC
void tpp::test6() {
	double e = 0.1;

	tpp::Vec2D<double> Q = {
		{1 - e, e, 0},
		{0, e, 1 - e}
	};

	tpp::Vec<double> px = { 0.3, 0.7 };

	// Forward probability transition matrix
	tpp::DistributionMatrix dm{ Q };

	tpp::DMCChannelCapacity cap{ dm, px, 1 };

	std::cout << "[BEC] C = " << cap.computeChannelCapacity() << std::endl;
	std::cout << "[BEC] Rx = " << cap.getSourceInformationSpeed() << std::endl;
}