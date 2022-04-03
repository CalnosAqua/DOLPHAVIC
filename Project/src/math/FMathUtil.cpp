#include "math/FMathUtil.hpp"
#include "math/Math.hpp"
#include "math/CFMatrix2x2.hpp"
#include "math/CFMatrix3x3.hpp"
#include "math/CFMatrix4x4.hpp"
#include "math/CFDualComplex.hpp"
#include "math/CFDualQuaternion.hpp"
#include "math/CFEulerRotation.hpp"
#include <numeric>

namespace dlav {
	template <>
	float const convert_angle<float>(EAngleType const& type, float const& angle) noexcept {
		float temp = 0.0f;
		switch (type) {
		case EAngleType::DEGREE:
			temp = 180.0f / PI<float>;
			break;
		case EAngleType::RADIAN:
			temp = PI<float> / 180.0f;
			break;
		}
		return angle * temp;
	}

	template <>
	double const convert_angle<double>(EAngleType const& type, double const& angle) noexcept {
		double temp = 0.0;
		switch (type) {
		case EAngleType::DEGREE:
			temp = 180.0 / PI<double>;
			break;
		case EAngleType::RADIAN:
			temp = PI<double> / 180.0;
			break;
		}
		return angle * temp;
	}

	CFMatrix3x3 const toMtx(CFComplex const& arg) noexcept {
		CFMatrix3x3 result;
		float sin, cos;

		sin = arg.y;
		cos = arg.x;

		result.m00 = result.m11 = cos;
		result.m01 = -sin;
		result.m10 = +sin;

		return result;
	}

	CFMatrix4x4 const toMtx(CFQuaternion const& arg) noexcept {
		CFMatrix4x4 result;

		result.m00 = sum({ arg.x * arg.x, -(arg.y * arg.y), -(arg.z * arg.z), arg.w * arg.w });
		result.m11 = sum({ -(arg.x * arg.x), arg.y * arg.y, -(arg.z * arg.z), arg.w * arg.w });
		result.m22 = sum({ -(arg.x * arg.x), -(arg.y * arg.y), arg.z * arg.z, arg.w * arg.w });

		result.m21 = 2.0f * sum({ arg.y * arg.z, arg.x * arg.w });
		result.m10 = 2.0f * sum({ arg.x * arg.y, arg.z * arg.w });
		result.m02 = 2.0f * sum({ arg.x * arg.z, arg.y * arg.w });

		result.m01 = 2.0f * sum({ arg.x * arg.y, -(arg.z * arg.w) });
		result.m12 = 2.0f * sum({ arg.y * arg.z, -(arg.x * arg.w) });
		result.m20 = 2.0f * sum({ arg.x * arg.z, -(arg.y * arg.w) });

		return result;
	}

	CFMatrix3x3 const toMtx(CFRotation const& arg) noexcept {
		static CFMatrix3x3 result;
		float sin, cos;

		sin = arg.sin();
		cos = arg.cos();

		result.m00 = result.m11 = cos;
		result.m01 = -sin;
		result.m10 = +sin;

		return result;
	}

	CFMatrix4x4 const toMtx(CFEulerRotation const& arg) noexcept {
		CFMatrix4x4 pitch, yaw, roll;

		pitch.m11 = pitch.m22 = arg.pitch.cos();
		yaw.m00 = yaw.m22 = arg.yaw.cos();
		roll.m00 = roll.m11 = arg.roll.cos();

		pitch.m12 = pitch.m12 = arg.pitch.sin();
		yaw.m02 = yaw.m20 = arg.yaw.sin();
		roll.m01 = roll.m10 = arg.roll.sin();

		pitch.m12 *= -1.0f;
		yaw.m20 *= -1.0f;
		roll.m01 *= -1.0f;

		return pitch * yaw * roll;
	}

	CFRotation const toRot(CFComplex const& arg) noexcept {
		CFRotation result;
		result.atan(arg.x, arg.y);
		return result;
	}

	CFEulerRotation const toRot(CFQuaternion const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return CFEulerRotation();
	}

	CFRotation const toRot(CFMatrix3x3 const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return CFRotation();
	}

	CFEulerRotation const toRot(CFMatrix4x4 const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return CFEulerRotation();
	}

