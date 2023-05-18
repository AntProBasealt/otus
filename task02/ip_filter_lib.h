#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>

struct ip_addrss
{
    union
    {
        uint32_t ip;
        int8_t octets[4];
    };

    bool operator==(const ip_addrss ip2) const
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

