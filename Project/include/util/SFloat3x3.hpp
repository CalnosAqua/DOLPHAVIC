/**	@file	SFloat3x3.hpp
 *	@brief	九つの単精度浮動小数点数を束ねた構造体
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlav {
	/**	@struct SFloat3x3
	 *	@brief	九つの単精度浮動小数点数を束ねた構造体
	 */
	struct SFloat3x3 {
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 9U;
		union {
			//!	@brief	全成分
			float p[9U];
			struct {
				//!	@brief	一行一列目の成分
				float m00;
				//!	@brief	一行二列目の成分
				float m01;
				//!	@brief	一行三列目の成分
				float m02;
				//!	@brief	二行一列目の成分
				float m10;
				//!	@brief	二行二列目の成分
				float m11;
				//!	@brief	二行三列目の成分
				float m12;
				//!	@brief	三行一列目の成分
				float m20;
				//!	@brief	三行二列目の成分
				float m21;
				//!	@brief	三行三列目の成分
				float m22;
			};
		};
	};
}