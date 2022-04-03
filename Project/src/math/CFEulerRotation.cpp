/**	@file	CFEulerRotation.hpp
 *	@brief	単精度浮動小数点数型オイラー回転量
 */
#include "math/CFEulerRotation.hpp"
#include "math/Math.hpp"
#include <immintrin.h>

namespace dlav {
	CFEulerRotation::CFEulerRotation() noexcept :
		p{}
	{}

	CFEulerRotation& CFEulerRotation::operator+=(CFEulerRotation const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < COUNT; ++idx) {
			p[idx] += rhs.p[idx];
		}
		return *this;
	}

	CFEulerRotation& CFEulerRotation::operator-=(CFEulerRotation const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFEulerRotation& CFEulerRotation::operator*=(float const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < COUNT; ++idx) {
			p[idx] *= rhs;
		}
		return *this;
	}

	CFEulerRotation& CFEulerRotation::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFEulerRotation const CFEulerRotation::operator+() const noexcept {
		return *this;
	}

	CFEulerRotation const CFEulerRotation::operator-() const noexcept {
		return *this * -1.0f;
	}

	CFEulerRotation const operator+(CFEulerRotation const& lhs, CFEulerRotation const& rhs) noexcept {
		CFEulerRotation result = lhs;
		result += rhs;
		return result;
	}

	CFEulerRotation const operator-(CFEulerRotation const& lhs, CFEulerRotation const& rhs) noexcept {
		CFEulerRotation result = lhs;
		result -= rhs;
		return result;
	}

	CFEulerRotation const operator*(CFEulerRotation const& lhs, float const& rhs) noexcept {
		CFEulerRotation result = lhs;
		result *= rhs;
		return result;
	}

	CFEulerRotation const operator*(float const& lhs, CFEulerRotation const& rhs) noexcept {
		return rhs * lhs;
	}

	CFEulerRotation const operator/(CFEulerRotation const& lhs, float const& rhs) noexcept {
		CFEulerRotation result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(CFEulerRotation const& lhs, CFEulerRotation const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < CFEulerRotation::COUNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFEulerRotation const& lhs, CFEulerRotation const& rhs) noexcept {
		return !(lhs == rhs);
	}
}