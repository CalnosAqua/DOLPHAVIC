/**	@file	CRTV.hpp
 *	@brief	レンダーターゲット
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "CD3D12SwapChain.hpp"
#include "CD3D12DescriptorHeap.hpp"
#include "CD3D12Resource.hpp"
#include <d3d12.h>
#include <vector>

namespace dlav {
	/** @class	CRenderTargetDesc
	 *	@brief	レンダーターゲットビュー初期化用データ
	 */
	struct SRenderTargetViewDesc final {
		//!	@brief	スワップチェインポインタ
		CD3D12SwapChain* pSwapchain;
		//!	@brief	バッファサイズ
		unsigned int FrameSize;
	};

	/** @class	CD3D12RenderTarget
	 *	@brief	レンダーターゲット
	 */
	class CD3D12RenderTarget final :
		public INoncopyable<CD3D12RenderTarget>
	{
	public:
		//!	@brief	デフォルトコンストラクタ
		CD3D12RenderTarget(CD3D12RenderTarget&&) noexcept = default;
		//!	@brief	デフォルトコンストラクタ
		CD3D12RenderTarget& operator=(CD3D12RenderTarget&&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CD3D12RenderTarget() noexcept;
		//!	@brief	デストラクタ
		~CD3D12RenderTarget() noexcept;

		//!	@brief	初期化関数
		bool const init(SRenderTargetViewDesc const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	リソース解放関数
		void rsrc_release() noexcept;

		//!	@brief	取得関数
		CD3D12Resource& get(unsigned int const&) const noexcept;
	private:
		//!	@brief	記述子ヒープ
		CD3D12DescriptorHeap m_heap;
		//!	@brief	データ
		std::vector<CD3D12Resource> m_datas;
	};
}