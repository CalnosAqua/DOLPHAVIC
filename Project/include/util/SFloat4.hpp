/**	@file	SFloat4.hpp
 *	@brief	四つの単精度浮動小数点数を束ねた構造体
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlav {
	/**	@struct SFloat4
	 *	@brief	四つの単精度浮動小数点数を束ねた構造体
	 */
	struct SFloat4 {
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 4U;
		union {
			//!	@brief	全成分
			float p[4U];
			struct {
				//!	@brief	第一成分
				float x;
				//!	@brief	第二成分
				float y;
				//!	@brief	第三成分
				float z;
				//!	@brief	第四成分
				float w;
			};
		};
	};
}