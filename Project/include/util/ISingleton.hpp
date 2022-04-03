/**	@file	ISingleton.hpp
 *	@brief	シングルトンインターフェース
 */
#pragma once
#include "INonmovable.hpp"

namespace dlav {
	/**	@class	ISingleton<T>
	 *	@brief	シングルトンインターフェース
	 */
	template <typename T>
	class ISingleton : public INonmovable<T>{
	public :
		//!	@brief	デストラクタ
		virtual ~ISingleton() noexcept {};
		//!	@brief	インスタンス取得関数
		static T& getInstance() noexcept {
			static T result;
			return result;
		}
	protected :
		//!	@brief	デフォルトコンストラクタ
		ISingleton() noexcept :
			INonmovable<T>()
		{}
	};
}