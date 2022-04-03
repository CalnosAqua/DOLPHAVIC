/**	@file	CLSeg.hpp
 *	@brief	線分
 */
#pragma once

namespace dlav {
	/**	@class	CLSeg<T>
	 *	@brief	線分
	 */
	template <typename T>
	class CLSeg final {
	public:
		union {
			//!	@brief	全成分
			T p[2U];
			struct {
				//!	@brief	始点
				T begin;
				//!	@brief	終点
				T end;
			};
		};

		//!	@brief	ムーブコンストラクタ
		CLSeg(CLSeg<T>&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CLSeg(CLSeg<T> const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CLSeg<T>& operator=(CLSeg<T>&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CLSeg<T>& operator=(CLSeg<T> const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CLSeg() noexcept;
		//!	@brief	デストラクタ
		~CLSeg() noexcept = default;

		//!	@brief	中間点
		T const operator[](float const&) const noexcept;
	};

	/* 実装 */

	template<typename T>
	inline CLSeg<T>::CLSeg() noexcept :
		begin(),
		end()
	{}

	template<typename T>
	inline T const CLSeg<T>::operator[](float const& rate) const noexcept {
		return (end - begin) * rate + begin;
	}
}