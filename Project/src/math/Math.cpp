/**	@file	Math.cpp
 *	@brief	数学関数群
 */
#include "math/Math.hpp"
#include <immintrin.h>
#include <numeric>

namespace dlav {
	template <>
	int const compare<float>(float const& lhs, float const& rhs) noexcept {
		if (fabsf(lhs - rhs) < FLT_EPSILON * fmaxf(fmaxf(fabsf(lhs), fabsf(rhs)), 1.0f)) {
			return 0;
		}
		if (lhs < rhs) {
			return -1;
		}
		return 1;
	}

	template <>
	int const compare<double>(double const& lhs, double const& rhs) noexcept {
		if (fabs(lhs - rhs) < DBL_EPSILON * fmax(fmax(fabs(lhs), fabs(rhs)), 1.0f)) {
			return 0;
		}
		if (lhs < rhs) {
			return -1;
		}
		return 1;
	}

	template <>
	float const sum<float>(float const* const args, size_t const& size) noexcept {
		float result = 0.0f;
		if (args == nullptr || size == 0U) {
			return result;
		}

		volatile float y, c, t;
		c = 0.0f;
		for (size_t idx = 0U; idx < size; ++idx) {
			y = *(args + idx) - c;
			t = result + y;
			c = (t - result) - y;
			result = t;
		}

		return result;
	}

	template <>
	double const sum<double>(double const* const args, size_t const& size) noexcept {
		double result = 0.0;
		if (args == nullptr || size == 0U) {
			return result;
		}

		volatile double y, c, t;
		c = 0.0;
		for (size_t idx = 0U; idx < size; ++idx) {
			y = *(args + idx) - c;
			t = result + y;
			c = (t - result) - y;
			result = t;
		}

		return result;
	}

	template <>
	__m128 const sum<__m128>(__m128 const* const args, size_t const& size) noexcept {
		__m128 result = _mm_set1_ps(0.0f);
		if (args == nullptr || size == 0U) {
			return result;
		}

		__m128 y, c, t;
		c = _mm_set1_ps(0.0f);
		for (size_t idx = 0U; idx < size; ++idx) {
			y = _mm_sub_ps(*(args + idx), c);
			t = _mm_add_ps(result, y);
			c = _mm_sub_ps(_mm_sub_ps(t, result), y);
			result = t;
		}

		return result;
	}

	template <>
	__m256d const sum<__m256d>(__m256d const* const args, size_t const& size) noexcept {
		__m256d result = _mm256_set1_pd(0.0);
		if (args == nullptr || size == 0U) {
			return result;
		}

		__m256d y, c, t;
		c = _mm256_set1_pd(0.0);
		for (size_t idx = 0U; idx < size; ++idx) {
			y = _mm256_sub_pd(*(args + idx), c);
			t = _mm256_add_pd(result, y);
			c = _mm256_sub_pd(_mm256_sub_pd(t, result), y);
			result = t;
		}

		return result;
	}

	template <>
	float const sqrt<float>(float const& arg) noexcept {
		float result = 0.0f;
		if (arg < 0.0f) {
			return result;
		}

		result = arg;
		float half = result * 0.5f;
		int temp = 0x5F3759DF - (*reinterpret_cast<int*>(&result) >> 1);
		result = *reinterpret_cast<float*>(&temp);

		result *= 1.5f - half * result * result;
		result *= 1.5f - half * result * result;
		result *= 1.5f - half * result * result;
		result *= arg;

		return result;
	}

	template <>
	double const sqrt<double>(double const& arg) noexcept {
		double result = 0.0;
		if (arg < 0.0) {
			return result;
		}

		result = arg;
		double half = result * 0.5;
		long long temp = 0x5FE6EB50C7B537AAL - (*reinterpret_cast<long long*>(&result) >> 1);
		result = *reinterpret_cast<double*>(&temp);

		result *= 1.5 - half * result * result;
		result *= 1.5 - half * result * result;
		result *= 1.5 - half * result * result;
		result *= arg;

		return result;
	}

	template <>
	float const mod<float>(float const& lhs, float const& rhs) noexcept {
		return floorf(lhs / rhs);
	}

	template <>
	double const mod<double>(double const& lhs, double const& rhs) noexcept {
		return floor(lhs / rhs);
	}

	template <>
	float const quot<float>(float const& lhs, float const& rhs) noexcept {
		return sum({ lhs, -(mod(lhs, rhs) * rhs) });
	}

	template <>
	double const quot<double>(double const& lhs, double const& rhs) noexcept {
		return sum({ lhs, -(mod(lhs, rhs) * rhs) });
	}
}