	CFComplex const toCmp(CFMatrix3x3 const&) noexcept {
		// TODO : 変換式を調べて実装する。
		return CFComplex();
	}

	CFQuaternion const toQt(CFMatrix4x4 const& arg) noexcept {
		float mult, v, biggest = FLT_MIN;
		unsigned long int i = 0U;
		CFQuaternion result = ZERO_FQT;
		CFVector4 tmp = ZERO_FVT4;

		tmp.x = sum({ arg.m00, -arg.m11, -arg.m22, 1.0f });
		tmp.y = sum({ -arg.m00,  arg.m11, -arg.m22, 1.0f });
		tmp.z = sum({ -arg.m00, -arg.m11,  arg.m22, 1.0f });
		tmp.w = sum({ arg.m00,  arg.m11,  arg.m22, 1.0f });

		for (unsigned long int idx = 0U; idx < 4U; idx++) {
			if (biggest > tmp.p[idx]) {
				biggest = tmp.p[idx];
				i = idx;
			}
		}
		if (tmp.p[i] < 0.0f) {
			return result;
		}

		v = sqrt(tmp.p[i]) * 0.5f;
		mult = 0.25f / v;
		result.p[i] = v;
		switch (i) {
		case 0:
			result.y = sum({ arg.m01,  arg.m10 }) * mult;
			result.z = sum({ arg.m20,  arg.m02 }) * mult;
			result.w = sum({ arg.m12, -arg.m21 }) * mult;
			break;
		case 1:
			result.x = sum({ arg.m01,  arg.m10 }) * mult;
			result.z = sum({ arg.m12,  arg.m21 }) * mult;
			result.w = sum({ arg.m20, -arg.m02 }) * mult;
			break;
		case 2:
			result.x = sum({ arg.m20,  arg.m02 }) * mult;
			result.y = sum({ arg.m12,  arg.m21 }) * mult;
			result.w = sum({ arg.m01, -arg.m10 }) * mult;
			break;
		case 3:
			result.x = sum({ arg.m12, -arg.m21 }) * mult;
			result.y = sum({ arg.m20, -arg.m02 }) * mult;
			result.z = sum({ arg.m01, -arg.m10 }) * mult;
			break;
		}

		return result;
	}

	CFComplex const toCmp(CFRotation const& arg) noexcept {
		CFComplex result;
		result.x = arg.cos();
		result.y = arg.sin();
		return result;
	}

	CFQuaternion const toQt(CFEulerRotation const& arg) noexcept {
		CFQuaternion pitch, yaw, roll;
		pitch.w = arg.pitch.cos();
		pitch.x = arg.pitch.sin();
		yaw.w = arg.yaw.cos();
		yaw.y = arg.yaw.sin();
		roll.w = arg.roll.cos();
		roll.z = arg.roll.sin();
		return pitch * yaw * roll;
	}

	CFMatrix3x3 const makeTransit(EHandSide const& hs, CFVector2 const& vt) noexcept {
		CFMatrix3x3 tmp = UNIT_FMTX3x3;
		switch (hs) {
		case EHandSide::LHS:
			tmp.m02 = vt.x;
			tmp.m12 = vt.y;
			break;
		case EHandSide::RHS:
			tmp.m20 = vt.x;
			tmp.m21 = vt.y;
			break;
		}
		return tmp;
	}

	CFMatrix4x4 const makeTransit(EHandSide const& hs, CFVector3 const& vt) noexcept {
		CFMatrix4x4 tmp = UNIT_FMTX4x4;
		switch (hs) {
		case EHandSide::LHS:
			tmp.m03 = vt.x;
			tmp.m13 = vt.y;
			tmp.m23 = vt.z;
			break;
		case EHandSide::RHS:
			tmp.m30 = vt.x;
			tmp.m31 = vt.y;
			tmp.m32 = vt.z;
			break;
		}
		return tmp;
	}

