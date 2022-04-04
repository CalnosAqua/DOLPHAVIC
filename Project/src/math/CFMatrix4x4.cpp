/**	@file	CFMatrix4x4.cpp
 *	@brief	単精度浮動小数点数型四次正方行列
 */
#include "math/CFMatrix4x4.hpp"
#include "math/CFMatrix3x3.hpp"
#include "math/Math.hpp"
#include <immintrin.h>
#include <utility>

namespace dlav {
	CFMatrix4x4::CFMatrix4x4() noexcept :
		SFloat4x4{}
	{}

	CFMatrix4x4::CFMatrix4x4(std::initializer_list<float> const& args) noexcept :
		SFloat4x4{}
	{
		unsigned int idx = 0U;
		for (auto& arg : args) {
			if (idx >= FLT4x4_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	CFMatrix4x4& CFMatrix4x4::row(unsigned int const& idx, CFVector4 const& arg) noexcept {
		if (idx >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			p[idx * FLT4_CNT + i] = arg.p[i];
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::column(unsigned int const& idx, CFVector4 const& arg) noexcept {
		if (idx >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			p[i * FLT4_CNT + idx] = arg.p[i];
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::row_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= FLT4_CNT || to >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			std::swap(p[from * FLT4_CNT + i], p[to * FLT4_CNT + i]);
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::column_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from == to || from >= FLT4_CNT || to >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			std::swap(p[i * FLT4_CNT + from], p[i * FLT4_CNT + to]);
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::row_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			p[idx * FLT4_CNT + i] *= amount;
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::column_scale(unsigned int const& idx, float const& amount) noexcept {
		if (idx >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			p[i * FLT4_CNT + idx] *= amount;
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::row_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= FLT4_CNT || to >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			p[to * FLT4_CNT + i] += amount * p[from * FLT4_CNT + i];
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::column_sop(unsigned int const& from, unsigned int const& to, float const& amount) noexcept {
		if (from == to || from >= FLT4_CNT || to >= FLT4_CNT) {
			return *this;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			p[i * FLT4_CNT + to] += amount * p[i * FLT4_CNT + from];
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::operator+=(CFMatrix4x4 const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < FLT4x4_CNT; idx += 4U) {
			_mm_store_ps(&p[idx], _mm_add_ps(_mm_load_ps(&p[idx]), _mm_load_ps(&rhs.p[idx])));
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::operator-=(CFMatrix4x4 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::operator*=(float const& rhs) noexcept {
		__m128 tmp = _mm_set1_ps(rhs);
		for (unsigned int idx = 0U; idx < FLT4x4_CNT; idx += 4U) {
			_mm_store_ps(&p[idx], _mm_mul_ps(_mm_load_ps(&p[idx]), tmp));
		}
		return *this;
	}

	CFMatrix4x4& CFMatrix4x4::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFVector4 const CFMatrix4x4::row(unsigned int const& idx) const noexcept {
		CFVector4 result;
		if (idx >= FLT4_CNT) {
			return result;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			result.p[i] = p[idx * FLT4_CNT + i];
		}
		return result;
	}

	CFVector4 const CFMatrix4x4::column(unsigned int const& idx) const noexcept {
		CFVector4 result;
		if (idx >= FLT4_CNT) {
			return result;
		}
		for (unsigned int i = 0U; i < FLT4_CNT; ++i) {
			result.p[i] = p[i * FLT4_CNT + idx];
		}
		return result;
	}

	CFMatrix4x4 const CFMatrix4x4::adj() const noexcept {
		CFMatrix4x4 result = *this;
		CFMatrix3x3 tmp;

		unsigned int idx1, idx2, idx4;
		unsigned int  dx1, dx2;
		unsigned int  dy1, dy2;

		for (idx1 = 0U; idx1 < FLT4x4_CNT; ++idx1) {
			dx1 = idx1 / FLT4_CNT;
			dy1 = idx1 % FLT4_CNT;
			for (idx2 = 0U, idx4 = 0U; idx2 < FLT4x4_CNT; ++idx2) {
				dx2 = idx2 / FLT4_CNT;
				dy2 = idx2 % FLT4_CNT;
				if (dx1 != dx2 && dy1 != dy2) {
					tmp.p[idx4] = p[dy2 * FLT4_CNT + dx2];
					++idx4;
				}
			}
			result.p[idx1] = tmp.det();
			if ((dx1 + dy1) % 2U == 1U) {
				result.p[idx1] *= -1.0f;
			}
		}

		return result;
	}

	CFMatrix4x4 const CFMatrix4x4::inv() const noexcept {
		float det_ = det();
		return compare(det_, 0.0f) ? *this / det_ : ZERO_FMTX4x4;
	}

	CFMatrix4x4 const CFMatrix4x4::transpose() const noexcept {
		CFMatrix4x4 result = *this;
		std::swap(result.m01, result.m10);
		std::swap(result.m02, result.m20);
		std::swap(result.m03, result.m30);
		std::swap(result.m12, result.m21);
		std::swap(result.m13, result.m31);
		std::swap(result.m23, result.m32);
		return result;
	}

	float const CFMatrix4x4::det() const noexcept {
		return sum({
			  m00 * m12 * m22 * m33,
			  m00 * m12 * m23 * m31,
			  m00 * m13 * m21 * m32,
			  m01 * m10 * m23 * m32,
			  m01 * m12 * m10 * m33,
			  m01 * m13 * m22 * m30,
			  m02 * m10 * m21 * m33,
			  m02 * m13 * m20 * m31,
			  m02 * m11 * m23 * m30,
			  m03 * m10 * m22 * m31,
			  m03 * m11 * m20 * m32,
			  m03 * m12 * m21 * m30,
			-(m00 * m13 * m22 * m31),
			-(m00 * m12 * m21 * m33),
			-(m00 * m11 * m23 * m32),
			-(m01 * m10 * m22 * m33),
			-(m01 * m13 * m20 * m32),
			-(m01 * m12 * m23 * m30),
			-(m02 * m12 * m20 * m33),
			-(m02 * m10 * m23 * m31),
			-(m02 * m13 * m21 * m30),
			-(m03 * m10 * m21 * m32),
			-(m03 * m12 * m20 * m31),
			-(m03 * m11 * m22 * m30)
		});
	}

	CFMatrix4x4 const CFMatrix4x4::operator+() const noexcept {
		return *this;
	}

	CFMatrix4x4 const CFMatrix4x4::operator-() const noexcept {
		return *this * -1.0f;
	}

	CFMatrix4x4 const operator+(CFMatrix4x4 const& lhs, CFMatrix4x4 const& rhs) noexcept {
		CFMatrix4x4 result = lhs;
		result += rhs;
		return result;
	}

	CFMatrix4x4 const operator-(CFMatrix4x4 const& lhs, CFMatrix4x4 const& rhs) noexcept {
		CFMatrix4x4 result = lhs;
		result -= rhs;
		return result;
	}

	CFMatrix4x4 const direct(CFVector4 const& lhs, CFVector4 const& rhs) noexcept {
		CFMatrix4x4 result;
		for (unsigned int idx = 0U; idx < FLT4x4_CNT; ++idx) {
			result.p[idx] = lhs.p[idx % FLT4_CNT] * rhs.p[idx / FLT4_CNT];
		}
		return result;
	}

	CFMatrix4x4 const wedge(CFVector4 const& lhs, CFVector4 const& rhs) noexcept {
		return direct(lhs, rhs) - direct(rhs, lhs);
	}

	CFMatrix4x4 const operator*(CFMatrix4x4 const& lhs, CFMatrix4x4 const& rhs) noexcept {
		CFMatrix4x4 result;
		for (unsigned int idx = 0U; idx < FLT4x4_CNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx % FLT4_CNT), rhs.column(idx / FLT4_CNT));
		}
		return result;
	}

	CFMatrix4x4 const operator*(CFMatrix4x4 const& lhs, float const& rhs) noexcept {
		CFMatrix4x4 result = lhs;
		result *= rhs;
		return result;
	}

	CFMatrix4x4 const operator*(float const& lhs, CFMatrix4x4 const& rhs) noexcept {
		return rhs * lhs;
	}

	CFMatrix4x4 const operator/(CFMatrix4x4 const& lhs, CFMatrix4x4 const& rhs) noexcept {
		return lhs * rhs.inv();
	}

	CFMatrix4x4 const operator/(CFMatrix4x4 const& lhs, float const& rhs) noexcept {
		CFMatrix4x4 result = lhs;
		result /= rhs;
		return result;
	}

	CFMatrix4x4 const operator/(float const& lhs, CFMatrix4x4 const& rhs) noexcept {
		return rhs.inv() / lhs;
	}

	CFVector4 const operator*(CFVector4 const& lhs, CFMatrix4x4 const& rhs) noexcept {
		CFVector4 result;
		for (unsigned int idx = 0U; idx < FLT4_CNT; ++idx) {
			result.p[idx] = dot(lhs, rhs.column(idx / FLT4_CNT));
		}
		return result;
	}

	CFVector4 const operator*(CFMatrix4x4 const& lhs, CFVector4 const& rhs) noexcept {
		CFVector4 result;
		for (unsigned int idx = 0U; idx < FLT4_CNT; ++idx) {
			result.p[idx] = dot(lhs.row(idx % FLT4_CNT), rhs);
		}
		return result;
	}

	bool const operator==(CFMatrix4x4 const& lhs, CFMatrix4x4 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < FLT4x4_CNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFMatrix4x4 const& lhs, CFMatrix4x4 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}