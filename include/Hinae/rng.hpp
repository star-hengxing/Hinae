#pragma once

#include "basic.hpp"

#include <ctime>

NAMESPACE_BEGIN(Hinae)

template <arithmetic T>
using LCG = Linear_congruential_generator<T, 16807u, 0u, MAX_NUMBER<u32>>;

template <arithmetic T, u32 A, u32 C, u32 M>
struct Linear_congruential_generator
{
public:
    Linear_congruential_generator(u32 seed = std::time(nullptr)) : seed(seed) {}

    constexpr T get()
    {
        seed = (multiplier * seed) % modulus;
        if constexpr(std::is_floating_point_v<T>)
            return static_cast<T>(seed) / static_cast<T>(modulus);
        else
            return static_cast<T>(seed);
    }

private:
    static constexpr u32 multiplier = A;
    static constexpr u32 increment = C;
    static constexpr u32 modulus = M;
    u32 seed;
};

NAMESPACE_END(Hinae)
