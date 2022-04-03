/**	@file	CFMatrix4x4.hpp
 *	@brief	単精度浮動小数点数型四次正方行列
 */
#pragma once
#pragma warning(disable : 4324)
#include "util/SFloat4x4.hpp"
#include "CFVector4.hpp"
#include <initializer_list>

namespace dlav {
	/**	@file	CFMatrix4x4
	 *	@brief	単精度浮動小数点数型四次正方行列
	 */
	class alignas(16) CFMatrix4x4 final : public SFloat4x4{
	public	:
		//!	@brief	ムーブコンストラクタ
		CFMatrix4x4(CFMatrix4x4&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFMatrix4x4(CFMatrix4x4 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFMatrix4x4& operator=(CFMatrix4x4&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFMatrix4x4& operator=(CFMatrix4x4 const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFMatrix4x4() noexcept;
		//!	@brief	デストラクタ
		~CFMatrix4x4() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFMatrix4x4(
			float const& m00, float const& m01, float const& m02, float const& m03,
			float const& m10, float const& m11, float const& m12, float const& m13,
			float const& m20, float const& m21, float const& m22, float const& m23,
			float const& m30, float const& m31, float const& m32, float const& m33
		) noexcept :
			SFloat4x4{
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33
			}
		{}
		//!	@brief	コンストラクタ
		explicit CFMatrix4x4(std::initializer_list<float> const&) noexcept;

		//!	@brief	行成分抽出関数
		CFMatrix4x4& row(unsigned int const&, CFVector4 const&) noexcept;
		//!	@brief	列成分抽出関数
		CFMatrix4x4& column(unsigned int const&, CFVector4 const&) noexcept;

		//!	@brief	行成分交換関数
		CFMatrix4x4& row_swap(unsigned int const& from, unsigned int const& to) noexcept;
		//!	@brief	列成分交換関数
		CFMatrix4x4& column_swap(unsigned int const& from, unsigned int const& to) noexcept;

		//!	@brief	行成分拡縮関数
		CFMatrix4x4& row_scale(unsigned int const&, float const&) noexcept;
		//!	@brief	列成分拡縮関数
		CFMatrix4x4& column_scale(unsigned int const&, float const&) noexcept;

		//!	@brief	行成分積和関数
		CFMatrix4x4& row_sop(unsigned int const& from, unsigned int const& to, float const&) noexcept;
		//!	@brief	列成分積和関数
		CFMatrix4x4& column_sop(unsigned int const& from, unsigned int const& to, float const&) noexcept;

		//!	@brief	複合加算演算子
		CFMatrix4x4& operator+=(CFMatrix4x4 const&) noexcept;
		//!	@brief	複合減算演算子
		CFMatrix4x4& operator-=(CFMatrix4x4 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFMatrix4x4& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFMatrix4x4& operator/=(float const&) noexcept;

		//!	@brief	行成分抽出関数
		CFVector4 const row(unsigned int const&) const noexcept;
		//!	@brief	列成分抽出関数
		CFVector4 const column(unsigned int const&) const noexcept;

		//!	@brief	余因子行列生成関数
		CFMatrix4x4 const adj() const noexcept;
		//!	@brief	逆行列生成関数
		CFMatrix4x4 const inv() const noexcept;
		//!	@brief	転置行列生成関数
		CFMatrix4x4 const transpose() const noexcept;
		//!	@brief	行列式計算関数
		float const det() const noexcept;

		//!	@brief	単項加算演算子
		CFMatrix4x4 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFMatrix4x4 const operator-() const noexcept;
	};
	//!	@brief	直積関数
	CFMatrix4x4 const direct(CFVector4 const&, CFVector4 const&) noexcept;
	//!	@brief	楔積関数
	CFMatrix4x4 const wedge(CFVector4 const&, CFVector4 const&) noexcept;

	//!	@brief	加算演算子
	CFMatrix4x4 const operator+(CFMatrix4x4 const&, CFMatrix4x4 const&) noexcept;
	//!	@brief	減算演算子
	CFMatrix4x4 const operator-(CFMatrix4x4 const&, CFMatrix4x4 const&) noexcept;
	//!	@brief	乗算演算子
	CFMatrix4x4 const operator*(CFMatrix4x4 const&, CFMatrix4x4 const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFMatrix4x4 const operator*(CFMatrix4x4 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFMatrix4x4 const operator*(float const&, CFMatrix4x4 const&) noexcept;
	//!	@brief	除算演算子
	CFMatrix4x4 const operator/(CFMatrix4x4 const&, CFMatrix4x4 const&) noexcept;
	//!	@brief	スカラ割演算子
	CFMatrix4x4 const operator/(CFMatrix4x4 const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	CFMatrix4x4 const operator/(float const&, CFMatrix4x4 const&) noexcept;

	//!	@brief	行列作用演算子
	CFVector4 const operator*(CFVector4 const&, CFMatrix4x4 const&) noexcept;
	//!	@brief	行列作用演算子
	CFVector4 const operator*(CFMatrix4x4 const&, CFVector4 const&) noexcept;

	//!	@brief	加算演算子
	bool const operator==(CFMatrix4x4 const&, CFMatrix4x4 const&) noexcept;
	//!	@brief	減算演算子
	bool const operator!=(CFMatrix4x4 const&, CFMatrix4x4 const&) noexcept;

	//!	@brief	零行列
	static CFMatrix4x4 constexpr ZERO_FMTX4x4 = CFMatrix4x4(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	//!	@brief	単位行列
	static CFMatrix4x4 constexpr UNIT_FMTX4x4 = CFMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}