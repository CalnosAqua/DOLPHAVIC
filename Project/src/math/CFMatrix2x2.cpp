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
			if (idx >= FLT2x2_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	CFMatrix2x2& CFMatrix2x2::row(unsigned int const& idx, CFVector2 const& arg) noexcept {
		if (idx >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			p[idx * FLT2_CNT + i] = arg.p[i];
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column(unsigned int const& idx, CFVector2 const& arg) noexcept {
		if (idx >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			p[i * FLT2_CNT + idx] = arg.p[i];
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::row_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= FLT2_CNT || to >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			std::swap(p[from * FLT2_CNT + i], p[to * FLT2_CNT + i]);
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= FLT2_CNT || to >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			std::swap(p[i * FLT2_CNT + from], p[i * FLT2_CNT + to]);
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::row_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			p[idx * FLT2_CNT + i] *= amount;
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			p[i * FLT2_CNT + idx] *= amount;
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::row_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= FLT2_CNT || to >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			p[to * FLT2_CNT + i] += amount * p[from * FLT2_CNT + i];
		}
		return *this;
	}

	CFMatrix2x2& CFMatrix2x2::column_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= FLT2_CNT || to >= FLT2_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			p[i * FLT2_CNT + to] += amount * p[i * FLT2_CNT + from];
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
		if (idx >= FLT2_CNT) {
			return result;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			result.p[i] = p[idx * FLT2_CNT + i];
		}
		return result;
	}

	CFVector2 const CFMatrix2x2::column(unsigned int const& idx) const noexcept {
		CFVector2 result;
		if (idx >= FLT2_CNT) {
			return result;
		}
		for (unsigned int i = 0U; i < FLT2_CNT; ++i) {
			result.p[i] = p[i * FLT2_CNT + idx];
		}
		return result;
	}

	CFMatrix2x2 const CFMatrix2x2::adj() const noexcept {
		CFMatrix2x2 result;

		unsigned int dx, dy, dx_t, dy_t;
		for (unsigned int cur = 0U; cur < FLT2x2_CNT; ++cur) {
			for (unsigned int idx = 0U; idx < FLT2x2_CNT; ++idx) {
				dx = idx % FLT2_CNT;
				dy = idx / FLT2_CNT;
				dx_t = cur % FLT2_CNT;
				dy_t = cur / FLT2_CNT;
				if (dx_t != dx && dy_t != dy) {
					result.p[cur] = p[dy * FLT2_CNT + dx];
					if ((dx_t + dy_t) % 2U == 1U) {
						result.p[cur] *= -1.0f;
					}
				}
			}
		}

		return result.transpose();
	}

	CFMatrix2x2 const CFMatrix2x2::inv() const noexcept {
		CFMatrix2x2 result;
		float det = this->det();
		if (compare(det, 0.0f)) {
			result = adj();
			result /= det;
		}
		return result;
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
		for (unsigned int idx = 0U; idx < FLT2x2_CNT; ++idx) {
			result.p[idx] = lhs.p[idx / FLT2_CNT] * rhs.p[idx % FLT2_CNT];
		}
		return result;
	}

	CFMatrix2x2 const wedge(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		return direct(lhs, rhs) - direct(rhs, lhs);
	}

	CFMatrix2x2 const operator*(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		CFMatrix2x2 result;
		for (unsigned int idx = 0U; idx < FLT2x2_CNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx / FLT2_CNT), rhs.column(idx % FLT2_CNT));
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
		for (unsigned int idx = 0U; idx < FLT2_CNT; ++idx) {
			result.p[idx] = dot(lhs, rhs.column(idx % FLT2_CNT));
		}
		return result;
	}

	CFVector2 const operator*(CFMatrix2x2 const& lhs, CFVector2 const& rhs) noexcept {
		CFVector2 result;
		for (unsigned int idx = 0U; idx < FLT2_CNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx / FLT2_CNT), rhs);
		}
		return result;
	}

	bool const operator==(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < FLT2x2_CNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFMatrix2x2 const& lhs, CFMatrix2x2 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}