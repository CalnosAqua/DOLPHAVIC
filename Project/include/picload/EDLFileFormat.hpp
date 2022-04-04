/**	@file	EDLFileFormat.hpp
 *	@brief	Dolphavic Library 用の画像データの種類
 */
#pragma once

namespace dlav {
	/**	@brief	EDLFileFormat
	 *	@class	画像データの種類
	 */
	enum class EDLFileFormat : unsigned int {
		//!	@brief	Unknown Format
		Unknown,
		//!	@brief	Dolphavic Graphics (Original)
		DAG,
		//!	@brief	Bitmap
		BMP,
		//!	@brief	Truevision Graphics Adaptor
		TGA,
		//!	@brief	Portable Network Graphics
		PNG,
		//!	@brief	Joint Photographic Experts Group
		JPEG,
		//!	@brief	Graphics Interchange Format
		GIF,
		//!	@brief	Tagged Image File Format
		TIFF
	};
}