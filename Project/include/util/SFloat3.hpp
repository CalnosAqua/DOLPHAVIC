/**	@file	SFloat3.hpp
 *	@brief	三つの単精度浮動小数点数を束ねた構造体
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlav {
	//!	@brief	成分数
	static unsigned int constexpr FLT3_CNT = 3U;

	/**	@struct SFloat3
	 *	@brief	三つの単精度浮動小数点数を束ねた構造体
	 */
	struct SFloat3 {
		union {
			//!	@brief	全成分
			float p[3U];
			struct {
				//!	@brief	第一成分
				float x;
				//!	@brief	第二成分
				float y;
				//!	@brief	第三成分
				float z;
			};
		};
	};
}