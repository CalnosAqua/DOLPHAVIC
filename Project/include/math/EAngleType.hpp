/**	@file	EAngleType.hpp
 *	@brief	角度の表現法
 */
#pragma once

namespace dlav {
	/**	@enum	EAngleType
	 *	@brief	回転量の表現法一覧
	 */
	enum class EAngleType : unsigned char {
		//!	@brief	度数法
		DEGREE,
		//!	@brief	弧度法
		RADIAN
	};
}