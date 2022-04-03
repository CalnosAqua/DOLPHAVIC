/**	@file	CFVector3.hpp
 *	@brief	単精度浮動小数点数型三次元ベクトル
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat3.hpp"
#include <initializer_list>

namespace dlav {
	/**	@class	CFVector3
	 *	@brief	単精度浮動小数点数型三次元ベクトル
	 */
	class alignas(16) CFVector3 final : public SFloat3{
	public	:
		//!	@brief	ムーブコンストラクタ
		CFVector3(CFVector3&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFVector3(CFVector3 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFVector3& operator=(CFVector3&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFVector3& operator=(CFVector3 const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFVector3() noexcept;
		//!	@brief	デストラクタ
		~CFVector3() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFVector3(float const& x, float const& y, float const& z) noexcept :
			SFloat3{ x, y, z }
		{}
		//!	@brief	コンストラクタ
		explicit CFVector3(std::initializer_list<float> const&) noexcept;

		//!	@brief	複合加算演算子
		CFVector3& operator+=(CFVector3 const&) noexcept;
		//!	@brief	複合減算演算子
		CFVector3& operator-=(CFVector3 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFVector3& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFVector3& operator/=(float const&) noexcept;

		//!	@brief	正規化関数
		CFVector3 const normalize() const noexcept;
		//!	@brief	ノルム二乗関数
		float const sqnorm() const noexcept;
		//!	@brief	ノルム関数
		float const norm() const noexcept;

		//!	@brief	単項加算演算子
		CFVector3 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFVector3 const operator-() const noexcept;
	};
	//!	@brief	内積関数
	float const dot(CFVector3 const&, CFVector3 const&) noexcept;
	//!	@brief	外積関数
	CFVector3 const cross(CFVector3 const&, CFVector3 const&) noexcept;

	//!	@brief	加算演算子
	CFVector3 const operator+(CFVector3 const&, CFVector3 const&) noexcept;
	//!	@brief	減算演算子
	CFVector3 const operator-(CFVector3 const&, CFVector3 const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFVector3 const operator*(CFVector3 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFVector3 const operator*(float const&, CFVector3 const&) noexcept;
	//!	@brief	スカラ割演算子
	CFVector3 const operator/(CFVector3 const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFVector3 const&, CFVector3 const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFVector3 const&, CFVector3 const&) noexcept;

	//!	@brief	単精度浮動小数点数型の三次元ゼロベクトル
	static CFVector3 constexpr ZERO_FVT3 = CFVector3(0.0f, 0.0f, 0.0f);
}