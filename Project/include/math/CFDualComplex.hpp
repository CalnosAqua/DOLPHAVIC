/**	@file	CFDualComplex.hpp
 *	@brief	双対複素数
 */
#pragma once
#include "CFComplex.hpp"

namespace dlav {
	/**	@class	CFDualComplex
	 *	@brief	双対複素数
	 */
	class CFDualComplex final {
	public	:
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 2U;
		union {
			//!	@brief	全成分
			CFComplex p[COUNT];
			struct {
				//!	@brief	実数成分
				CFComplex re;
				//!	@brief	虚数成分
				CFComplex im;
			};
		};
		//!	@brief	ムーブコンストラクタ
		CFDualComplex(CFDualComplex&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFDualComplex(CFDualComplex const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFDualComplex& operator=(CFDualComplex&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFDualComplex& operator=(CFDualComplex const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFDualComplex() noexcept;
		//!	@brief	デストラクタ
		~CFDualComplex() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFDualComplex(CFComplex const& x, CFComplex const& y) noexcept :
			p{ x, y }
		{}
		//!	@brief	コンストラクタ
		explicit CFDualComplex(std::initializer_list<CFComplex> const&) noexcept;

		//!	@brief	複合加算演算子
		CFDualComplex& operator+=(CFDualComplex const&) noexcept;
		//!	@brief	複合減算演算子
		CFDualComplex& operator-=(CFDualComplex const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFDualComplex& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFDualComplex& operator/=(float const&) noexcept;

		//!	@brief	正規化関数
		CFDualComplex const normalize() const noexcept;
		//!	@brief	共役生成関数
		CFDualComplex const conj() const noexcept;
		//!	@brief	逆元生成関数
		CFDualComplex const inv() const noexcept;
		//!	@brief	ノルム二乗関数
		float const sqnorm() const noexcept;
		//!	@brief	ノルム関数
		float const norm() const noexcept;

		//!	@brief	単項加算演算子
		CFDualComplex const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFDualComplex const operator-() const noexcept;
	};
	//!	@brief	加算演算子
	CFDualComplex const operator+(CFDualComplex const&, CFDualComplex const&) noexcept;
	//!	@brief	減算演算子
	CFDualComplex const operator-(CFDualComplex const&, CFDualComplex const&) noexcept;
	//!	@brief	乗算演算子
	CFDualComplex const operator*(CFDualComplex const&, CFDualComplex const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFDualComplex const operator*(CFDualComplex const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFDualComplex const operator*(float const&, CFDualComplex const&) noexcept;
	//!	@brief	除算演算子
	CFDualComplex const operator/(CFDualComplex const&, CFDualComplex const&) noexcept;
	//!	@brief	スカラ割演算子
	CFDualComplex const operator/(CFDualComplex const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	CFDualComplex const operator/(float const&, CFDualComplex const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFDualComplex const&, CFDualComplex const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFDualComplex const&, CFDualComplex const&) noexcept;

	//!	@brief	単精度浮動小数点数型の零双対複素数
	static CFDualComplex constexpr ZERO_FDCMP = CFDualComplex(ZERO_FCMP, ZERO_FCMP);
	//!	@brief	単精度浮動小数点数型の単位双対複素数
	static CFDualComplex constexpr UNIT_FDCMP = CFDualComplex(UNIT_FCMP, ZERO_FCMP);
}