#pragma once

#ifdef USE_SIMD
#include <immintrin.h>
#endif

#include <algorithm>
#include <array>

#include "basic.hpp"

NAMESPACE_BEGIN(star)

using Matrix4d = Matrix4<double>;
using Matrix4f = Matrix4<float>;
using Matrix4i = Matrix4<int>;

#ifdef USE_SIMD
static void sse_matrix4x4_mul(const float* lhs, const float* rhs, float* result)
{
    __m128 row1 = _mm_load_ps(&rhs[0]);
    __m128 row2 = _mm_load_ps(&rhs[4]);
    __m128 row3 = _mm_load_ps(&rhs[8]);
    __m128 row4 = _mm_load_ps(&rhs[12]);
    for(uint32_t i = 0; i < 4; ++i)
    {
        __m128 ai1 = _mm_set1_ps(lhs[i * 4 + 0]);
        __m128 ai2 = _mm_set1_ps(lhs[i * 4 + 1]);
        __m128 ai3 = _mm_set1_ps(lhs[i * 4 + 2]);
        __m128 ai4 = _mm_set1_ps(lhs[i * 4 + 3]);

        __m128 row = _mm_add_ps
        (
            _mm_add_ps
            (
                _mm_mul_ps(ai1, row1),
                _mm_mul_ps(ai2, row2)
            ), 
            _mm_add_ps
            (
                _mm_mul_ps(ai3, row3),
                _mm_mul_ps(ai4, row4)
            )
        );
        _mm_store_ps(&result[i * 4], row);
    }
}
#endif

template <arithmetic T>
struct Matrix4
{
private:
    T data[16];

public:
    Matrix4() = default;
    Matrix4(const Matrix4<T>&) = default;
    Matrix4(Matrix4<T>&&) = default;
    ~Matrix4() = default;
    Matrix4<T>& operator = (const Matrix4<T>&) = default;
    Matrix4<T>& operator = (Matrix4<T>&&) = default;
    auto operator <=> (const Matrix4<T>&) const = default;

    template <arithmetic... U>
	Matrix4(U... args) : data{ args... } {}

    Matrix4<T>& operator *= (T rhs)
    {
        for(auto& i : data) i *= rhs;
        return *this;
    }

    Matrix4<T> operator * (T rhs) const
    {
        return
        {
            data[0]  * rhs, data[1]  * rhs, data[2]  * rhs, data[3]  * rhs,
            data[4]  * rhs, data[5]  * rhs, data[6]  * rhs, data[7]  * rhs,
            data[8]  * rhs, data[9]  * rhs, data[10] * rhs, data[11] * rhs,
            data[12] * rhs, data[13] * rhs, data[14] * rhs, data[15] * rhs
        };
    }

    Matrix4<T> operator * (const Matrix4<T>& rhs) const
	{
		Matrix4<T> ret;
#ifdef USE_SIMD
        sse_matrix4x4_mul(data, rhs.data, ret.data);
#else
        const Matrix4<T>& lhs = *this;
        T sum;
		for(uint32_t i = 0; i < 4; i++)
        {
            for(uint32_t j = 0; j < 4; j++)
            {
                sum = 0;
                for(uint32_t k = 0; k < 4; k++)
                {
                    sum += lhs[i][k] * rhs[k][j];
                }
                ret[i][j] = sum;
            }
        }
#endif
		return ret;
	}

    struct Index
    {
        Matrix4<T>& m;
        uint32_t i;

        Index(const Index&) = delete;
        Index(Index&&) = delete;
        ~Index() = default;
        Index& operator = (const Index&) = delete;
        Index& operator = (Index&&) = delete;

        Index(Matrix4<T>& m, uint32_t i): m(m), i(i) { assert(i < 4); }

        operator T () const { return m.data[i]; }

        Index& operator [] (uint32_t index)
		{
			assert(index < 4);
			i = i * 4 + index;
			return *this;
		}

		Index& operator = (T x)
		{
			m.data[i] = x;
			return *this;
		}

		Index& operator += (T x)
		{
			m.data[i] += x;
			return *this;
		}
    };

    Index operator [] (uint32_t index) { return { *this, index }; }

    Index operator [] (uint32_t index) const
    {
        return
        {
            const_cast<Matrix4<T>&>(*this),
            index
        };
    }

 	static Matrix4<T> identity()
	{
		return
		{
			ONE<T>,  ZERO<T>, ZERO<T>, ZERO<T>,
			ZERO<T>, ONE<T>,  ZERO<T>, ZERO<T>,
			ZERO<T>, ZERO<T>, ONE<T>,  ZERO<T>,
			ZERO<T>, ZERO<T>, ZERO<T>, ONE<T>
		};
	}

    static Matrix4<T> fill(T value)
    {
        return
        {
            value, value, value, value,
            value, value, value, value,
            value, value, value, value,
            value, value, value, value
        };
    }

    Matrix4<T> transpose() const
	{
		return
        {
            data[0], data[4], data[8],  data[12],
            data[1], data[5], data[9],  data[13],
            data[2], data[6], data[10], data[14],
            data[3], data[7], data[11], data[15]
        };
	}

    Matrix4<T> adjugate() const
	{
		Matrix4<T> m;
		for(uint32_t i = 0; i < 4; ++i)
		{
			for(uint32_t j = 0; j < 4; ++j)
			{
                const T value = determinant(minor(*this, i, j));
                m[i][j] = (is_odd(i + j) && !is_zero(value)) ? -value : value;
			}
		}
		return m.transpose();
	}

    Matrix4<T> inverse() const
	{
		Matrix4<T> adj = adjugate();

		const T det =
            data[0] * adj.data[0] -
            data[1] * adj.data[4] +
            data[2] * adj.data[8] -
            data[3] * adj.data[12];

		return adj * reciprocal(det);
	}

private:
    static T determinant(const std::array<T, 9>& m)
    {
        return  m[0] * (m[4] * m[8] - m[5] * m[7]) -
                m[1] * (m[3] * m[8] - m[5] * m[6]) +
                m[2] * (m[3] * m[7] - m[4] * m[6]);
    }

    static std::array<T, 9> minor(const Matrix4<T>& m, uint32_t i, uint32_t j)
	{
		std::array<T, 9> ret;
		uint32_t k = 0;
		for(uint32_t x = 0; x < 4; ++x)
		{
			for(uint32_t y = 0; y < 4; ++y)
			{
				if(x != i && y != j)
				{
					ret[k] = m[x][y];
					k++;
				}
			}
		}
		return ret;
	}
};

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Matrix4<T>& m)
{
    for(uint32_t i = 0; i < 4; ++i)
    {
        os << '[';
        for (uint32_t j = 0; j < 4; ++j)
        {
            os << m[i][j] << (j != 3 ? ", " : "]\n");
        }
    }
	return os;
}

NAMESPACE_END(star)
