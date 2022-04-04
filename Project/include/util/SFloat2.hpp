/**	@file	SFloat2.hpp
 *	@brief	二つの単精度浮動小数点数を束ねた構造体
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlav {
	//!	@brief	成分数
	static unsigned int constexpr FLT2_CNT = 2U;

	/**	@struct SFloat2
	 *	@brief	二つの単精度浮動小数点数を束ねた構造体
	 */
	struct SFloat2 {
		union {
			//!	@brief	全成分
			float p[2U];
			struct {
				//!	@brief	第一成分
				float x;
				//!	@brief	第二成分
				float y;
			};
		};
	};
}