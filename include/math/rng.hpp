#pragma once

#include "basic.hpp"

NAMESPACE_BEGIN(Hinae)

template <arithmetic T>
using LCG = Linear_congruential_generator<T, 16807u, 0u, MAX_NUMBER<uint32_t>>;

template <arithmetic T, uint32_t A, uint32_t C, uint32_t M>
struct Linear_congruential_generator
{
public:
    Linear_congruential_generator(uint32_t seed = time(nullptr)) : seed(seed) {}

    constexpr T get()
    { 
        seed = (multiplier * seed) % modulus;
        if constexpr(std::is_floating_point_v<T>)
            return static_cast<T>(seed) / static_cast<T>(modulus);
        else
            return static_cast<T>(seed);
    }
    
private:
    static constexpr uint32_t multiplier = A;
    static constexpr uint32_t increment = C;
    static constexpr uint32_t modulus = M;
    uint32_t seed;
};

NAMESPACE_END(Hinae)
