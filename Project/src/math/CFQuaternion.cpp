/**	@file	CFQuaternion.cpp
 *	@brief	単精度浮動小数点数型四元数
 */
#include "math/CFQuaternion.hpp"
#include "math/Math.hpp"
#include <immintrin.h>

namespace dlav {
	CFQuaternion::CFQuaternion() noexcept :
		SFloat4()
	{}

	CFQuaternion::CFQuaternion(std::initializer_list<float> const& args) noexcept :
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

	CFQuaternion& CFQuaternion::operator+=(CFQuaternion const& rhs) noexcept {
		_mm_store_ps(p, _mm_add_ps(_mm_load_ps(p), _mm_load_ps(rhs.p)));
		return *this;
	}

	CFQuaternion& CFQuaternion::operator-=(CFQuaternion const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	CFQuaternion& CFQuaternion::operator*=(float const& rhs) noexcept {
		_mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_set1_ps(rhs)));
		return *this;
	}

	CFQuaternion& CFQuaternion::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	CFQuaternion const CFQuaternion::normalize() const noexcept {
		CFQuaternion result;
		float norm = this->norm();
		if (compare(norm, 0.0f) > 0) {
			result = *this;
			result /= norm;
		}
		return result;
	}

	CFQuaternion const CFQuaternion::conj() const noexcept {
		CFQuaternion result = *this;
		result.y *= -1.0f;
		return result;
	}

	CFQuaternion const CFQuaternion::inv() const noexcept {
		CFQuaternion result;
		float norm = sqnorm();
		if (compare(norm, 0.0f) > 0) {
			result = *this;
			result /= norm;
		}
		return result;
	}

	float const CFQuaternion::sqnorm() const noexcept {
		return dot(*this, *this);
	}

	float const CFQuaternion::norm() const noexcept {
		return sqrt(sqnorm());
	}

	CFQuaternion const CFQuaternion::operator+() const noexcept {
		return *this;
	}

	CFQuaternion const CFQuaternion::operator-() const noexcept {
		return *this * -1.0f;
	}

	float const dot(CFQuaternion const& lhs, CFQuaternion const& rhs) noexcept {
		float tmp[4U];
		_mm_store_ps(tmp, _mm_mul_ps(_mm_load_ps(lhs.p), _mm_load_ps(rhs.p)));
		return sum(tmp, 4U);
	}

	CFQuaternion const operator+(CFQuaternion const& lhs, CFQuaternion const& rhs) noexcept {
		CFQuaternion result = lhs;
		result += rhs;
		return result;
	}

	CFQuaternion const operator-(CFQuaternion const& lhs, CFQuaternion const& rhs) noexcept {
		CFQuaternion result = lhs;
		result -= rhs;
		return result;
	}

	CFQuaternion const operator*(CFQuaternion const& lhs, CFQuaternion const& rhs) noexcept {
		CFQuaternion result;
		_mm_store_ps(result.p, sum({
			_mm_set_ps(  lhs.w * rhs.w ,  lhs.z * rhs.w ,  lhs.y * rhs.w ,  lhs.x * rhs.w),
			_mm_set_ps(-(lhs.x * rhs.x),  lhs.w * rhs.z ,  lhs.w * rhs.y ,  lhs.w * rhs.x),
			_mm_set_ps(-(lhs.y * rhs.y),  lhs.x * rhs.y ,  lhs.z * rhs.x ,  lhs.y * rhs.z),
			_mm_set_ps(-(lhs.z * rhs.z),-(lhs.y * rhs.x),-(lhs.x * rhs.z),-(lhs.z * rhs.y))
			}));
		return result;
	}

	CFQuaternion const operator*(CFQuaternion const& lhs, float const& rhs) noexcept {
		CFQuaternion result = lhs;
		result *= rhs;
		return result;
	}

	CFQuaternion const operator*(float const& lhs, CFQuaternion const& rhs) noexcept {
		return rhs * lhs;
	}

	CFQuaternion const operator/(CFQuaternion const& lhs, CFQuaternion const& rhs) noexcept {
		CFQuaternion result;
		result = lhs * rhs.inv();
		return result;
	}

	CFQuaternion const operator/(CFQuaternion const& lhs, float const& rhs) noexcept {
		CFQuaternion result = lhs;
		result /= rhs;
		return result;
	}

	CFQuaternion const operator/(float const& lhs, CFQuaternion const& rhs) noexcept {
		return rhs.inv() * lhs;
	}

	bool const operator==(CFQuaternion const& lhs, CFQuaternion const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < FLT4_CNT; ++idx) {
			result = !compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(CFQuaternion const& lhs, CFQuaternion const& rhs) noexcept {
		return !(lhs == rhs);
	}
}