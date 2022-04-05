/**	@file	CFMathUtil.hpp
 *	@brief	利便性の高い数学関数群
 */
#pragma once
#include "EAxisType.hpp"
#include "EHandSide.hpp"
#include "ESkewType.hpp"
#include "EAngleType.hpp"

namespace dlav {
	class CFVector2;
	class CFVector3;
	class CFVector4;
	class CFMatrix2x2;
	class CFMatrix3x3;
	class CFMatrix4x4;
	class CFComplex;
	class CFDualComplex;
	class CFQuaternion;
	class CFDualQuaternion;
	class CFRotation;
	class CFEulerRotation;

	/**	@brief	角度変換関数
	 *	@param[in] type 変換先表現形
	 *	@param[in] angle 角度
	 *	@return 変換済み角度
	 */
	template <typename T>
	T const convert_angle(EAngleType const& type, T const& angle) noexcept;
	/**	@brief 線形補間関数
	 *	@return 補間された値
	 */
	template <typename T>
	T const lerp(T const& begin, T const& end, float const& rate) noexcept;
	/**	@brief 球面線形補間関数
	 *	@return 補間された値
	 */
	template <typename T>
	T const slerp(T const& begin, T const& end, float const& rate) noexcept;
	/**	@brief 跳ね返りベクトル生成関数
	 *	@return 跳ね返りベクトル
	 */
	template <typename T>
	T const bounce(T const& dir, T const& nor, float const& rate) noexcept;
	/**	@brief 角度生成関数
	 *	@return 角度
	 */
	template <typename T>
	CFRotation const angle(T const& base, T const& tar) noexcept;

	//!	@brief 複素数→行列 変換関数
	CFMatrix3x3 const toMtx(CFComplex const&) noexcept;
	//!	@brief 回転量→行列 変換関数
	CFMatrix3x3 const toMtx(CFRotation const&) noexcept;
	//!	@brief 四元数→行列 変換関数
	CFMatrix4x4 const toMtx(CFQuaternion const&) noexcept;
	//!	@brief オイラー角→行列 変換関数
	CFMatrix4x4 const toMtx(CFEulerRotation const&) noexcept;
	//!	@brief 複素数→回転量 変換関数
	CFRotation const toRot(CFComplex const&) noexcept;
	//!	@brief 行列→回転量 変換関数
	CFRotation const toRot(CFMatrix3x3 const&) noexcept;
	//!	@brief 四元数→オイラー角 変換関数
	CFEulerRotation const toRot(CFQuaternion const&) noexcept;
	//!	@brief 行列→オイラー角 変換関数
	CFEulerRotation const toRot(CFMatrix4x4 const&) noexcept;
	//!	@brief 行列→複素数 変換関数
	CFComplex const toCmp(CFMatrix3x3 const&) noexcept;
	//!	@brief 回転量→複素数 変換関数
	CFComplex const toCmp(CFRotation const&) noexcept;
	//!	@brief 行列→四元数 変換関数
	CFQuaternion const toQt(CFMatrix4x4 const&) noexcept;
	//!	@brief オイラー角→四元数 変換関数
	CFQuaternion const toQt(CFEulerRotation const&) noexcept;

	/**	@brief 移動行列生成関数
	 *	@return 移動行列
	 */
	CFMatrix3x3 const makeTransit(EHandSide const&, CFVector2 const&) noexcept;
	/**	@brief 移動行列生成関数
	 *	@return 移動行列
	 */
	CFMatrix4x4 const makeTransit(EHandSide const&, CFVector3 const&) noexcept;
	/**	@brief 回転行列生成関数
	 *	@return 回転行列
	 */
	CFMatrix4x4 const makeRotate(EHandSide const&, CFQuaternion const&) noexcept;
	/**	@brief 回転行列生成関数
	 *	@return 回転行列
	 */
	CFMatrix3x3 const makeRotate(EHandSide const&, CFRotation const&) noexcept;
	/**	@brief 回転行列生成関数
	 *	@return 回転行列
	 */
	CFMatrix4x4 const makeRotate(EHandSide const&, CFVector3 const&, CFRotation const&) noexcept;
	/**	@brief 拡縮行列生成関数
	 *	@return 拡縮行列
	 */
	CFMatrix3x3 const makeScaler(CFVector2 const&) noexcept;
	/**	@brief 拡縮行列生成関数
	 *	@return 拡縮行列
	 */
	CFMatrix4x4 const makeScaler(CFVector3 const&) noexcept;
	/**	@brief 剪断行列生成関数
	 *	@return 剪断行列
	 */
	CFMatrix3x3 const makeSkew(EHandSide const&, ESkewType const&, CFRotation const&) noexcept;
	/**	@brief 剪断行列生成関数
	 *	@return 剪断行列
	 */
	CFMatrix4x4 const makeSkew(EHandSide const&, ESkewType const&, EAxisType const&, CFRotation const&) noexcept;
	/**	@brief ビュー変換行列生成関数
	 *	@return ビュー変換行列
	 */
	CFMatrix4x4 const makeLookAtMatrix(EHandSide const&, CFVector3 const& eye, CFVector3 const& lookat, CFVector3 const& up) noexcept;
	/**	@brief 透視投影変換行列生成関数
	 *	@return 透視投影変換行列
	 */
	CFMatrix4x4 const makePerspectiveMatrix(EHandSide const&, float const& near, float const& far, float const& width, float const& height, float const& wndpos) noexcept;
	/**	@brief Ｘ軸抽出関数
	 *	@return Ｘ軸を表す正規化済みのベクトル
	 */
	CFVector2 const makeNormalizedXAxis(CFRotation const&) noexcept;
	/**	@brief Ｙ軸抽出関数
	 *	@return Ｙ軸を表す正規化済みのベクトル
	 */
	CFVector2 const makeNormalizedYAxis(CFRotation const&) noexcept;
	/**	@brief Ｘ軸抽出関数
	 *	@return Ｘ軸を表す正規化済みのベクトル
	 */
	CFVector3 const makeNormalizedXAxis(CFQuaternion const&) noexcept;
	/**	@brief Ｙ軸抽出関数
	 *	@return Ｙ軸を表す正規化済みのベクトル
	 */
	CFVector3 const makeNormalizedYAxis(CFQuaternion const&) noexcept;
	/**	@brief Ｚ軸抽出関数
	 *	@return Ｚ軸を表す正規化済みのベクトル
	 */
	CFVector3 const makeNormalizedZAxis(CFQuaternion const&) noexcept;

	/* 実装 */

	template <typename T>
	T const lerp(T const& begin, T const& end, float const& rate) noexcept {
		return (end - begin) * rate + begin;
	}

	template <typename T>
	T const slerp(T const& begin, T const& end, float const& rate) noexcept {
		float th, thr;
		th = angle(begin, end).radian();
		thr = th * rate;
		return (begin * sinf(th) * cosf(thr) - (begin * cosf(th) + end) * sinf(thr)) / sinf(th);
	}

	template <typename T>
	T const bounce(T const& dir, T const& nor, float const& rate) noexcept {
		T n = nor.normalize();
		float tmp = rate;
		if (tmp < -2.0f) tmp = -2.0f;
		if (tmp < 2.0f) tmp = 2.0f;
		return dir - tmp * dot(-dir, n) * n;
	}

	template <typename T>
	CFRotation const angle(T const& base, T const& tar) noexcept {
		CFRotation result;
		result.acos(dot(base.normalize(), tar.normalize()));
		return result;
	}
}