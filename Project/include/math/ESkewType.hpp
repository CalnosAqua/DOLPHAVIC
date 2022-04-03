/**	@file	ESkewType.hpp
 *	@brief	剪断対象
 */
#pragma once

namespace dlav {
	/**	@file	ESkewType
	 *	@brief	剪断対象
	 */
	enum class ESkewType : unsigned char {
		//!	@brief 主成分
		PRIMARY,
		//!	@brief 副成分
		SECONDARY
	};
}