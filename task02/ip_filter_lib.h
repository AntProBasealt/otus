#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include <memory>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>

struct ip_address
{
    union
    {
        uint32_t ip;
        int8_t octets[4];
    };

    bool operator==(const ip_address ip2) const
    {
        if (this->ip == ip2.ip)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

std::string splitLine(const std::string &str, char d);

void ptintIpVector(std::vector<std::string> &ipVector);

void printIpVector(std::vector<ip_address> &printIpVector);

void sortIp(std::vector<ip_address> &ips);

std::unique_ptr<std::vector<ip_address>> getIpByMask(std::vector<ip_address> &ips,
                                                    std::vector<int> mask);

std::unique_ptr<std::vector<ip_address>> getIpByByte(std::vector<ip_address> &ips,
                                                    uint8_t byte);
