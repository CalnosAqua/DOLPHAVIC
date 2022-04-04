/**	@file	EDLColourFormat.hpp
 *	@brief	色フォーマット
 */
#pragma once

namespace dlav {
	/**	@class	EDLColorFormat
	 *	@brief	ピクセルフォーマット
	 */
	enum class EDLColorFormat : unsigned char {
		//!	@brief	フルカラー
		FullColor,
		//!	@brief	グレースケール
		GrayScale,
		//!	@brief	カラーインデックス
		ColorIndex,
		//!	@brief	ハイダイナミックレンジ
		HighDynamicRange
	};
}