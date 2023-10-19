#include "ip_filter_lib.h"

#include <arpa/inet.h>
#include <regex>
#include <time.h>

std::string splitLine(const std::string &str, char d)
{
    std::string::size_type stop = str.find_first_of(d);

    return str.substr(0, stop);
}

void printIpVector(std::vector<ip_address> &ipVector)
{
    std::for_each(ipVector.begin(), ipVector.end(), [&](const auto &currentIp)
    {
        struct in_addr my_addr;

        my_addr.s_addr = currentIp.ip;

        std::cout << inet_ntoa(my_addr) << std::endl;
    });
}

void sortIp(std::vector<ip_address> &ips)
{
    std::sort(ips.begin(), ips.end(), [](ip_address &ip1, ip_address &ip2) {
        for (size_t i = 0; i < MAX_OCTETS; i++)
        {
            if (ip1.octets[i] > ip2.octets[i])
            {
                return true;
            }
            if (ip1.octets[i] < ip2.octets[i])
            {
                return false;
            }
        }
        return false;
    });
}

std::vector<ip_address> getIpByMask(std::vector<ip_address> &ips, const std::vector<int> &mask)
{
    std::vector<ip_address> resultVector;

    for (std::vector<ip_address>::iterator it = ips.begin(); it != ips.end();)
    {
        bool matchFLag = true;

        for (size_t i = 0; i < MAX_OCTETS; i++)
        {
            if (mask[i] != -1 && mask[i] != it->octets[i])
            {
                matchFLag = false;
                break;
            }
        }
        if (matchFLag)
        {
            resultVector.emplace_back(*it);
        }
        ++it;
    }

    return resultVector;
}

std::vector<ip_address> getIpByByte(std::vector<ip_address> &ips, uint8_t byte)
{
    std::vector<ip_address> resultVector;

    std::for_each(ips.begin(), ips.end(), [&](const auto &currentIp) {
        for (size_t i = 0; i < MAX_OCTETS; i++)
        {
            if (byte == currentIp.octets[i])
            {
                resultVector.emplace_back(currentIp);
                return;
            }
        }
    });

    return resultVector;
}
