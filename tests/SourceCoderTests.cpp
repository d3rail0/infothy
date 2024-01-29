#include "pch.h"
#include <string>

#include "Information/Coding/Huffman.hpp"
#include "Information/Coding/ShannonFano.hpp"
#include <cassert>

namespace {
    const double EPSILON = 1e-4;
}

TEST(SourceCoderTest, HuffmanTest1) {
    tpp::HuffmanCode hc;
    std::string inputText = "AAAAABCCCCCCCCCCCCCCCCCCCCDEFGH";
    std::string encoded = hc.encode(inputText);
    std::string decoded = hc.decode(hc.getSymbolTable(), encoded);

    EXPECT_EQ(inputText, decoded);

    EXPECT_NEAR(hc.getSourceEntropy(), 1.79135, EPSILON);
    EXPECT_NEAR(hc.getWeightedPathLen(), 1.87097, EPSILON);
    EXPECT_NEAR(hc.getCodeEfficacy(), 0.957446, EPSILON);
    EXPECT_NEAR(hc.getTransmissionSpeed(400), 748.387, EPSILON);
    EXPECT_NEAR(hc.getSingleSymbolDuration(400), 0.00133621, EPSILON);
}

TEST(SourceCoderTest, HuffmanTest2) {
    tpp::HuffmanCode hc;
    tpp::sf symFreqs = { {'1', 42}, {'2', 24}, {'3', 12}, {'4', 10}, {'5', 10}, {'6', 2} };
    hc.genSymbolTableFrom(symFreqs);

    EXPECT_NEAR(hc.getSourceEntropy(), 2.16411, EPSILON);
    EXPECT_NEAR(hc.getWeightedPathLen(), 2.26, EPSILON);
    EXPECT_NEAR(hc.getCodeEfficacy(), 0.957571, EPSILON);
    EXPECT_NEAR(hc.getTransmissionSpeed(400), 904, EPSILON);
    EXPECT_NEAR(hc.getSingleSymbolDuration(400), 0.00110619, EPSILON);
}

TEST(SourceCoderTest, HuffmanTest3) {
    tpp::HuffmanCode hc;
    tpp::sfd symFreqs = { {'1', 0.42}, {'2', 0.24}, {'3', 0.12}, {'4', 0.10}, {'5', 0.10}, {'6', 0.02} };
    hc.genSymbolTableFrom(symFreqs);

    EXPECT_NEAR(hc.getSourceEntropy(), 2.16411, EPSILON);
    EXPECT_NEAR(hc.getWeightedPathLen(), 2.26, EPSILON);
    EXPECT_NEAR(hc.getCodeEfficacy(), 0.957571, EPSILON);
    EXPECT_NEAR(hc.getTransmissionSpeed(400), 904, EPSILON);
    EXPECT_NEAR(hc.getSingleSymbolDuration(400), 0.00110619, EPSILON);
}

TEST(SourceCoderTest, ShannonFanoTest1) {
    tpp::ShannonFano shf;
    std::string inputText = "AAAAABCCCCCCCCCCCCCCCCCCCCDEFGH";
    std::string encoded = shf.encode(inputText);
    std::string decoded = shf.decode(shf.getSymbolTable(), encoded);

    EXPECT_EQ(inputText, decoded);

    EXPECT_NEAR(shf.getSourceEntropy(), 1.79135, EPSILON);
    EXPECT_NEAR(shf.getWeightedPathLen(), 1.93548, EPSILON);
    EXPECT_NEAR(shf.getCodeEfficacy(), 0.925531, EPSILON);
    EXPECT_NEAR(shf.getTransmissionSpeed(400), 774.1935, EPSILON);
    EXPECT_NEAR(shf.getSingleSymbolDuration(400), 0.00129167, EPSILON);
}

TEST(SourceCoderTest, ShannonFanoTest2) {
    tpp::ShannonFano shf;
    tpp::sfd symProbs = { {'1', 0.25}, {'2', 0.25}, {'3', 0.125}, {'4', 0.125}, {'5', 0.125}, {'6', 0.125} };
    shf.genSymbolTableFrom(symProbs);

    EXPECT_NEAR(shf.getSourceEntropy(), 2.5, EPSILON);
    EXPECT_NEAR(shf.getWeightedPathLen(), 2.5, EPSILON);
    EXPECT_NEAR(shf.getCodeEfficacy(), 1.0, EPSILON);
    EXPECT_NEAR(shf.getTransmissionSpeed(400), 1000, EPSILON);
    EXPECT_NEAR(shf.getSingleSymbolDuration(400), 0.001, EPSILON);
}

TEST(SourceCoderTest, ShannonFanoTest3) {
    tpp::ShannonFano shf;
    tpp::sfd symProbs = { {'1', 0.42}, {'2', 0.24}, {'3', 0.12}, {'4', 0.10}, {'5', 0.10}, {'6', 0.02} };
    shf.genSymbolTableFrom(symProbs);

    EXPECT_NEAR(shf.getSourceEntropy(), 2.16411, EPSILON);
    EXPECT_NEAR(shf.getWeightedPathLen(), 2.26, EPSILON);
    EXPECT_NEAR(shf.getCodeEfficacy(), 0.957571, EPSILON);
    EXPECT_NEAR(shf.getTransmissionSpeed(400), 904, EPSILON);
    EXPECT_NEAR(shf.getSingleSymbolDuration(400), 0.00110619, EPSILON);
}

