/**	@file	stdafx.hpp
 *	@brief	プリコンパイル済みヘッダ
 */
#pragma once

#if !defined(_CRT_SECURE_NO_WARNINGS)
#	define _CRT_SECURE_NO_WARNINGS
#endif

#if !defined(_CRT_NON_CONFORMING_SWPRINTFS)
#	define _CRT_NON_CONFORMING_SWPRINTFS
#endif

#if !defined(NOMINMAX)
#	define NOMINMAX
#endif

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <initializer_list>
#include <immintrin.h>
#include <numeric>
#include <utility>
#include <memory>
#include <vector>
#include <exception>
#include <iostream>

#include <crtdbg.h>
#include <Windows.h>
#include <wrl/client.h>
#include <tchar.h>
#include <DirectXMath.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3dcompiler.h>

using Microsoft::WRL::ComPtr;
using namespace DirectX;