/**	@file	CD3D12Resource.hpp
 *	@brief	Direct3D12 用のリソースクラス
 */
#pragma once
#include "SD3D12Resource.hpp"
#include <dxgi1_6.h>
#include <d3d12.h>

namespace dlav {
	/**	@struct	SRenderTargetDesc
	 *	@brief	レンダーターゲット用のバッファを作る為の基本データ
	 */
	struct SRenderTargetDesc final {
		//!	@brief	CPU 記述子
		D3D12_CPU_DESCRIPTOR_HANDLE handle;
		//!	@brief	スワップチェイン
		IDXGISwapChain4* swapchain;
		//!	@brief	バッファインデックス
		unsigned int index;
	};

	/**	@struct	SDepthStencilDesc
	 *	@brief	深度ステンシル用のバッファを作る為の基本データ
	 */
	struct SDepthStencilDesc final {
		//!	@brief	CPU 記述子
		D3D12_CPU_DESCRIPTOR_HANDLE handle;
		//!	@brief	ウィンドウの横幅
		unsigned int width;
		//!	@brief	ウィンドウの縦幅
		unsigned int height;
	};

	/**	@struct	SIndexBufferDesc
	 *	@brief	インデックスバッファを作る為の基本データ
	 */
	struct SIndexBufferDesc final {
		//!	@brief	インデックスバッファビュー記述子
		mutable D3D12_INDEX_BUFFER_VIEW view;
		//!	@brief	インデックスデータへのポインタ
		mutable unsigned int* indecies;
		//!	@brief	配列長
		unsigned int count;
	};

	/**	@class	CD3D12Resource
	 *	@brief	Direct3D12 用のリソースクラス
	 */
	class CD3D12Resource final :
		public INoncopyable<CD3D12Resource>
	{
	public	:
		//!	@brief	ムーブコンストラクタ
		CD3D12Resource(CD3D12Resource&&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CD3D12Resource& operator=(CD3D12Resource&&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CD3D12Resource() noexcept;
		//!	@brief	デストラクタ
		~CD3D12Resource() noexcept = default;

		//!	@brief	バッファ生成関数
		bool const init(SIndexBufferDesc const&) noexcept;
		//!	@brief	レンダーターゲット生成関数
		bool const init(SRenderTargetDesc const&) noexcept;
		//!	@brief	深度ステンシル生成関数
		bool const init(SDepthStencilDesc const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	メンバアクセス演算子
		ID3D12Resource2* operator->() const noexcept;

		//!	@brief	リソースポインタ取得関数
		ID3D12Resource2*& get() const noexcept;
		//!	@brief	CPU 記述子取得関数
		D3D12_CPU_DESCRIPTOR_HANDLE& getCPUDescriptorHandle() const noexcept;
		//!	@brief	GPU 記述子取得関数
		D3D12_GPU_DESCRIPTOR_HANDLE& getGPUDescriptorHandle() const noexcept;

	private	:
		//!	@brief	リソース
		SD3D12Resource m_rsrc;
		//!	@brief	バインド状況
		bool m_binded;
	};
}