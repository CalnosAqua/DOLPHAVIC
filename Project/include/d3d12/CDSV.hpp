/**	@file	CRTV.hpp
 *	@brief	深度バッファビュー
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "CD3D12DescriptorHeap.hpp"
#include "CD3D12Resource.hpp"
#include <d3d12.h>

namespace dlav {
	/** @class	CD3D12DepthStencilView
	 *	@brief	深度バッファビュー
	 */
	class CD3D12DepthStencil final :
		public INoncopyable<CD3D12DepthStencil>
	{
	public:
		//!	@brief	デフォルトコンストラクタ
		CD3D12DepthStencil(CD3D12DepthStencil&&) noexcept = default;
		//!	@brief	デフォルトコンストラクタ
		CD3D12DepthStencil& operator=(CD3D12DepthStencil&&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CD3D12DepthStencil() noexcept;
		//!	@brief	デストラクタ
		~CD3D12DepthStencil() noexcept;

		//!	@brief	初期化関数
		bool const init(HWND const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	リソース解放関数
		void rsrc_release() noexcept;

		//!	@brief	取得関数
		CD3D12Resource const& get() const noexcept;
		//!	@brief	取得関数
		D3D12_DEPTH_STENCIL_DESC& getDesc() const noexcept;
	private:
		//!	@brief	記述子ヒープ
		CD3D12DescriptorHeap m_heap;
		//!	@brief	データ
		CD3D12Resource m_data;
	};
}