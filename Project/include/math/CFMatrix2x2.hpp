/**	@file	CFMatrix2x2.hpp
 *	@brief	単精度浮動小数点数型二次正方行列
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat2x2.hpp"
#include "CFVector2.hpp"
#include <initializer_list>

namespace dlav {
	/**	@file	CFMatrix2x2
	 *	@brief	単精度浮動小数点数型二次正方行列
	 */
	class alignas(16) CFMatrix2x2 final : public SFloat2x2 {
	public	:
		//!	@brief	ムーブコンストラクタ
		CFMatrix2x2(CFMatrix2x2&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFMatrix2x2(CFMatrix2x2 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFMatrix2x2& operator=(CFMatrix2x2&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFMatrix2x2& operator=(CFMatrix2x2 const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFMatrix2x2() noexcept;
		//!	@brief	デストラクタ
		~CFMatrix2x2() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFMatrix2x2(
			float const& m00, float const& m01,
			float const& m10, float const& m11
		) noexcept :
			SFloat2x2{
				m00, m01,
				m10, m11
			}
		{}
		//!	@brief	コンストラクタ
		explicit CFMatrix2x2(std::initializer_list<float> const&) noexcept;

		//!	@brief	行成分抽出関数
		CFMatrix2x2& row(unsigned int const&, CFVector2 const&) noexcept;
		//!	@brief	列成分抽出関数
		CFMatrix2x2& column(unsigned int const&, CFVector2 const&) noexcept;

		//!	@brief	行成分交換関数
		CFMatrix2x2& row_swap(unsigned int const& from, unsigned int const& to) noexcept;
		//!	@brief	列成分交換関数
		CFMatrix2x2& column_swap(unsigned int const& from, unsigned int const& to) noexcept;

		//!	@brief	行成分拡縮関数
		CFMatrix2x2& row_scale(unsigned int const&, float const&) noexcept;
		//!	@brief	列成分拡縮関数
		CFMatrix2x2& column_scale(unsigned int const&, float const&) noexcept;

		//!	@brief	行成分積和関数
		CFMatrix2x2& row_sop(unsigned int const& from, unsigned int const& to, float const&) noexcept;
		//!	@brief	列成分積和関数
		CFMatrix2x2& column_sop(unsigned int const& from, unsigned int const& to, float const&) noexcept;

		//!	@brief	複合加算演算子
		CFMatrix2x2& operator+=(CFMatrix2x2 const&) noexcept;
		//!	@brief	複合減算演算子
		CFMatrix2x2& operator-=(CFMatrix2x2 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFMatrix2x2& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFMatrix2x2& operator/=(float const&) noexcept;

		//!	@brief	行成分抽出関数
		CFVector2 const row(unsigned int const&) const noexcept;
		//!	@brief	列成分抽出関数
		CFVector2 const column(unsigned int const&) const noexcept;

		//!	@brief	余因子行列生成関数
		CFMatrix2x2 const adj() const noexcept;
		//!	@brief	逆行列生成関数
		CFMatrix2x2 const inv() const noexcept;
		//!	@brief	転置行列生成関数
		CFMatrix2x2 const transpose() const noexcept;
		//!	@brief	行列式計算関数
		float const det() const noexcept;

		//!	@brief	単項加算演算子
		CFMatrix2x2 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFMatrix2x2 const operator-() const noexcept;
	};
	//!	@brief	直積関数
	CFMatrix2x2 const direct(CFVector2 const&, CFVector2 const&) noexcept;
	//!	@brief	楔積関数
	CFMatrix2x2 const wedge(CFVector2 const&, CFVector2 const&) noexcept;

	//!	@brief	加算演算子
	CFMatrix2x2 const operator+(CFMatrix2x2 const&, CFMatrix2x2 const&) noexcept;
	//!	@brief	減算演算子
	CFMatrix2x2 const operator-(CFMatrix2x2 const&, CFMatrix2x2 const&) noexcept;
	//!	@brief	乗算演算子
	CFMatrix2x2 const operator*(CFMatrix2x2 const&, CFMatrix2x2 const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFMatrix2x2 const operator*(CFMatrix2x2 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFMatrix2x2 const operator*(float const&, CFMatrix2x2 const&) noexcept;
	//!	@brief	除算演算子
	CFMatrix2x2 const operator/(CFMatrix2x2 const&, CFMatrix2x2 const&) noexcept;
	//!	@brief	スカラ割演算子
	CFMatrix2x2 const operator/(CFMatrix2x2 const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	CFMatrix2x2 const operator/(float const&, CFMatrix2x2 const&) noexcept;

	//!	@brief	行列作用演算子
	CFVector2 const operator*(CFVector2 const&, CFMatrix2x2 const&) noexcept;
	//!	@brief	行列作用演算子
	CFVector2 const operator*(CFMatrix2x2 const&, CFVector2 const&) noexcept;

	//!	@brief	加算演算子
	bool const operator==(CFMatrix2x2 const&, CFMatrix2x2 const&) noexcept;
	//!	@brief	減算演算子
	bool const operator!=(CFMatrix2x2 const&, CFMatrix2x2 const&) noexcept;

	//!	@brief	零行列
	static CFMatrix2x2 constexpr ZERO_FMTX2x2 = CFMatrix2x2(
		0.0f, 0.0f,
		0.0f, 0.0f
	);
	//!	@brief	単位行列
	static CFMatrix2x2 constexpr UNIT_FMTX2x2 = CFMatrix2x2(
		1.0f, 0.0f,
		0.0f, 1.0f
	);
}