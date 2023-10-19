#include <iostream>
#include <string>
#include <vector>

#include <memory>
#include <stdlib.h>

#include <arpa/inet.h>
#include <fstream>
#include <ip_filter_lib.h>

int main(int, char const *[])
{
    try
    {
        std::vector<ip_address> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::string v = splitLine(line, '\t');
            ip_address currentIp;
            currentIp.ip = inet_addr(v.c_str());
            ip_pool.push_back(currentIp);
        }

        sortIp(ip_pool);
        printIpVector(ip_pool);

        auto printByMask = [](std::vector<ip_address> ips, std::vector<int> mask)
        {
            auto byMaskResult = getIpByMask(ips, mask);
            printIpVector(*byMaskResult.get());
        };

        printByMask(ip_pool, {1, -1, -1, -1});
        printByMask(ip_pool, {46, 70, -1, -1});

        auto resultByByte = getIpByByte(ip_pool, 46);
        printIpVector(*resultByByte.get());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
