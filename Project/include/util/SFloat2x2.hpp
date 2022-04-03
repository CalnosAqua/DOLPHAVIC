/**	@file	SFloat2x2.hpp
 *	@brief	四つの単精度浮動小数点数を束ねた構造体
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlav {
	/**	@struct SFloat2x2
	 *	@brief	四つの単精度浮動小数点数を束ねた構造体
	 */
	struct SFloat2x2 {
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 4U;
		union {
			//!	@brief	全成分
			float p[4U];
			struct {
				//!	@brief	一行一列目の成分
				float m00;
				//!	@brief	一行二列目の成分
				float m01;
				//!	@brief	二行一列目の成分
				float m10;
				//!	@brief	二行二列目の成分
				float m11;
			};
		};
	};
}