/**	@file	CRay.hpp
 *	@brief	光線
 */
#pragma once

namespace dlav {
	/**	@class	CRay<T>
	 *	@brief	光線
	 */
	template <typename T>
	class CRay final {
	public	:
		union {
			//!	@brief	全成分
			T p[2U];
			struct {
				//!	@brief	基準点
				T position;
				//!	@brief	方向
				T direction;
			};
		};

		//!	@brief	ムーブコンストラクタ
		CRay(CRay<T>&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CRay(CRay<T> const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CRay<T>& operator=(CRay<T>&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CRay<T>& operator=(CRay<T> const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CRay() noexcept;
		//!	@brief	デストラクタ
		~CRay() noexcept = default;

		//!	@brief	到達点
		T const operator[](float const&) const noexcept;
	};

	/* 実装 */

	template<typename T>
	inline CRay<T>::CRay() noexcept :
		position(),
		direction()
	{}

	template<typename T>
	inline T const CRay<T>::operator[](float const& rate) const noexcept {
		return position + direction * rate;
	}
}