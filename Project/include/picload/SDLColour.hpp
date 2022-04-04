/**	@file	SDLColour.hpp
 *	@brief	色構造体
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlav {
	using byte = unsigned char;

	/**	@struct	SFAlphaColour
	 *	@brief	単精度浮動小数点数型のアルファ付き色構造体
	 */
	struct SFAlphaColour final {
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 4U;
		union {
			//!	@brief	全成分
			float p[4U];
			struct {
				//!	@brief	赤色輝度
				float r;
				//!	@brief	緑色輝度
				float g;
				//!	@brief	青色輝度
				float b;
				//!	@brief	(不)透明度
				float a;
			};
		};
	};

	/**	@struct	SBAlphaColour
	 *	@brief	byte 型のアルファ付き色構造体
	 */
	struct SBAlphaColour final {
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 4U;
		union {
			//!	@brief	全成分
			byte p[4U];
			struct {
				//!	@brief	赤色輝度
				byte r;
				//!	@brief	緑色輝度
				byte g;
				//!	@brief	青色輝度
				byte b;
				//!	@brief	(不)透明度
				byte a;
			};
		};
	};

	/**	@struct	SFColour
	 *	@brief	単精度浮動小数点数型の色構造体
	 */
	struct SFColour final {
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 3U;
		union {
			//!	@brief	全成分
			float p[3U];
			struct {
				//!	@brief	赤色輝度
				float r;
				//!	@brief	緑色輝度
				float g;
				//!	@brief	青色輝度
				float b;
			};
		};
	};

	/**	@struct	SBColour
	 *	@brief	byte 型の色構造体
	 */
	struct SBColour final {
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 3U;
		union {
			//!	@brief	全成分
			byte p[3U];
			struct {
				//!	@brief	赤色輝度
				byte r;
				//!	@brief	緑色輝度
				byte g;
				//!	@brief	青色輝度
				byte b;
			};
		};
	};

	//!	@brief	色を最適化する関数
	void optimize(SFAlphaColour&) noexcept;
	//!	@brief	色を最適化する関数
	void optimize(SFColour&) noexcept;
}