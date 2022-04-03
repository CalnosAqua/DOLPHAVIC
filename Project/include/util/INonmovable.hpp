/**	@file	INonmovable.hpp
 *	@brief	ムーブ禁止インターフェース
 */
#pragma once
#include "INoncopyable.hpp"

namespace dlav {
	/**	@class	INonmovable<T>
	 *	@brief	ムーブ禁止インターフェース
	 */
	template <typename T>
	class INonmovable : public INoncopyable<T> {
	public :
		//!	@brief	ムーブコンストラクタ
		INonmovable(T&&) noexcept = delete;
		//!	@brief	ムーブ代入演算子
		T& operator=(T&&) noexcept = delete;
		
		//!	@brief	デフォルトコンストラクタ
		INonmovable() noexcept :
			INoncopyable<T>()
		{}
		//!	@brief	デストラクタ
		virtual ~INonmovable() noexcept {};
	};
}