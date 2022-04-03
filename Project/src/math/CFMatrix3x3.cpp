/**	@file	CFMatrix3x3.cpp
 *	@brief	単精度浮動小数点数型三次正方行列
 */
#include "math/CFMatrix3x3.hpp"
#include "math/CFMatrix2x2.hpp"
#include "math/Math.hpp"
#include <immintrin.h>
#include <utility>

namespace dlav {
	CFMatrix3x3::CFMatrix3x3() noexcept :
		SFloat3x3{}
	{}

	CFMatrix3x3::CFMatrix3x3(std::initializer_list<float> const& args) noexcept :
		SFloat3x3{}
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

	CFMatrix3x3& CFMatrix3x3::row(unsigned int const& idx, CFVector3 const& arg) noexcept {
		if (idx >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			p[idx * CFVector3::COUNT + i] = arg.p[i];
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::column(unsigned int const& idx, CFVector3 const& arg) noexcept {
		if (idx >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			p[i * CFVector3::COUNT + idx] = arg.p[i];
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::row_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= CFVector3::COUNT || to >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			std::swap(p[from * CFVector3::COUNT + i], p[to * CFVector3::COUNT + i]);
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::column_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= CFVector3::COUNT || to >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			std::swap(p[i * CFVector3::COUNT + from], p[i * CFVector3::COUNT + to]);
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::row_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			p[idx * CFVector3::COUNT + i] *= amount;
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::column_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			p[i * CFVector3::COUNT + idx] *= amount;
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::row_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= CFVector3::COUNT || to >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			p[to * CFVector3::COUNT + i] += amount * p[from * CFVector3::COUNT + i];
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::column_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= CFVector3::COUNT || to >= CFVector3::COUNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			p[i * CFVector3::COUNT + to] += amount * p[i * CFVector3::COUNT + from];
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::operator+=(CFMatrix3x3 const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < CFMatrix3x3::COUNT; idx += 4U) {
			_mm_store_ps(&p[idx], _mm_add_ps(_mm_load_ps(&p[idx]), _mm_load_ps(&rhs.p[idx])));
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::operator-=(CFMatrix3x3 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::operator*=(float const& rhs) noexcept {
		__m128 tmp = _mm_set1_ps(rhs);
		for (unsigned int idx = 0U; idx < CFMatrix3x3::COUNT; idx += 4U) {
			_mm_store_ps(&p[idx], _mm_mul_ps(_mm_load_ps(&p[idx]), tmp));
		}
		return *this;
	}

	CFMatrix3x3& CFMatrix3x3::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFVector3 const CFMatrix3x3::row(unsigned int const& idx) const noexcept {
		CFVector3 result;
		if (idx >= CFVector3::COUNT) {
			return result;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			result.p[i] = p[idx * CFVector3::COUNT + i];
		}
		return result;
	}

	CFVector3 const CFMatrix3x3::column(unsigned int const& idx) const noexcept {
		CFVector3 result;
		if (idx >= CFVector3::COUNT) {
			return result;
		}
		for (unsigned int i = 0U; i < CFVector3::COUNT; ++i) {
			result.p[i] = p[i * CFVector3::COUNT + idx];
		}
		return result;
	}

	CFMatrix3x3 const CFMatrix3x3::adj() const noexcept {
		CFMatrix3x3 result = *this;
		CFMatrix2x2 tmp;

		unsigned int idx1, idx2, idx3;
		unsigned int  dx1, dx2;
		unsigned int  dy1, dy2;

		for (idx1 = 0U; idx1 < CFMatrix3x3::COUNT; ++idx1) {
			dx1 = idx1 / CFVector3::COUNT;
			dy1 = idx1 % CFVector3::COUNT;
			for (idx2 = 0U, idx3 = 0U; idx2 < CFMatrix3x3::COUNT; ++idx2) {
				dx2 = idx2 / CFVector3::COUNT;
				dy2 = idx2 % CFVector3::COUNT;
				if (dx1 != dx2 && dy1 != dy2) {
					tmp.p[idx3] = p[dy2 * CFVector3::COUNT + dx2];
					++idx3;
				}
			}
			result.p[idx1] = tmp.det();
			if ((dx1 + dy1) % 2U == 1U) {
				result.p[idx1] *= -1.0f;
			}
		}

		return result;
	}

	CFMatrix3x3 const CFMatrix3x3::inv() const noexcept {
		float det_ = det();
		return compare(det_, 0.0f) ? *this / det_ : ZERO_FMTX3x3;
	}

	CFMatrix3x3 const CFMatrix3x3::transpose() const noexcept {
		CFMatrix3x3 result = *this;
		std::swap(result.m01, result.m10);
		std::swap(result.m02, result.m20);
		std::swap(result.m12, result.m21);
		return result;
	}

	float const CFMatrix3x3::det() const noexcept {
		return sum({
			  m00 * m11 * m22,
			  m01 * m12 * m20,
			  m02 * m10 * m21,
			-(m00 * m12 * m21),
			-(m01 * m10 * m22),
			-(m02 * m11 * m20)
		});
	}

	CFMatrix3x3 const CFMatrix3x3::operator+() const noexcept {
		return *this;
	}

	CFMatrix3x3 const CFMatrix3x3::operator-() const noexcept {
		return *this * -1.0f;
	}

	CFMatrix3x3 const operator+(CFMatrix3x3 const& lhs, CFMatrix3x3 const& rhs) noexcept {
		CFMatrix3x3 result = lhs;
		result += rhs;
		return result;
	}

	CFMatrix3x3 const operator-(CFMatrix3x3 const& lhs, CFMatrix3x3 const& rhs) noexcept {
		CFMatrix3x3 result = lhs;
		result -= rhs;
		return result;
	}

	CFMatrix3x3 const direct(CFVector3 const& lhs, CFVector3 const& rhs) noexcept {
		CFMatrix3x3 result;
		for (unsigned int idx = 0U; idx < CFMatrix3x3::COUNT; ++idx) {
			result.p[idx] = lhs.p[idx % CFVector3::COUNT] * rhs.p[idx / CFVector3::COUNT];
		}
		return result;
	}

	CFMatrix3x3 const wedge(CFVector3 const& lhs, CFVector3 const& rhs) noexcept {
		return direct(lhs, rhs) - direct(rhs, lhs);
	}

	CFMatrix3x3 const operator*(CFMatrix3x3 const& lhs, CFMatrix3x3 const& rhs) noexcept {
		CFMatrix3x3 result;
		for (unsigned int idx = 0U; idx < CFMatrix3x3::COUNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx % CFVector3::COUNT), rhs.column(idx / CFVector3::COUNT));
		}
		return result;
	}

	CFMatrix3x3 const operator*(CFMatrix3x3 const& lhs, float const& rhs) noexcept {
		CFMatrix3x3 result = lhs;
		result *= rhs;
		return result;
	}

	CFMatrix3x3 const operator*(float const& lhs, CFMatrix3x3 const& rhs) noexcept {
		return rhs * lhs;
	}

	CFMatrix3x3 const operator/(CFMatrix3x3 const& lhs, CFMatrix3x3 const& rhs) noexcept {
		return lhs * rhs.inv();
	}

	CFMatrix3x3 const operator/(CFMatrix3x3 const& lhs, float const& rhs) noexcept {
		CFMatrix3x3 result = lhs;
		result /= rhs;
		return result;
	}

	CFMatrix3x3 const operator/(float const& lhs, CFMatrix3x3 const& rhs) noexcept {
		return rhs.inv() / lhs;
	}

	CFVector3 const operator*(CFVector3 const& lhs, CFMatrix3x3 const& rhs) noexcept {
		CFVector3 result;
		for (unsigned int idx = 0U; idx < CFVector3::COUNT; ++idx) {
			result.p[idx] = dot(lhs, rhs.column(idx / CFVector3::COUNT));
		}
		return result;
	}

	CFVector3 const operator*(CFMatrix3x3 const& lhs, CFVector3 const& rhs) noexcept {
		CFVector3 result;
		for (unsigned int idx = 0U; idx < CFVector3::COUNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx % CFVector3::COUNT), rhs);
		}
		return result;
	}

	bool const operator==(CFMatrix3x3 const& lhs, CFMatrix3x3 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < CFMatrix3x3::COUNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFMatrix3x3 const& lhs, CFMatrix3x3 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}