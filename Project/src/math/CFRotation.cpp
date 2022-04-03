/**	@file	CFRotation.cpp
 *	@brief	単精度浮動小数点数型回転量
 */
#include "math/CFRotation.hpp"
#include "math/Math.hpp"
#include <array>

namespace dlav {
	CFRotation::CFRotation() noexcept :
		m_angle()
	{}

	CFRotation& CFRotation::radian(float const& arg) noexcept {
		m_angle = arg / PI<float>;
		return *this;
	}

	CFRotation& CFRotation::degree(float const& arg) noexcept {
		m_angle = arg / 180.0f;
		return *this;
	}

	CFRotation& CFRotation::asin(float const& arg) noexcept {
		m_angle = asinf(arg);
		return *this;
	}

	CFRotation& CFRotation::acos(float const& arg) noexcept {
		m_angle = acosf(arg);
		return *this;
	}

	CFRotation& CFRotation::atan(float const& arg) noexcept {
		m_angle = atanf(arg);
		return *this;
	}

	CFRotation& CFRotation::atan(float const& x, float const& y) noexcept {
		m_angle = atan2f(y, x);
		return *this;
	}

	CFRotation& CFRotation::operator+=(CFRotation const& rhs) noexcept {
		m_angle = sum({ m_angle, rhs.m_angle });
		return *this;
	}

	CFRotation& CFRotation::operator-=(CFRotation const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFRotation& CFRotation::operator*=(float const& rhs) noexcept {
		m_angle *= rhs;
		return *this;
	}

	CFRotation& CFRotation::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	float const CFRotation::radian() const noexcept {
		return m_angle * PI<float>;
	}

	float const CFRotation::degree() const noexcept {
		return m_angle * 180.0f;
	}

	float const CFRotation::sin() const noexcept {
		return sinf(radian());
	}

	float const CFRotation::cos() const noexcept {
		return cosf(radian());
	}

	float const CFRotation::tan() const noexcept {
		return tanf(radian());
	}

	CFRotation const CFRotation::anglize() const noexcept {
		CFRotation result = *this;
		while (result.m_angle < -1.0f) {
			result.m_angle = sum({ result.m_angle, 2.0f });
		}
		while (result.m_angle > 1.0f) {
			result.m_angle = sum({ result.m_angle, -2.0f });
		}
		return result;
	}

	int const CFRotation::round() const noexcept {
		return static_cast<int>(m_angle / 2.0f);
	}

	CFRotation const CFRotation::operator+() const noexcept {
		return *this;
	}

	CFRotation const CFRotation::operator-() const noexcept {
		return *this * -1.0f;
	}

	int const compare(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		return compare(lhs.m_angle, rhs.m_angle);
	}

	CFRotation const operator+(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		CFRotation result = lhs;
		result += rhs;
		return result;
	}

	CFRotation const operator-(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		CFRotation result = lhs;
		result -= rhs;
		return result;
	}

	CFRotation const operator*(CFRotation const& lhs, float const& rhs) noexcept {
		CFRotation result = lhs;
		result *= rhs;
		return result;
	}

	CFRotation const operator*(float const& lhs, CFRotation const& rhs) noexcept {
		return rhs * lhs;
	}

	CFRotation const operator/(CFRotation const& lhs, float const& rhs) noexcept {
		CFRotation result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		return !compare(lhs, rhs);
	}

	bool const operator!=(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		return compare(lhs, rhs);
	}

	bool const operator<=(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		return compare(lhs, rhs) <= 0;
	}

	bool const operator>=(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		return compare(lhs, rhs) >= 0;
	}

	bool const operator<(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		return compare(lhs, rhs) < 0;
	}

	bool const operator>(CFRotation const& lhs, CFRotation const& rhs) noexcept {
		return compare(lhs, rhs) > 0;
	}
}