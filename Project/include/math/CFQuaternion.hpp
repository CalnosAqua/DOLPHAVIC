/**	@file	CFQuaternion.hpp
 *	@brief	単精度浮動小数点数型四元数
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat4.hpp"
#include <initializer_list>

namespace dlav {
	/**	@class	CFQuaternion
	 *	@brief	単精度浮動小数点数型四元数
	 */
	class alignas(16) CFQuaternion final : public SFloat4{
	public	:
		//!	@brief	ムーブコンストラクタ
		CFQuaternion(CFQuaternion&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFQuaternion(CFQuaternion const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFQuaternion& operator=(CFQuaternion&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFQuaternion& operator=(CFQuaternion const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFQuaternion() noexcept;
		//!	@brief	デストラクタ
		~CFQuaternion() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFQuaternion(float const& x, float const& y, float const& z, float const& w) noexcept :
			SFloat4{ x, y, z, w }
		{}
		//!	@brief	コンストラクタ
		explicit CFQuaternion(std::initializer_list<float> const&) noexcept;

		//!	@brief	複合加算演算子
		CFQuaternion& operator+=(CFQuaternion const&) noexcept;
		//!	@brief	複合減算演算子
		CFQuaternion& operator-=(CFQuaternion const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFQuaternion& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFQuaternion& operator/=(float const&) noexcept;

		//!	@brief	正規化関数
		CFQuaternion const normalize() const noexcept;
		//!	@brief	共役生成関数
		CFQuaternion const conj() const noexcept;
		//!	@brief	逆元生成関数
		CFQuaternion const inv() const noexcept;
		//!	@brief	ノルム二乗関数
		float const sqnorm() const noexcept;
		//!	@brief	ノルム関数
		float const norm() const noexcept;

		//!	@brief	単項加算演算子
		CFQuaternion const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFQuaternion const operator-() const noexcept;
	};
	//!	@brief	内積関数
	float const dot(CFQuaternion const&, CFQuaternion const&) noexcept;

	//!	@brief	加算演算子
	CFQuaternion const operator+(CFQuaternion const&, CFQuaternion const&) noexcept;
	//!	@brief	減算演算子
	CFQuaternion const operator-(CFQuaternion const&, CFQuaternion const&) noexcept;
	//!	@brief	乗算演算子
	CFQuaternion const operator*(CFQuaternion const&, CFQuaternion const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFQuaternion const operator*(CFQuaternion const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFQuaternion const operator*(float const&, CFQuaternion const&) noexcept;
	//!	@brief	除算演算子
	CFQuaternion const operator/(CFQuaternion const&, CFQuaternion const&) noexcept;
	//!	@brief	スカラ割演算子
	CFQuaternion const operator/(CFQuaternion const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	CFQuaternion const operator/(float const&, CFQuaternion const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFQuaternion const&, CFQuaternion const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFQuaternion const&, CFQuaternion const&) noexcept;

	//!	@brief	単精度浮動小数点数型の二次元零四元数
	static CFQuaternion constexpr ZERO_FQT = CFQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
	//!	@brief	単精度浮動小数点数型の単位四元数
	static CFQuaternion constexpr UNIT_FQT = CFQuaternion(0.0f, 0.0f, 0.0f, 1.0f);
}