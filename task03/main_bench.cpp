#include "ip_filter_lib.h"
#include <benchmark/benchmark.h>
#include <iostream>
#include <random>

void generateRandomIpVector(std::vector<ip_address> &ips, int size)
{
    ips.clear();
    ips.reserve(size);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist255(0, 255);

    for (size_t i = 0; i < size; i++)
    {
        ip_address currentIp;
        for (size_t j = 0; j < MAX_OCTETS; j++)
        {
            currentIp.octets[j] = dist255(rng);
        }
        ips.emplace_back(currentIp);
    }
}

static void BM_getByMask(benchmark::State &state)
{
    std::vector<ip_address> ips;

    generateRandomIpVector(ips, 100);

    const std::vector<int>mask = {128, -1, -1, -1};

    for (auto _ : state)
        auto result = getIpByMask(ips, mask);
}
BENCHMARK(BM_getByMask);

static void BM_getByByte(benchmark::State &state)
{
    std::vector<ip_address> ips;

    generateRandomIpVector(ips, 100);

    for (auto _ : state)
        auto result = getIpByByte(ips, 128);
}
BENCHMARK(BM_getByByte);

static void BM_sortIp(benchmark::State &state)
{
    std::vector<ip_address> ips;

    generateRandomIpVector(ips, 100);

    for (auto _ : state)
        sortIp(ips);
}
BENCHMARK(BM_sortIp);

BENCHMARK_MAIN();
