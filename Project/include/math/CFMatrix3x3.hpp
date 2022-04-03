/**	@file	CFMatrix3x3.hpp
 *	@brief	単精度浮動小数点数型三次正方行列
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat3x3.hpp"
#include "CFVector3.hpp"
#include <initializer_list>

namespace dlav {
	/**	@file	CFMatrix3x3
	 *	@brief	単精度浮動小数点数型三次正方行列
	 */
	class alignas(16) CFMatrix3x3 final : public SFloat3x3{
	public	:
		//!	@brief	ムーブコンストラクタ
		CFMatrix3x3(CFMatrix3x3&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFMatrix3x3(CFMatrix3x3 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFMatrix3x3& operator=(CFMatrix3x3&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFMatrix3x3& operator=(CFMatrix3x3 const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFMatrix3x3() noexcept;
		//!	@brief	デストラクタ
		~CFMatrix3x3() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFMatrix3x3(
			float const& m00, float const& m01, float const& m02,
			float const& m10, float const& m11, float const& m12,
			float const& m20, float const& m21, float const& m22
		) noexcept :
			SFloat3x3{
				m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22
			}
		{}
		//!	@brief	コンストラクタ
		explicit CFMatrix3x3(std::initializer_list<float> const&) noexcept;

		//!	@brief	行成分抽出関数
		CFMatrix3x3& row(unsigned int const&, CFVector3 const&) noexcept;
		//!	@brief	列成分抽出関数
		CFMatrix3x3& column(unsigned int const&, CFVector3 const&) noexcept;

		//!	@brief	行成分交換関数
		CFMatrix3x3& row_swap(unsigned int const& from, unsigned int const& to) noexcept;
		//!	@brief	列成分交換関数
		CFMatrix3x3& column_swap(unsigned int const& from, unsigned int const& to) noexcept;

		//!	@brief	行成分拡縮関数
		CFMatrix3x3& row_scale(unsigned int const&, float const&) noexcept;
		//!	@brief	列成分拡縮関数
		CFMatrix3x3& column_scale(unsigned int const&, float const&) noexcept;

		//!	@brief	行成分積和関数
		CFMatrix3x3& row_sop(unsigned int const& from, unsigned int const& to, float const&) noexcept;
		//!	@brief	列成分積和関数
		CFMatrix3x3& column_sop(unsigned int const& from, unsigned int const& to, float const&) noexcept;

		//!	@brief	複合加算演算子
		CFMatrix3x3& operator+=(CFMatrix3x3 const&) noexcept;
		//!	@brief	複合減算演算子
		CFMatrix3x3& operator-=(CFMatrix3x3 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFMatrix3x3& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFMatrix3x3& operator/=(float const&) noexcept;

		//!	@brief	行成分抽出関数
		CFVector3 const row(unsigned int const&) const noexcept;
		//!	@brief	列成分抽出関数
		CFVector3 const column(unsigned int const&) const noexcept;

		//!	@brief	余因子行列生成関数
		CFMatrix3x3 const adj() const noexcept;
		//!	@brief	逆行列生成関数
		CFMatrix3x3 const inv() const noexcept;
		//!	@brief	転置行列生成関数
		CFMatrix3x3 const transpose() const noexcept;
		//!	@brief	行列式計算関数
		float const det() const noexcept;

		//!	@brief	単項加算演算子
		CFMatrix3x3 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFMatrix3x3 const operator-() const noexcept;
	};
	//!	@brief	直積関数
	CFMatrix3x3 const direct(CFVector3 const&, CFVector3 const&) noexcept;
	//!	@brief	楔積関数
	CFMatrix3x3 const wedge(CFVector3 const&, CFVector3 const&) noexcept;

	//!	@brief	加算演算子
	CFMatrix3x3 const operator+(CFMatrix3x3 const&, CFMatrix3x3 const&) noexcept;
	//!	@brief	減算演算子
	CFMatrix3x3 const operator-(CFMatrix3x3 const&, CFMatrix3x3 const&) noexcept;
	//!	@brief	乗算演算子
	CFMatrix3x3 const operator*(CFMatrix3x3 const&, CFMatrix3x3 const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFMatrix3x3 const operator*(CFMatrix3x3 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFMatrix3x3 const operator*(float const&, CFMatrix3x3 const&) noexcept;
	//!	@brief	除算演算子
	CFMatrix3x3 const operator/(CFMatrix3x3 const&, CFMatrix3x3 const&) noexcept;
	//!	@brief	スカラ割演算子
	CFMatrix3x3 const operator/(CFMatrix3x3 const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	CFMatrix3x3 const operator/(float const&, CFMatrix3x3 const&) noexcept;

	//!	@brief	行列作用演算子
	CFVector3 const operator*(CFVector3 const&, CFMatrix3x3 const&) noexcept;
	//!	@brief	行列作用演算子
	CFVector3 const operator*(CFMatrix3x3 const&, CFVector3 const&) noexcept;

	//!	@brief	加算演算子
	bool const operator==(CFMatrix3x3 const&, CFMatrix3x3 const&) noexcept;
	//!	@brief	減算演算子
	bool const operator!=(CFMatrix3x3 const&, CFMatrix3x3 const&) noexcept;

	//!	@brief	零行列
	static CFMatrix3x3 constexpr ZERO_FMTX3x3 = CFMatrix3x3(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	);
	//!	@brief	単位行列
	static CFMatrix3x3 constexpr UNIT_FMTX3x3 = CFMatrix3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}