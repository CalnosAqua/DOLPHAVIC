/**	@file	CFVector2.cpp
 *	@brief	単精度浮動小数点数型二次元ベクトル
 */
#include "math/CFVector2.hpp"
#include "math/Math.hpp"
#include <immintrin.h>

namespace dlav {
	CFVector2::CFVector2() noexcept :
		SFloat2()
	{}

	CFVector2::CFVector2(std::initializer_list<float> const& args) noexcept :
		SFloat2()
	{
		unsigned int idx = 0U;
		for (auto& arg : args) {
			if (idx >= FLT2_CNT) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	CFVector2& CFVector2::operator+=(CFVector2 const& rhs) noexcept {
		_mm_store_ps(p, _mm_add_ps(_mm_load_ps(p), _mm_load_ps(rhs.p)));
		return *this;
	}

	CFVector2& CFVector2::operator-=(CFVector2 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFVector2& CFVector2::operator*=(float const& rhs) noexcept {
		_mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_set1_ps(rhs)));
		return *this;
	}

	CFVector2& CFVector2::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFVector2 const CFVector2::normalize() const noexcept {
		float magnitude = norm();
		return magnitude > 0.0f ? *this / magnitude : ZERO_FVT2;
	}

	float const CFVector2::sqnorm() const noexcept {
		return dot(*this, *this);
	}

	float const CFVector2::norm() const noexcept {
		return sqrt(sqnorm());
	}

	CFVector2 const CFVector2::operator+() const noexcept {
		return *this;
	}

	CFVector2 const CFVector2::operator-() const noexcept {
		return *this * -1.0f;
	}

	float const dot(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		float tmp[4U];
		_mm_store_ps(tmp, _mm_mul_ps(_mm_load_ps(lhs.p), _mm_load_ps(rhs.p)));
		return sum(tmp, 4U);
	}

	CFVector2 const cross(CFVector2 const& vt) noexcept {
		return CFVector2(vt.y, -vt.x);
	}

	CFVector2 const operator+(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		CFVector2 result = lhs;
		result += rhs;
		return result;
	}

	CFVector2 const operator-(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		CFVector2 result = lhs;
		result -= rhs;
		return result;
	}

	CFVector2 const operator*(CFVector2 const& lhs, float const& rhs) noexcept {
		CFVector2 result = lhs;
		result *= rhs;
		return result;
	}

	CFVector2 const operator*(float const& lhs, CFVector2 const& rhs) noexcept {
		return rhs * lhs;
	}

	CFVector2 const operator/(CFVector2 const& lhs, float const& rhs) noexcept {
		CFVector2 result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < FLT2_CNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFVector2 const& lhs, CFVector2 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}