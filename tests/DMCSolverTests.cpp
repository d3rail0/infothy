#include "pch.h"
#include <fstream>
#include <string>

#include "DMCSolver.h"

class DMCSolverTest : public ::testing::Test {
protected:

	tpp::DMCSolver getSolverForFile(const std::string& filename) {
		tpp::DMCSolver dmcs;

		std::ifstream fs("./input/" + filename);

		if (!fs) {
			throw std::runtime_error("File failed to load");
		}

		fs >> dmcs;
		return dmcs;
	}

	const double EPSILON = 1e-4;

};

TEST_F(DMCSolverTest, BinaryErasureChannel) {
	tpp::DMCSolver solver;
	ASSERT_NO_THROW({
			solver = getSolverForFile("z1.txt");
	}, std::runtime_error);

	ASSERT_FLOAT_EQ(solver.getIOVec().at(0), 0.3);
	ASSERT_FLOAT_EQ(solver.getIOVec().at(1), 0.7);

	tpp::DMCSolution sol = solver.solve();

	EXPECT_NEAR(sol._srcSelfInfo[0], 1.73697, EPSILON);
	EXPECT_NEAR(sol._srcSelfInfo[1], 0.514573, EPSILON);

	EXPECT_NEAR(sol._outSelfInfo[0], 1.88897, EPSILON);
	EXPECT_NEAR(sol._outSelfInfo[1], 3.32193, EPSILON);
	EXPECT_NEAR(sol._outSelfInfo[2], 0.666576, EPSILON);

	EXPECT_NEAR(sol.H_X, 0.881291, EPSILON);
	EXPECT_NEAR(sol.H_Y, 1.26216, EPSILON);
	EXPECT_NEAR(sol.H_Y_X, 0.468996, EPSILON);
	EXPECT_NEAR(sol.H_X_Y, 0.0881291, EPSILON);
	EXPECT_NEAR(sol.H_XY, 1.35029, EPSILON);
	EXPECT_NEAR(sol.I_XY, 0.793162, EPSILON);
	EXPECT_NEAR(sol.C, 0.9, EPSILON);
	EXPECT_NEAR(sol.Rx, 0.881291, EPSILON);
}

TEST_F(DMCSolverTest, JointProbabiltyDistrInput) {
	tpp::DMCSolver solver;
	ASSERT_NO_THROW({
		solver = getSolverForFile("z2.txt");
	});

	EXPECT_TRUE(solver.getIOVec().empty());

	tpp::DMCSolution sol = solver.solve();

	EXPECT_NEAR(sol._srcSelfInfo[0], 1.58511, EPSILON);
	EXPECT_NEAR(sol._srcSelfInfo[1], 0.58489, EPSILON);

	EXPECT_NEAR(sol._outSelfInfo[0], 1.79136, EPSILON);
	EXPECT_NEAR(sol._outSelfInfo[1], 0.491876, EPSILON);

	EXPECT_NEAR(sol.H_X, 0.918262, EPSILON);
	EXPECT_NEAR(sol.H_Y, 0.867296, EPSILON);
	EXPECT_NEAR(sol.H_Y_X, 0.618842, EPSILON);
	EXPECT_NEAR(sol.H_X_Y, 0.669809, EPSILON);
	EXPECT_NEAR(sol.H_XY, 1.5371, EPSILON);
	EXPECT_NEAR(sol.I_XY, 0.248454, EPSILON);
	EXPECT_NEAR(sol.C, 0.267588, EPSILON);
	EXPECT_NEAR(sol.Rx, 0.918262, EPSILON);
}

TEST_F(DMCSolverTest, InputProbabilityDistr) {
	tpp::DMCSolver solver;
	ASSERT_NO_THROW({
		solver = getSolverForFile("z3.txt");
		});

	for (double val : solver.getIOVec()) {
		ASSERT_FLOAT_EQ(val, 0.1);
	}

	tpp::DMCSolution sol = solver.solve();

	for (int i = 0; i < 10; ++i) {
		EXPECT_NEAR(sol._srcSelfInfo[i], 3.32193, EPSILON);
		EXPECT_NEAR(sol._outSelfInfo[i], 3.32193, EPSILON);
	}

	EXPECT_NEAR(sol.H_X, 3.32193, EPSILON);
	EXPECT_NEAR(sol.H_Y, 3.32193, EPSILON);
	EXPECT_NEAR(sol.H_Y_X, 3.32193, EPSILON);
	EXPECT_NEAR(sol.H_X_Y, 3.32193, EPSILON);
	EXPECT_NEAR(sol.H_XY, 6.64386, EPSILON);
	EXPECT_NEAR(sol.I_XY, 0.0, EPSILON);
	EXPECT_NEAR(sol.C, 0.0, EPSILON);
	EXPECT_NEAR(sol.Rx, 3.32193, EPSILON);
}

TEST_F(DMCSolverTest, OutputProbabilityDistr) {
	tpp::DMCSolver solver;
	ASSERT_NO_THROW({
		solver = getSolverForFile("z4.txt");
		});

	ASSERT_FLOAT_EQ(solver.getIOVec().at(0), 0.28889);
	ASSERT_FLOAT_EQ(solver.getIOVec().at(1), 0.71111);

	tpp::DMCSolution sol = solver.solve();

	EXPECT_NEAR(sol._srcSelfInfo[0], 1.58496, EPSILON);
	EXPECT_NEAR(sol._srcSelfInfo[1], 0.58497, EPSILON);

	EXPECT_NEAR(sol._outSelfInfo[0], 1.79142, EPSILON);
	EXPECT_NEAR(sol._outSelfInfo[1], 0.491855, EPSILON);

	EXPECT_NEAR(sol.H_X, 0.918299, EPSILON);
	EXPECT_NEAR(sol.H_Y, 0.867282, EPSILON);
	EXPECT_NEAR(sol.H_Y_X, 0.618754, EPSILON);
	EXPECT_NEAR(sol.H_X_Y, 0.669771, EPSILON);
	EXPECT_NEAR(sol.H_XY, 1.53705, EPSILON);
	EXPECT_NEAR(sol.I_XY, 0.248528, EPSILON);
	EXPECT_NEAR(sol.C, 0.26765, EPSILON);
	EXPECT_NEAR(sol.Rx, 0.918299, EPSILON);
}