/**	@file	CFVector3.cpp
 *	@brief	単精度浮動小数点数型三次元ベクトル
 */
#include "math/CFVector3.hpp"
#include "math/Math.hpp"
#include <immintrin.h>

namespace dlav {
	CFVector3::CFVector3() noexcept :
		SFloat3()
	{}

	CFVector3::CFVector3(std::initializer_list<float> const& args) noexcept :
		SFloat3()
	{
		unsigned int idx = 0U;
		for (auto& arg : args) {
			if (idx >= FLT3_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	CFVector3& CFVector3::operator+=(CFVector3 const& rhs) noexcept {
		_mm_store_ps(p, _mm_add_ps(_mm_load_ps(p), _mm_load_ps(rhs.p)));
		return *this;
	}

	CFVector3& CFVector3::operator-=(CFVector3 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFVector3& CFVector3::operator*=(float const& rhs) noexcept {
		_mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_set1_ps(rhs)));
		return *this;
	}

	CFVector3& CFVector3::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFVector3 const CFVector3::normalize() const noexcept {
		float magnitude = norm();
		return magnitude > 0.0f ? *this / magnitude : ZERO_FVT3;
	}

	float const CFVector3::sqnorm() const noexcept {
		return dot(*this, *this);
	}

	float const CFVector3::norm() const noexcept {
		return sqrt(sqnorm());
	}

	CFVector3 const CFVector3::operator+() const noexcept {
		return *this;
	}

	CFVector3 const CFVector3::operator-() const noexcept {
		return *this * -1.0f;
	}

	float const dot(CFVector3 const& lhs, CFVector3 const& rhs) noexcept {
		float tmp[4U];
		_mm_store_ps(tmp, _mm_mul_ps(_mm_load_ps(lhs.p), _mm_load_ps(rhs.p)));
		return sum(tmp, 4U);
	}

	CFVector3 const cross(CFVector3 const& vt1, CFVector3 const& vt2) noexcept {
		CFVector3 result;
		_mm_store_ps(result.p, sum({
			_mm_set_ps(0.0f,  vt1.x * vt2.y,   vt1.z * vt2.x,   vt1.y * vt2.z),
			_mm_set_ps(0.0f,-(vt1.y * vt2.x),-(vt1.x * vt2.z),-(vt1.z * vt2.y))
			}));
		return result;
	}

	CFVector3 const operator+(CFVector3 const& lhs, CFVector3 const& rhs) noexcept {
		CFVector3 result = lhs;
		result += rhs;
		return result;
	}

	CFVector3 const operator-(CFVector3 const& lhs, CFVector3 const& rhs) noexcept {
		CFVector3 result = lhs;
		result -= rhs;
		return result;
	}

	CFVector3 const operator*(CFVector3 const& lhs, float const& rhs) noexcept {
		CFVector3 result = lhs;
		result *= rhs;
		return result;
	}

	CFVector3 const operator*(float const& lhs, CFVector3 const& rhs) noexcept {
		return rhs * lhs;
	}

	CFVector3 const operator/(CFVector3 const& lhs, float const& rhs) noexcept {
		CFVector3 result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(CFVector3 const& lhs, CFVector3 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < FLT3_CNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFVector3 const& lhs, CFVector3 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}