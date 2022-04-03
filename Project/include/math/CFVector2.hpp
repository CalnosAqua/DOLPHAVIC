/**	@file	CFVector2.hpp
 *	@brief	単精度浮動小数点数型二次元ベクトル
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat2.hpp"
#include <initializer_list>

namespace dlav {
	/**	@class	CFVector2
	 *	@brief	単精度浮動小数点数型二次元ベクトル
	 */
	class alignas(16) CFVector2 final : public SFloat2{
	public	:
		//!	@brief	ムーブコンストラクタ
		CFVector2(CFVector2&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFVector2(CFVector2 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFVector2& operator=(CFVector2&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFVector2& operator=(CFVector2 const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFVector2() noexcept;
		//!	@brief	デストラクタ
		~CFVector2() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFVector2(float const& x, float const& y) noexcept :
			SFloat2{ x, y }
		{}
		//!	@brief	コンストラクタ
		explicit CFVector2(std::initializer_list<float> const&) noexcept;

		//!	@brief	複合加算演算子
		CFVector2& operator+=(CFVector2 const&) noexcept;
		//!	@brief	複合減算演算子
		CFVector2& operator-=(CFVector2 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFVector2& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFVector2& operator/=(float const&) noexcept;

		//!	@brief	正規化関数
		CFVector2 const normalize() const noexcept;
		//!	@brief	ノルム二乗関数
		float const sqnorm() const noexcept;
		//!	@brief	ノルム関数
		float const norm() const noexcept;

		//!	@brief	単項加算演算子
		CFVector2 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFVector2 const operator-() const noexcept;
	};
	//!	@brief	内積関数
	float const dot(CFVector2 const&, CFVector2 const&) noexcept;
	//!	@brief	外積関数
	CFVector2 const cross(CFVector2 const&) noexcept;

	//!	@brief	加算演算子
	CFVector2 const operator+(CFVector2 const&, CFVector2 const&) noexcept;
	//!	@brief	減算演算子
	CFVector2 const operator-(CFVector2 const&, CFVector2 const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFVector2 const operator*(CFVector2 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFVector2 const operator*(float const&, CFVector2 const&) noexcept;
	//!	@brief	スカラ割演算子
	CFVector2 const operator/(CFVector2 const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFVector2 const&, CFVector2 const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFVector2 const&, CFVector2 const&) noexcept;

	//!	@brief	単精度浮動小数点数型の二次元ゼロベクトル
	static CFVector2 constexpr ZERO_FVT2 = CFVector2(0.0f, 0.0f);
}