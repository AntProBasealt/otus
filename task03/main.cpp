#include <iostream>
#include <string>
#include <vector>

#include <memory>
#include <stdlib.h>

#include <arpa/inet.h>
#include <fstream>
#include <iostream>

#include "ip_filter_lib.h"

int main(int, char const *[])
{
    try
    {
        std::vector<ip_address> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::string v = splitLine(line, '\t');


            ip_address currentIp;
            in_addr ip;

            if(inet_aton(v.c_str(), &ip) ==0) {
                std::cout << "String:" << v << " is not a valid IP address!" << std::endl;
                continue;
            }
            currentIp.ip = ip.s_addr;

            ip_pool.push_back(currentIp);
        }

        sortIp(ip_pool);
        printIpVector(ip_pool);

        auto printByMask = [](std::vector<ip_address> ips, std::vector<int> mask) {
            auto byMaskResult = getIpByMask(ips, mask);
            printIpVector(byMaskResult);
        };

        printByMask(ip_pool, {1, -1, -1, -1});

        printByMask(ip_pool, {46, 70, -1, -1});

        auto resultByByte = getIpByByte(ip_pool, 46);
        printIpVector(resultByByte);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
