/**	@file	CFMatrix2x2.cpp
 *	@brief	単精度浮動小数点数型二次正方行列
 */
#include "math/CFMatrix2x2.hpp"
#include "math/Math.hpp"
#include <immintrin.h>
#include <utility>

namespace dlav {
	CFMatrix2x2::CFMatrix2x2() noexcept :
		SFloat2x2{}
	{}

	CFMatrix2x2::CFMatrix2x2(std::initializer_list<float> const& args) noexcept :
		SFloat2x2{}
	{
		unsigned int idx = 0U;
		for (auto& arg : args) {
			if (idx >= COUNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	CFMatrix2x2& CFMatrix2x2::row(unsigned int const& idx, CFVector2 const& arg) noexcept {
		if (idx >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			p[idx * CFVector2::COUNT + i] = arg.p[i];
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column(unsigned int const& idx, CFVector2 const& arg) noexcept {
		if (idx >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			p[i * CFVector2::COUNT + idx] = arg.p[i];
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::row_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= CFVector2::COUNT || to >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			std::swap(p[from * CFVector2::COUNT + i], p[to * CFVector2::COUNT + i]);
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= CFVector2::COUNT || to >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			std::swap(p[i * CFVector2::COUNT + from], p[i * CFVector2::COUNT + to]);
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::row_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			p[idx * CFVector2::COUNT + i] *= amount;
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			p[i * CFVector2::COUNT + idx] *= amount;
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::row_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= CFVector2::COUNT || to >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			p[to * CFVector2::COUNT + i] += amount * p[from * CFVector2::COUNT + i];
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= CFVector2::COUNT || to >= CFVector2::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			p[i * CFVector2::COUNT + to] += amount * p[i * CFVector2::COUNT + from];
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::operator+=(CFMatrix2x2 const& rhs) noexcept {
		_mm_store_ps(p, _mm_add_ps(_mm_load_ps(p), _mm_load_ps(rhs.p)));
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::operator-=(CFMatrix2x2 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::operator*=(float const& rhs) noexcept {
		_mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_set1_ps(rhs)));
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFVector2 const CFMatrix2x2::row(unsigned int const& idx) const noexcept {
		CFVector2 result;
		if (idx >= CFVector2::COUNT) {
			return result;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			result.p[i] = p[idx * CFVector2::COUNT + i];
		}
		return result;
	}

	CFVector2 const CFMatrix2x2::column(unsigned int const& idx) const noexcept {
		CFVector2 result;
		if (idx >= CFVector2::COUNT) {
			return result;
		}
		for (unsigned int i = 0U; i < CFVector2::COUNT; ++i) {
			result.p[i] = p[i * CFVector2::COUNT + idx];
		}
		return result;
	}

	CFMatrix2x2 const CFMatrix2x2::adj() const noexcept {
		CFMatrix2x2 result = *this;
		std::swap(result.m00, result.m11);
		result.m01 *= -1.0f;
		result.m10 *= -1.0f;
		return result;
	}

	CFMatrix2x2 const CFMatrix2x2::inv() const noexcept {
		float det_ = det();
		return compare(det_, 0.0f) ? *this / det_ : ZERO_FMTX2x2;
	}

	CFMatrix2x2 const CFMatrix2x2::transpose() const noexcept {
		CFMatrix2x2 result = *this;
		std::swap(result.m01, result.m10);
		return result;
	}

	float const CFMatrix2x2::det() const noexcept {
		return sum({
			  m11 * m00,
			-(m01 * m10)
		});
	}

	CFMatrix2x2 const CFMatrix2x2::operator+() const noexcept {
		return *this;
	}

	CFMatrix2x2 const CFMatrix2x2::operator-() const noexcept {
		return *this * -1.0f;
	}

	CFMatrix2x2 const operator+(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		CFMatrix2x2 result = lhs;
		result += rhs;
		return result;
	}

	CFMatrix2x2 const operator-(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		CFMatrix2x2 result = lhs;
		result -= rhs;
		return result;
	}

	CFMatrix2x2 const direct(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		CFMatrix2x2 result;
		for (unsigned int idx = 0U; idx < CFMatrix2x2::COUNT; ++idx) {
			result.p[idx] = lhs.p[idx % CFVector2::COUNT] * rhs.p[idx / CFVector2::COUNT];
		}
		return result;
	}

	CFMatrix2x2 const wedge(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		return direct(lhs, rhs) - direct(rhs, lhs);
	}

	CFMatrix2x2 const operator*(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		CFMatrix2x2 result;
		for (unsigned int idx = 0U; idx < CFMatrix2x2::COUNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx % CFVector2::COUNT), rhs.column(idx / CFVector2::COUNT));
		}
		return result;
	}

	CFMatrix2x2 const operator*(CFMatrix2x2 const& lhs, float const& rhs) noexcept {
		CFMatrix2x2 result = lhs;
		result *= rhs;
		return result;
	}

	CFMatrix2x2 const operator*(float const& lhs, CFMatrix2x2 const& rhs) noexcept {
		return rhs * lhs;
	}

	CFMatrix2x2 const operator/(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		return lhs * rhs.inv();
	}

	CFMatrix2x2 const operator/(CFMatrix2x2 const& lhs, float const& rhs) noexcept {
		CFMatrix2x2 result = lhs;
		result /= rhs;
		return result;
	}

	CFMatrix2x2 const operator/(float const& lhs, CFMatrix2x2 const& rhs) noexcept {
		return rhs.inv() / lhs;
	}

	CFVector2 const operator*(CFVector2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		CFVector2 result;
		for (unsigned int idx = 0U; idx < CFVector2::COUNT; ++idx) {
			result.p[idx] = dot(lhs, rhs.column(idx / CFVector2::COUNT));
		}
		return result;
	}

	CFVector2 const operator*(CFMatrix2x2 const& lhs, CFVector2 const& rhs) noexcept {
		CFVector2 result;
		for (unsigned int idx = 0U; idx < CFVector2::COUNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx % CFVector2::COUNT), rhs);
		}
		return result;
	}

	bool const operator==(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < CFMatrix2x2::COUNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}