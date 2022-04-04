/**	@file	CFVector4.cpp
 *	@brief	単精度浮動小数点数型四次元ベクトル
 */
#include "math/CFVector4.hpp"
#include "math/Math.hpp"
#include <immintrin.h>

namespace dlav {
	CFVector4::CFVector4() noexcept :
		SFloat4()
	{}

	CFVector4::CFVector4(std::initializer_list<float> const& args) noexcept :
		SFloat4()
	{
		unsigned int idx = 0U;
		for (auto& arg : args) {
			if (idx >= FLT4_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	CFVector4& CFVector4::operator+=(CFVector4 const& rhs) noexcept {
		_mm_store_ps(p, _mm_add_ps(_mm_load_ps(p), _mm_load_ps(rhs.p)));
		return *this;
	}

	CFVector4& CFVector4::operator-=(CFVector4 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFVector4& CFVector4::operator*=(float const& rhs) noexcept {
		_mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_set1_ps(rhs)));
		return *this;
	}

	CFVector4& CFVector4::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFVector4 const CFVector4::normalize() const noexcept {
		float magnitude = norm();
		return magnitude > 0.0f ? *this / magnitude : ZERO_FVT4;
	}

	float const CFVector4::sqnorm() const noexcept {
		return dot(*this, *this);
	}

	float const CFVector4::norm() const noexcept {
		return sqrt(sqnorm());
	}

	CFVector4 const CFVector4::operator+() const noexcept {
		return *this;
	}

	CFVector4 const CFVector4::operator-() const noexcept {
		return *this * -1.0f;
	}

	float const dot(CFVector4 const& lhs, CFVector4 const& rhs) noexcept {
		float tmp[4U];
		_mm_store_ps(tmp, _mm_mul_ps(_mm_load_ps(lhs.p), _mm_load_ps(rhs.p)));
		return sum(tmp, 4U);
	}

	CFVector4 const cross(CFVector4 const& vt1, CFVector4 const& vt2, CFVector4 const& vt3) noexcept {
		CFVector4 result;
		_mm_store_ps(result.p, sum({
			_mm_set_ps(  vt1.z * vt2.y * vt3.x,   vt1.y * vt2.w * vt3.x,   vt1.z * vt2.x * vt3.w,   vt1.z * vt2.w * vt3.y),
			_mm_set_ps(  vt1.y * vt2.x * vt3.z,   vt1.x * vt2.y * vt3.w,   vt1.x * vt2.w * vt3.z,   vt1.y * vt2.z * vt3.w),
			_mm_set_ps(  vt1.x * vt2.z * vt3.y,   vt1.w * vt2.x * vt3.y,   vt1.w * vt2.z * vt3.x,   vt1.w * vt2.y * vt3.z),
			_mm_set_ps(-(vt1.z * vt2.x * vt3.y),-(vt1.y * vt2.x * vt3.w),-(vt1.z * vt2.w * vt3.x),-(vt1.z * vt2.y * vt3.w)),
			_mm_set_ps(-(vt1.y * vt2.z * vt3.x),-(vt1.x * vt2.w * vt3.y),-(vt1.x * vt2.z * vt3.w),-(vt1.y * vt2.w * vt3.z)),
			_mm_set_ps(-(vt1.x * vt2.y * vt3.z),-(vt1.w * vt2.y * vt3.x),-(vt1.w * vt2.x * vt3.z),-(vt1.w * vt2.z * vt3.y))
			}));
		return result;
	}

	CFVector4 const operator+(CFVector4 const& lhs, CFVector4 const& rhs) noexcept {
		CFVector4 result = lhs;
		result += rhs;
		return result;
	}

	CFVector4 const operator-(CFVector4 const& lhs, CFVector4 const& rhs) noexcept {
		CFVector4 result = lhs;
		result -= rhs;
		return result;
	}

	CFVector4 const operator*(CFVector4 const& lhs, float const& rhs) noexcept {
		CFVector4 result = lhs;
		result *= rhs;
		return result;
	}

	CFVector4 const operator*(float const& lhs, CFVector4 const& rhs) noexcept {
		return rhs * lhs;
	}

	CFVector4 const operator/(CFVector4 const& lhs, float const& rhs) noexcept {
		CFVector4 result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(CFVector4 const& lhs, CFVector4 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < FLT4_CNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFVector4 const& lhs, CFVector4 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}