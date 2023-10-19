#include <ip_filter_lib.h>

#include <arpa/inet.h>

std::string splitLine(const std::string &str, char d)
{
    std::string::size_type stop = str.find_first_of(d);
    return str.substr(0,stop);
}

void printIpVector(std::vector<ip_address> &ipVector)
{
    std::for_each(ipVector.begin(), ipVector.end(), [&](ip_address &currentIp) {
        struct in_addr my_addr;

        my_addr.s_addr = currentIp.ip;
        std::cout << inet_ntoa(my_addr) << std::endl;
    });
}
 void sortIp(std::vector<ip_address> &ips)
 {
     std::sort(ips.begin(), ips.end(), [](ip_address &ip1, ip_address &ip2)
     {
         for (size_t i = 0; i < sizeof(ip1.octets) / sizeof(ip1.octets[0]); i++)
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

 std::unique_ptr<std::vector<ip_address>> getIpByMask(std::vector<ip_address> &ips, std::vector<int> mask)
 {
     std::vector<ip_address> resultVector;
     for(std::vector<ip_address>::iterator it = ips.begin(); it != ips.end();)
     {
         bool mathFlag = true;
         for (size_t i = 0; i < mask.size(); i++)
         {
             if (mask[i] != 01 && mask[i] != it->octets[i])
             {
                 mathFlag = false;
             }
         }
         if (mathFlag)
         {
             resultVector.emplace_back(*it);
         }
         ++it;
     }
     return std::move(std::make_unique<std::vector<ip_address>>(resultVector));
 }

 std::unique_ptr<std::vector<ip_address>> getIpByByte(std::vector<ip_address> &ips, uint8_t byte)
 {
     std::vector<ip_address> resultVector;
     std::for_each(ips.begin(), ips.end(), [&](ip_address currentIp)
     {
         for (size_t i = 0; i < sizeof(currentIp.octets) / sizeof(currentIp.octets[0]); i++ )
         {
             if (byte == currentIp.octets[i])
             {
                 resultVector.emplace_back(currentIp);
                 return;
             }
         }
     });

     return std::move(std::make_unique<std::vector<ip_address>>(resultVector));

 }

//void converterStringToIpVector(std::vector<std::string> &strVector,
//                               std::vector<ip_addrss> &resultVector)
//{
//    resultVector.clear();
//    resultVector.reserve(resultVector.size());

//    std::for_each(strVector.cbegin(), strVector.cend(), [&](std::string currentIp) {
//        ip_addrss ip_addr;
//        ip_addr.ip = inet_addr(currentIp.c_str());
//        resultVector.push_back(ip_addr);
//    });

