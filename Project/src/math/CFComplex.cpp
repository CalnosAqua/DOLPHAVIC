/**	@file	CFComplex.cpp
 *	@brief	単精度浮動小数点数型複素数
 */
#include "math/CFComplex.hpp"
#include "math/Math.hpp"
#include <immintrin.h>
#include <array>

namespace dlav {
	CFComplex::CFComplex() noexcept :
		SFloat2()
	{}

	CFComplex::CFComplex(std::initializer_list<float> const& args) noexcept :
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

	CFComplex& CFComplex::operator+=(CFComplex const& rhs) noexcept {
		_mm_store_ps(p, _mm_add_ps(_mm_load_ps(p), _mm_load_ps(rhs.p)));
		return *this;
	}

	CFComplex& CFComplex::operator-=(CFComplex const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFComplex& CFComplex::operator*=(CFComplex const& rhs) noexcept {
		_mm_store_ps(p, sum({
			_mm_set_ps(0.0f, 0.0f, x * rhs.y,   x * rhs.x),
			_mm_set_ps(0.0f, 0.0f, y * rhs.x, -(y * rhs.y)),
			}));
		return *this;
	}

	CFComplex& CFComplex::operator*=(float const& rhs) noexcept {
		_mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_set1_ps(rhs)));
		return *this;
	}

	CFComplex& CFComplex::operator/=(CFComplex const& rhs) noexcept {
		*this *= rhs.inv();
		return *this;
	}

	CFComplex& CFComplex::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFComplex const CFComplex::normalize() const noexcept {
		CFComplex result;
		float norm = this->norm();
		if (compare(norm, 0.0f) > 0) {
			result = *this;
			result /= norm;
		}
		return result;
	}

	CFComplex const CFComplex::conj() const noexcept {
		CFComplex result = *this;
		result.y *= -1.0f;
		return result;
	}

	CFComplex const CFComplex::inv() const noexcept {
		CFComplex result;
		float norm = sqnorm();
		if (compare(norm, 0.0f) > 0) {
			result = *this;
			result /= norm;
		}
		return result;
	}

	float const CFComplex::sqnorm() const noexcept {
		return dot(*this, *this);
	}

	float const CFComplex::norm() const noexcept {
		return sqrt(sqnorm());
	}

	CFComplex const CFComplex::operator+() const noexcept {
		return *this;
	}

	CFComplex const CFComplex::operator-() const noexcept {
		return *this * -1.0f;
	}

	float const dot(CFComplex const& lhs, CFComplex const& rhs) noexcept {
		float tmp[4U];
		_mm_store_ps(tmp, _mm_mul_ps(_mm_load_ps(lhs.p), _mm_load_ps(rhs.p)));
		return sum(tmp, 4U);
	}

	CFComplex const operator+(CFComplex const& lhs, CFComplex const& rhs) noexcept {
		CFComplex result = lhs;
		result += rhs;
		return result;
	}

	CFComplex const operator-(CFComplex const& lhs, CFComplex const& rhs) noexcept {
		CFComplex result = lhs;
		result -= rhs;
		return result;
	}

	CFComplex const operator*(CFComplex const& lhs, CFComplex const& rhs) noexcept {
		CFComplex result = lhs;
		result *= rhs;
		return result;
	}

	CFComplex const operator*(CFComplex const& lhs, float const& rhs) noexcept {
		CFComplex result = lhs;
		result *= rhs;
		return result;
	}

	CFComplex const operator*(float const& lhs, CFComplex const& rhs) noexcept {
		return rhs * lhs;
	}

	CFComplex const operator/(CFComplex const& lhs, CFComplex const& rhs) noexcept {
		CFComplex result = lhs;
		result /= rhs;
		return result;
	}

	CFComplex const operator/(CFComplex const& lhs, float const& rhs) noexcept {
		CFComplex result = lhs;
		result /= rhs;
		return result;
	}

	CFComplex const operator/(float const& lhs, CFComplex const& rhs) noexcept {
		return rhs.inv() * lhs;
	}

	bool const operator==(CFComplex const& lhs, CFComplex const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < FLT2_CNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFComplex const& lhs, CFComplex const& rhs) noexcept {
		return !(lhs == rhs);
	}
}