/**	@file	EHandSide.hpp
 *	@brief	Ｘ軸の方向指定の為の基準
 */
#pragma once

namespace dlav {
	/**	@enum	EHandSide
	 *	@brief	Ｘ軸の方向指定の為の基準
	 */
	enum class EHandSide : unsigned char {
		//!	@brief	左手系
		LHS,
		//!	@brief	右手系
		RHS
	};
}