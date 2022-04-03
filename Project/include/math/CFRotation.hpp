/**	@file	CFRotation.hpp
 *	@brief	単精度浮動小数点数型回転量
 */
#pragma once

namespace dlav {
	/**	@class	CFRotation
	 *	@brief	単精度浮動小数点数型回転量
	 */
	class CFRotation final {
	public	:
		//!	@brief	ムーブコンストラクタ
		CFRotation(CFRotation&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFRotation(CFRotation const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFRotation& operator=(CFRotation&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFRotation& operator=(CFRotation const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFRotation() noexcept;
		//!	@brief	デストラクタ
		~CFRotation() noexcept = default;

		//!	@brief	回転量設定関数（弧度法）
		CFRotation& radian(float const&) noexcept;
		//!	@brief	回転量設定関数（度数法）
		CFRotation& degree(float const&) noexcept;

		//!	@brief	正弦関数
		CFRotation& asin(float const&) noexcept;
		//!	@brief	余弦関数
		CFRotation& acos(float const&) noexcept;
		//!	@brief	正接関数
		CFRotation& atan(float const&) noexcept;
		//!	@brief	正接関数
		CFRotation& atan(float const& x, float const& y) noexcept;

		//!	@brief	複合加算演算子
		CFRotation& operator+=(CFRotation const&) noexcept;
		//!	@brief	複合減算演算子
		CFRotation& operator-=(CFRotation const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFRotation& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFRotation& operator/=(float const&) noexcept;

		//!	@brief	回転量取得関数（弧度法）
		float const radian() const noexcept;
		//!	@brief	回転量取得関数（度数法）
		float const degree() const noexcept;

		//!	@brief	正弦関数
		float const sin() const noexcept;
		//!	@brief	余弦関数
		float const cos() const noexcept;
		//!	@brief	正接関数
		float const tan() const noexcept;

		//!	@brief	角度化関数
		CFRotation const anglize() const noexcept;
		//!	@brief	回転数取得関数
		int const round() const noexcept;

		//!	@brief	単項加算演算子
		CFRotation const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFRotation const operator-() const noexcept;

		//!	@brief	比較関数
		friend int const compare(CFRotation const&, CFRotation const&) noexcept;
	private	:
		//!	@brief	回転量
		float m_angle;
	};
	//!	@brief	加算演算子
	CFRotation const operator+(CFRotation const&, CFRotation const&) noexcept;
	//!	@brief	減算演算子
	CFRotation const operator-(CFRotation const&, CFRotation const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFRotation const operator*(CFRotation const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFRotation const operator*(float const&, CFRotation const&) noexcept;
	//!	@brief	スカラ割演算子
	CFRotation const operator/(CFRotation const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFRotation const&, CFRotation const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFRotation const&, CFRotation const&) noexcept;
	//!	@brief	小なりイコール演算子
	bool const operator<=(CFRotation const&, CFRotation const&) noexcept;
	//!	@brief	大なりイコール演算子
	bool const operator>=(CFRotation const&, CFRotation const&) noexcept;
	//!	@brief	小なり演算子
	bool const operator< (CFRotation const&, CFRotation const&) noexcept;
	//!	@brief	大なり演算子
	bool const operator> (CFRotation const&, CFRotation const&) noexcept;
}