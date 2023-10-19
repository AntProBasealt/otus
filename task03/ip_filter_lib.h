#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>

inline static const int MAX_OCTETS = 4;

struct ip_address {
    union{
        uint32_t ip;
        uint8_t octets[MAX_OCTETS];
    };

    bool operator ==(const ip_address ip2) const {

        if(this->ip ==ip2.ip)
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
void printIpVector(std::vector<ip_address> &printIpVector);
void printIpVector(std::vector<std::string> &ipVector);
void sortIp(std::vector<ip_address> &ips);
std::vector<ip_address> getIpByMask(std::vector<ip_address> &ips, const std::vector<int> &mask);
std::vector<ip_address> getIpByByte(std::vector<ip_address> &ips, uint8_t byte);
