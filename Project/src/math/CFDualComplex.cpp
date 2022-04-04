/**	@file	CFDualComplex.cpp
 *	@brief	双対複素数
 */
#include "math/CFDualComplex.hpp"
#include "math/Math.hpp"

namespace dlav {
	CFDualComplex::CFDualComplex() noexcept :
		CFDualComplex(ZERO_FCMP, ZERO_FCMP)
	{}

	CFDualComplex::CFDualComplex(std::initializer_list<CFComplex> const& args) noexcept :
		CFDualComplex()
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

	CFDualComplex& CFDualComplex::operator+=(CFDualComplex const& rhs) noexcept {
		re += rhs.re;
		im += rhs.im;
		return *this;
	}

	CFDualComplex& CFDualComplex::operator-=(CFDualComplex const& rhs) noexcept {
		re -= rhs.re;
		im -= rhs.im;
		return *this;
	}

	CFDualComplex& CFDualComplex::operator*=(float const& rhs) noexcept {
		re *= rhs;
		im *= rhs;
		return *this;
	}

	CFDualComplex& CFDualComplex::operator/=(float const& rhs) noexcept {
		re /= rhs;
		im /= rhs;
		return *this;
	}

	CFDualComplex const CFDualComplex::normalize() const noexcept {
		CFDualComplex result;
		float norm = this->norm();
		if (compare(norm, 0.0f) > 0) {
			result = *this;
			result /= norm;
		}
		return result;
	}

	CFDualComplex const CFDualComplex::conj() const noexcept {
		return CFDualComplex(re.conj(), -im);
	}

	CFDualComplex const CFDualComplex::inv() const noexcept {
		CFDualComplex result;
		float norm = sqnorm();
		if (compare(norm, 0.0f) > 0) {
			result = *this;
			result /= norm;
		}
		return result;
	}

	float const CFDualComplex::sqnorm() const noexcept {
		return re.sqnorm();
	}

	float const CFDualComplex::norm() const noexcept {
		return re.norm();
	}

	CFDualComplex const CFDualComplex::operator+() const noexcept {
		return *this;
	}

	CFDualComplex const CFDualComplex::operator-() const noexcept {
		return *this * -1.0f;
	}

	CFDualComplex const operator+(CFDualComplex const& lhs, CFDualComplex const& rhs) noexcept {
		CFDualComplex result = lhs;
		result += rhs;
		return result;
	}

	CFDualComplex const operator-(CFDualComplex const& lhs, CFDualComplex const& rhs) noexcept {
		CFDualComplex result = lhs;
		result -= rhs;
		return result;
	}

	CFDualComplex const operator*(CFDualComplex const& lhs, CFDualComplex const& rhs) noexcept {
		return CFDualComplex(lhs.re * rhs.re, lhs.re * rhs.im + lhs.im * rhs.re.conj());
	}

	CFDualComplex const operator*(CFDualComplex const& lhs, float const& rhs) noexcept {
		CFDualComplex result = lhs;
		result *= rhs;
		return result;
	}

	CFDualComplex const operator*(float const& lhs, CFDualComplex const& rhs) noexcept {
		return rhs * lhs;
	}

	CFDualComplex const operator/(CFDualComplex const& lhs, CFDualComplex const& rhs) noexcept {
		return lhs * rhs.inv();
	}

	CFDualComplex const operator/(CFDualComplex const& lhs, float const& rhs) noexcept {
		CFDualComplex result = lhs;
		result /= rhs;
		return result;
	}

	CFDualComplex const operator/(float const& lhs, CFDualComplex const& rhs) noexcept {
		return rhs.inv() * lhs;
	}

	bool const operator==(CFDualComplex const& lhs, CFDualComplex const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < CFDualComplex::COUNT; ++idx) {
			result = (lhs.p[idx] == rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFDualComplex const& lhs, CFDualComplex const& rhs) noexcept {
		return !(lhs == rhs);
	}
}