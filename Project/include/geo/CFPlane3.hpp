/**	@file	CFPlane3.hpp
 *	@brief	三次元平面方程式
 */
#pragma once
#include "math/CFMatrix3x3.hpp"
#include "math/EHandSide.hpp"

namespace dlav {
	/**	@class	CFPlane3
	 *	@brief	三次元平面方程式
	 */
	class CFPlane3 final {
	public	:
		//!	@brief	ムーブコンストラクタ
		CFPlane3(CFPlane3&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFPlane3(CFPlane3 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFPlane3& operator=(CFPlane3&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFPlane3& operator=(CFPlane3 const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFPlane3() noexcept;
		//!	@brief	デストラクタ
		~CFPlane3() noexcept = default;

		//! @brief 初期化関数
		CFPlane3& init(CFVector3 const&, CFVector3 const&, CFVector3 const&) noexcept;

		//! @brief 法線取得関数
		CFVector3 const normal() const noexcept;
		//! @brief 従法線取得関数
		CFVector3 const binormal() const noexcept;
		//! @brief 接ベクトル取得関数
		CFVector3 const tangent() const noexcept;

		//!	@brief	行列取得関数
		CFMatrix3x3 const getMatrix(EHandSide const&) const noexcept;
		//!	@brief	Ｄ値取得関数
		float const getDValue() const noexcept;

	private	:
		//!	接ベクトル空間行列
		CFMatrix3x3	m_mtx;
		//!	Ｄ値
		float m_value;
	};
}