/**	@file	SD3D12Resource.hpp
 *	@brief	リソース
 */
#pragma once
#include "util/INoncopyable.hpp"
#include <d3d12.h>

namespace dlav {
	/**	@struct	SD3D12Resource
	 *	@brief	リソース
	 */
	struct SD3D12Resource : public INoncopyable<SD3D12Resource> {
		//!	@brief	CPU 記述子ハンドル
		D3D12_CPU_DESCRIPTOR_HANDLE cpu;
		//!	@brief	GPU 記述子ハンドル
		D3D12_GPU_DESCRIPTOR_HANDLE gpu;
		//!	@brief	リソース
		ID3D12Resource2* rsrc;

		//!	@brief	ムーブコンストラクタ
		SD3D12Resource(SD3D12Resource&&) noexcept;
		//!	@brief	ムーブ代入演算子
		SD3D12Resource& operator=(SD3D12Resource&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		SD3D12Resource() noexcept;
		//!	@brief	デストラクタ
		~SD3D12Resource() noexcept;

		//!	@brief	メンバアクセス演算子
		ID3D12Resource2* operator->() const noexcept;
	};
}