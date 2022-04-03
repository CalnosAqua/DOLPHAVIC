/**	@file	dalib.hpp
 *	@brief	ライブラリエントリヘッダ
 */
#pragma once

#if defined(_M_IX86)
#   if defined(DEBUG) | defined(_DEBUG)
#       pragma comment(lib, "_dlav86.lib")
#   else
#       pragma comment(lib, "dlav86.lib")
#   endif
#else
#   if defined(DEBUG) | defined(_DEBUG)
#       pragma comment(lib, "_dlav64.lib")
#   else
#       pragma comment(lib, "dlav64.lib")
#   endif
#endif