	CFMatrix4x4 const makeRotate(EHandSide const& hs, CFQuaternion const& qt) noexcept {
		CFMatrix4x4 result = UNIT_FMTX4x4;

		result.m00 = sum({ qt.x * qt.x, -(qt.y * qt.y), -(qt.z * qt.z), qt.w * qt.w });
		result.m11 = sum({ -(qt.x * qt.x), qt.y * qt.y, -(qt.z * qt.z), qt.w * qt.w });
		result.m22 = sum({ -(qt.x * qt.x), -(qt.y * qt.y), qt.z * qt.z, qt.w * qt.w });

		result.m21 = 2.0f * sum({ qt.y * qt.z, qt.x * qt.w });
		result.m10 = 2.0f * sum({ qt.x * qt.y, qt.z * qt.w });
		result.m02 = 2.0f * sum({ qt.x * qt.z, qt.y * qt.w });

		result.m01 = 2.0f * sum({ qt.x * qt.y, -(qt.z * qt.w) });
		result.m12 = 2.0f * sum({ qt.y * qt.z, -(qt.x * qt.w) });
		result.m20 = 2.0f * sum({ qt.x * qt.z, -(qt.y * qt.w) });

		return hs == EHandSide::LHS ? result.transpose() : result;
	}

	CFMatrix3x3 const makeRotate(EHandSide const& hs, CFRotation const& rot) noexcept {
		CFMatrix3x3 result = UNIT_FMTX3x3;

		result.m11 = result.m00 = rot.cos();
		result.m01 = result.m10 = rot.sin();
		result.m01 *= -1.0f;

		return hs == EHandSide::LHS ? result.transpose() : result;
	}

	CFMatrix4x4 const makeRotate(EHandSide const& hs, CFVector3 const& axis, CFRotation const& rot) noexcept {
		CFMatrix4x4 result;
		float sin = rot.sin(), cos = rot.cos();
		CFVector3 n = axis.normalize();

		result.m00 = cos + n.x * n.x * (1.0f - cos);
		result.m11 = cos + n.y * n.y * (1.0f - cos);
		result.m22 = cos + n.z * n.z * (1.0f - cos);

		result.m01 = n.x * n.y * (1.0f - cos) - n.z * sin;
		result.m12 = n.y * n.z * (1.0f - cos) - n.x * sin;
		result.m20 = n.x * n.z * (1.0f - cos) - n.y * sin;

		result.m10 = n.x * n.y * (1.0f - cos) + n.z * sin;
		result.m21 = n.y * n.z * (1.0f - cos) + n.x * sin;
		result.m02 = n.x * n.z * (1.0f - cos) + n.y * sin;

		return hs == EHandSide::LHS ? result.transpose() : result;
	}

	CFMatrix3x3 const makeScaler(CFVector2 const& vt) noexcept {
		CFMatrix3x3 tmp = UNIT_FMTX3x3;
		tmp.m00 = vt.x;
		tmp.m11 = vt.y;
		return tmp;
	}

	CFMatrix4x4 const makeScaler(CFVector3 const& vt) noexcept {
		CFMatrix4x4 tmp = UNIT_FMTX4x4;
		tmp.m00 = vt.x;
		tmp.m11 = vt.y;
		tmp.m22 = vt.z;
		return tmp;
	}

	CFMatrix3x3 const makeSkew(EHandSide const& hs, ESkewType const& st, CFRotation const& rot) noexcept {
		CFMatrix3x3 result = UNIT_FMTX3x3;
		switch (st) {
		case ESkewType::PRIMARY:
			result.m01 = rot.tan();
			break;
		case ESkewType::SECONDARY:
			result.m10 = rot.tan();
			break;
		}
		result = (hs == EHandSide::LHS) ? result.transpose() : result;
		return result;
	}

	CFMatrix4x4 const makeSkew(EHandSide const& hs, ESkewType const& st, EAxisType const& at, CFRotation const& rot) noexcept {
		CFMatrix4x4 result = UNIT_FMTX4x4;
		switch (at) {
		case EAxisType::X_AXIS:
			result.m21 = rot.tan();
			break;
		case EAxisType::Y_AXIS:
			result.m02 = rot.tan();
			break;
		case EAxisType::Z_AXIS:
			result.m01 = rot.tan();
			break;
		}
		result = (st == ESkewType::SECONDARY) ? result.transpose() : result;
		result = (hs == EHandSide::LHS) ? result.transpose() : result;
		return result;
	}
}