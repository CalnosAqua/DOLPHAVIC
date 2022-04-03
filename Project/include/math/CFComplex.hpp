/**	@file	CFComplex.hpp
 *	@brief	単精度浮動小数点数型複素数
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat2.hpp"
#include <initializer_list>

namespace dlav {
	/**	@class	CFComplex
	 *	@brief	単精度浮動小数点数型複素数
	 */
	class alignas(16) CFComplex final : public SFloat2{
	public	:
		//!	@brief	ムーブコンストラクタ
		CFComplex(CFComplex&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFComplex(CFComplex const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFComplex& operator=(CFComplex&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFComplex& operator=(CFComplex const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFComplex() noexcept;
		//!	@brief	デストラクタ
		~CFComplex() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFComplex(float const& x, float const& y) noexcept :
			SFloat2{ x, y }
		{}
		//!	@brief	コンストラクタ
		explicit CFComplex(std::initializer_list<float> const&) noexcept;

		//!	@brief	複合加算演算子
		CFComplex& operator+=(CFComplex const&) noexcept;
		//!	@brief	複合減算演算子
		CFComplex& operator-=(CFComplex const&) noexcept;
		//!	@brief	複合乗算演算子
		CFComplex& operator*=(CFComplex const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFComplex& operator*=(float const&) noexcept;
		//!	@brief	複合除算演算子
		CFComplex& operator/=(CFComplex const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFComplex& operator/=(float const&) noexcept;

		//!	@brief	正規化関数
		CFComplex const normalize() const noexcept;
		//!	@brief	共役生成関数
		CFComplex const conj() const noexcept;
		//!	@brief	逆元生成関数
		CFComplex const inv() const noexcept;
		//!	@brief	ノルム二乗関数
		float const sqnorm() const noexcept;
		//!	@brief	ノルム関数
		float const norm() const noexcept;

		//!	@brief	単項加算演算子
		CFComplex const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFComplex const operator-() const noexcept;
	};
	//!	@brief	内積関数
	float const dot(CFComplex const&, CFComplex const&) noexcept;

	//!	@brief	加算演算子
	CFComplex const operator+(CFComplex const&, CFComplex const&) noexcept;
	//!	@brief	減算演算子
	CFComplex const operator-(CFComplex const&, CFComplex const&) noexcept;
	//!	@brief	乗算演算子
	CFComplex const operator*(CFComplex const&, CFComplex const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFComplex const operator*(CFComplex const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFComplex const operator*(float const&, CFComplex const&) noexcept;
	//!	@brief	除算演算子
	CFComplex const operator/(CFComplex const&, CFComplex const&) noexcept;
	//!	@brief	スカラ割演算子
	CFComplex const operator/(CFComplex const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	CFComplex const operator/(float const&, CFComplex const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFComplex const&, CFComplex const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFComplex const&, CFComplex const&) noexcept;

	//!	@brief	単精度浮動小数点数型の二次元零複素数
	static CFComplex constexpr ZERO_FCMP = CFComplex(0.0f, 0.0f);
	//!	@brief	単精度浮動小数点数型の単位複素数
	static CFComplex constexpr UNIT_FCMP = CFComplex(1.0f, 0.0f);
}