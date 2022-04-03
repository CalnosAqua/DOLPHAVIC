/**	@file	EAxisType.hpp
 *	@brief	三次元空間上の軸の種類
 */
#pragma once

namespace dlav {
	/**	@enum	EAxisType
	 *	@brief	三次元空間上の軸の種類
	 */
	enum class EAxisType : unsigned char {
		//!	@brief	Ｘ軸（ピッチ角、YZ平面）
		X_AXIS,
		//!	@brief	Ｙ軸（ヨー角、XZ平面）
		Y_AXIS,
		//!	@brief	Ｚ軸（ロール角、XY平面）
		Z_AXIS
	};
}