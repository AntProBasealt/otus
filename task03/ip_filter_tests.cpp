#include "ip_filter_lib.h"
#include "gtest/gtest.h"

void convertStringToIpVector(std::vector<std::string> &strVector,
                             std::vector<ip_address> &resultVector)
{
    resultVector.clear();
    resultVector.reserve(resultVector.size());
    std::for_each(strVector.cbegin(), strVector.cend(), [&](std::string currentIp) {
        ip_address ip_addr;

        ip_addr.ip = inet_addr(currentIp.c_str());

        resultVector.push_back(ip_addr);
    });
}

TEST(sortTest, sortingTest)
{
    std::vector<std::string> testIps   = {"1.1.1.2", "1.1.1.3", "1.2.1.3", "2.2.1.3"};
    std::vector<std::string> resultIps = {"2.2.1.3", "1.2.1.3", "1.1.1.3", "1.1.1.2"};

    std::vector<ip_address> testVector;

    convertStringToIpVector(testIps, testVector);

    std::vector<ip_address> resultVector;

    convertStringToIpVector(resultIps, resultVector);

    sortIp(testVector);

    EXPECT_EQ(testVector, resultVector);
}

TEST(getByMask, filterTest)
{
    std::vector<std::string> testIps
        = {"46.46.46.2", "46.46.46.0", "46.46.46.1", "46.46.46.3", "192.168.46.3", "192.168.0.3"};
    std::vector<std::string> resultIps = {"46.46.46.2", "46.46.46.0", "46.46.46.1", "46.46.46.3"};

    std::vector<ip_address> testVector;

    convertStringToIpVector(testIps, testVector);

    std::vector<ip_address> resultVector;

    convertStringToIpVector(resultIps, resultVector);

    auto resultByMask = getIpByMask(testVector, {-1, 46, 46, -1});

    EXPECT_EQ(resultByMask, resultVector);
}

TEST(getByByte, filterTest)
{
    std::vector<std::string> testIps
        = {"46.46.46.2", "46.46.46.0", "46.46.46.1", "46.46.46.3", "192.168.46.3", "192.168.0.3"};
    std::vector<std::string> resultIps = {"46.46.46.2",
                                          "46.46.46.0",
                                          "46.46.46.1",
                                          "46.46.46.3",
                                          "192.168.46.3"};

    std::vector<ip_address> testVector;

    convertStringToIpVector(testIps, testVector);

    std::vector<ip_address> resultVector;

    convertStringToIpVector(resultIps, resultVector);

    auto resultByByte = getIpByByte(testVector, 46);

    EXPECT_EQ(resultByByte, resultVector);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
