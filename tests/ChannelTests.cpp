#include "pch.h"

#include "Information/DMCCapacity.h"
#include "Types.h"

namespace {
	const double EPSILON = 1e-4;
}

TEST(ChannelTest, ShannonEntropy) {
	double entropy = tpp::shannonEntropy({ 0.1, 0.2, 0.3, 0.4 });
	EXPECT_NEAR(entropy, 1.84644, EPSILON);
}

TEST(ChannelTest, DistributionMatrixManipulation) {
    // Setup DistributionMatrix
    tpp::DistributionMatrix dm;
    tpp::Vec2D<double> distr = { {0.2, 0.2}, {0.4, 0.2} };
    dm.setDistribution(distr);

    // Perform operations
    dm /= 10;
    tpp::Vec<double> h = dm.getMarginalDistributionH();
    tpp::Vec<double> v = dm.getMarginalDistributionV();
    h *= 2;
    v *= 10;

    // Assertions
    EXPECT_NEAR(h[0], 0.08, EPSILON);
    EXPECT_NEAR(h[1], 0.12, EPSILON);
    EXPECT_NEAR(v[0], 0.6, EPSILON);
    EXPECT_NEAR(v[1], 0.4, EPSILON);
}

TEST(ChannelTest, EntropyCalculations) {
    tpp::Vec2D<double> distr = { {2. / 9, 1. / 9}, {1. / 15, 3. / 5} };
    tpp::DistributionMatrix dm(distr);

    // Entropy Calculations
    tpp::Vec<double> px1 = dm.getMarginalDistributionH();
    EXPECT_NEAR(tpp::shannonEntropy(px1), 0.918296, EPSILON);
    EXPECT_NEAR(tpp::conditionalEntropyYX(dm), 0.618762, EPSILON);
    EXPECT_NEAR(tpp::conditionedEntropyYx(dm, 0), 0.918296, EPSILON);
    EXPECT_NEAR(tpp::conditionedEntropyYx(dm, 1), 0.468996, EPSILON);
    EXPECT_NEAR(tpp::conditionalEntropyXY(dm), 0.669777, EPSILON);
    EXPECT_NEAR(tpp::jointEntropyXY(dm), 1.53706, EPSILON);

    // Mutual Information Calculations
    EXPECT_NEAR(tpp::mutualInformation(dm), 0.248519, EPSILON);

    tpp::Vec2D<double> Q = { {2. / 3, 1. / 3}, {1. / 10, 9. / 10} };
    tpp::Vec<double> px = { 1. / 3, 2. / 3 };
    tpp::DistributionMatrix txDm(Q);
    EXPECT_NEAR(tpp::mutualInformation(txDm, px), 0.248519, EPSILON);

    tpp::Vec<double> py = { 13. / 45, 32. / 45 };
    tpp::DistributionMatrix txDmBackward{ dm / py };
    EXPECT_NEAR(tpp::mutualInformation(txDmBackward, py), 0.248519, EPSILON);

    // Entropy Calculation without Joint Distribution
    EXPECT_NEAR(tpp::conditionalEntropyYX(Q, px), 0.618762, EPSILON);
}

TEST(ChannelTest, DMCChannelCapacity) {
    tpp::Vec2D<double> Q = { {2. / 3, 1. / 3}, {1. / 10, 9. / 10} };
    tpp::Vec<double> px = { 1. / 3, 2. / 3 };
    tpp::DistributionMatrix dm{ Q };
    tpp::DMCChannelCapacity cap{ dm, px, 1, tpp::Unit::BITS };

    EXPECT_NEAR(cap.computeChannelCapacity(), 0.267645, EPSILON);
    EXPECT_NEAR(cap.getSourceInformationSpeed(), 0.918296, EPSILON);
}


TEST(ChannelTest, BSCChannel) {
    double e = 0.2;
    tpp::Vec2D<double> Q = { {1 - e, e}, {e, 1 - e} };
    tpp::Vec<double> px = { 0.3, 0.7 };
    tpp::DistributionMatrix dm{ Q };
    tpp::DMCChannelCapacity cap{ dm, px, 1, tpp::Unit::BITS };

    EXPECT_NEAR(cap.computeChannelCapacity(), 0.278072, EPSILON);
    EXPECT_NEAR(cap.getSourceInformationSpeed(), 0.881291, EPSILON);
}

TEST(ChannelTest, BECChannel) {
    double e = 0.1;
    tpp::Vec2D<double> Q = { {1 - e, e, 0}, {0, e, 1 - e} };
    tpp::Vec<double> px = { 0.3, 0.7 };
    tpp::DistributionMatrix dm{ Q };
    tpp::DMCChannelCapacity cap{ dm, px, 1, tpp::Unit::BITS };

    EXPECT_NEAR(cap.computeChannelCapacity(), 0.9, EPSILON);
    EXPECT_NEAR(cap.getSourceInformationSpeed(), 0.881291, EPSILON);
}