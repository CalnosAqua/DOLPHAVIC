/**	@file	CFVector4.hpp
 *	@brief	単精度浮動小数点数型四次元ベクトル
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat4.hpp"
#include <initializer_list>

namespace dlav {
	/**	@class	CFVector4
	 *	@brief	単精度浮動小数点数型四次元ベクトル
	 */
	class alignas(16) CFVector4 final : public SFloat4{
	public	:
		//!	@brief	ムーブコンストラクタ
		CFVector4(CFVector4&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFVector4(CFVector4 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFVector4& operator=(CFVector4&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFVector4& operator=(CFVector4 const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFVector4() noexcept;
		//!	@brief	デストラクタ
		~CFVector4() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFVector4(float const& x, float const& y, float const& z, float const& w) noexcept :
			SFloat4{ x, y, z, w }
		{}
		//!	@brief	コンストラクタ
		explicit CFVector4(std::initializer_list<float> const&) noexcept;

		//!	@brief	複合加算演算子
		CFVector4& operator+=(CFVector4 const&) noexcept;
		//!	@brief	複合減算演算子
		CFVector4& operator-=(CFVector4 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFVector4& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFVector4& operator/=(float const&) noexcept;

		//!	@brief	正規化関数
		CFVector4 const normalize() const noexcept;
		//!	@brief	ノルム二乗関数
		float const sqnorm() const noexcept;
		//!	@brief	ノルム関数
		float const norm() const noexcept;

		//!	@brief	単項加算演算子
		CFVector4 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFVector4 const operator-() const noexcept;
	};
	//!	@brief	内積関数
	float const dot(CFVector4 const&, CFVector4 const&) noexcept;
	//!	@brief	外積関数
	CFVector4 const cross(CFVector4 const&, CFVector4 const&, CFVector4 const&) noexcept;

	//!	@brief	加算演算子
	CFVector4 const operator+(CFVector4 const&, CFVector4 const&) noexcept;
	//!	@brief	減算演算子
	CFVector4 const operator-(CFVector4 const&, CFVector4 const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFVector4 const operator*(CFVector4 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFVector4 const operator*(float const&, CFVector4 const&) noexcept;
	//!	@brief	スカラ割演算子
	CFVector4 const operator/(CFVector4 const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFVector4 const&, CFVector4 const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFVector4 const&, CFVector4 const&) noexcept;

	//!	@brief	単精度浮動小数点数型の四次元ゼロベクトル
	static CFVector4 constexpr ZERO_FVT4 = CFVector4(0.0f, 0.0f, 0.0f, 0.0f);
}