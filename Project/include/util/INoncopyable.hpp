/**	@file	INoncopyable.hpp
 *	@brief	コピー禁止インターフェース
 */
#pragma once

namespace dlav {
	/**	@class	INoncopyable<T>
	 *	@brief	コピー禁止インターフェース
	 */
	template <typename T>
	class INoncopyable {
	public :
		//!	@brief	コピーコンストラクタ
		INoncopyable(T const&) noexcept = delete;
		//!	@brief	コピー代入演算子
		T& operator=(T const&) noexcept = delete;
		
		//!	@brief	デフォルトコンストラクタ
		INoncopyable() noexcept {}
		//!	@brief	デストラクタ
		virtual ~INoncopyable() noexcept {};
	};
}