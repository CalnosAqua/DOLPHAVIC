/**	@file	CFDualQuaternion.cpp
 *	@brief	双対四元数
 */
#include "math/CFDualQuaternion.hpp"
#include "math/Math.hpp"

namespace dlav {
	CFDualQuaternion::CFDualQuaternion() noexcept :
		CFDualQuaternion(ZERO_FQT, ZERO_FQT)
	{}

	CFDualQuaternion::CFDualQuaternion(std::initializer_list<CFQuaternion> const& args) noexcept :
		CFDualQuaternion()
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

	CFDualQuaternion& CFDualQuaternion::operator+=(CFDualQuaternion const& rhs) noexcept {
		re += rhs.re;
		im += rhs.im;
		return *this;
	}

	CFDualQuaternion& CFDualQuaternion::operator-=(CFDualQuaternion const& rhs) noexcept {
		re -= rhs.re;
		im -= rhs.im;
		return *this;
	}

	CFDualQuaternion& CFDualQuaternion::operator*=(float const& rhs) noexcept {
		re *= rhs;
		im *= rhs;
		return *this;
	}

	CFDualQuaternion& CFDualQuaternion::operator/=(float const& rhs) noexcept {
		re /= rhs;
		im /= rhs;
		return *this;
	}

	CFDualQuaternion const CFDualQuaternion::normalize() const noexcept {
		float magnitude = norm();
		return compare(magnitude, 0.0f) > 0U ? *this / magnitude : ZERO_FDQT;
	}

	CFDualQuaternion const CFDualQuaternion::conj() const noexcept {
		return CFDualQuaternion(re.conj(), -im);
	}

	CFDualQuaternion const CFDualQuaternion::inv() const noexcept {
		float magnitude = sqnorm();
		return compare(magnitude, 0.0f) > 0U ? conj() / magnitude : ZERO_FDQT;
	}

	float const CFDualQuaternion::sqnorm() const noexcept {
		return re.sqnorm();
	}

	float const CFDualQuaternion::norm() const noexcept {
		return re.norm();
	}

	CFDualQuaternion const CFDualQuaternion::operator+() const noexcept {
		return *this;
	}

	CFDualQuaternion const CFDualQuaternion::operator-() const noexcept {
		return *this * -1.0f;
	}

	CFDualQuaternion const operator+(CFDualQuaternion const& lhs, CFDualQuaternion const& rhs) noexcept {
		CFDualQuaternion result = lhs;
		result += rhs;
		return result;
	}

	CFDualQuaternion const operator-(CFDualQuaternion const& lhs, CFDualQuaternion const& rhs) noexcept {
		CFDualQuaternion result = lhs;
		result -= rhs;
		return result;
	}

	CFDualQuaternion const operator*(CFDualQuaternion const& lhs, CFDualQuaternion const& rhs) noexcept {
		return CFDualQuaternion(lhs.re * rhs.re, lhs.re * rhs.im + lhs.im * rhs.re);
	}

	CFDualQuaternion const operator*(CFDualQuaternion const& lhs, float const& rhs) noexcept {
		CFDualQuaternion result = lhs;
		result *= rhs;
		return result;
	}

	CFDualQuaternion const operator*(float const& lhs, CFDualQuaternion const& rhs) noexcept {
		return rhs * lhs;
	}

	CFDualQuaternion const operator/(CFDualQuaternion const& lhs, CFDualQuaternion const& rhs) noexcept {
		return lhs * rhs.inv();
	}

	CFDualQuaternion const operator/(CFDualQuaternion const& lhs, float const& rhs) noexcept {
		CFDualQuaternion result = lhs;
		result /= rhs;
		return result;
	}

	CFDualQuaternion const operator/(float const& lhs, CFDualQuaternion const& rhs) noexcept {
		return rhs.inv() * lhs;
	}

	bool const operator==(CFDualQuaternion const& lhs, CFDualQuaternion const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < CFDualQuaternion::COUNT; ++idx) {
			result = (lhs.p[idx] == rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFDualQuaternion const& lhs, CFDualQuaternion const& rhs) noexcept {
		return !(lhs == rhs);
	}
}