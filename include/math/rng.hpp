#pragma once

#include "basic.hpp"

NAMESPACE_BEGIN(star)

template <arithmetic T>
struct LCG
{
public:
    LCG(uint32_t x = time(nullptr)) : x(x) {}

    T get() noexcept
    {
        x = a * x % m;
        return static_cast<T>(x) * inv_m;
    }
    
private:
    const uint32_t m = MAX_NUMBER<uint32_t>;
    const uint32_t a = 16807;
    const T inv_m = reciprocal(m);
    uint32_t x;
};

template <arithmetic T>
T rand() noexcept
{
    static LCG<T> rng;
    return rng.get();
}

NAMESPACE_END(star)
