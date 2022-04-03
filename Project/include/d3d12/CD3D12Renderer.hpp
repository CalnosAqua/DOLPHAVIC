/**	@file	CD3D12Renderer.hpp
 *	@brief	Direct3D12 を利用したレンダラ
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "util/SFloat4.hpp"
#include "CD3D12ResourceBarrier.hpp"
#include "CD3D12CommandQueue.hpp"
#include "CD3D12CommandList.hpp"
#include "CD3D12Fence.hpp"
#include "CRTV.hpp"
#include "CDSV.hpp"

#include "CD3D12RootSignature.hpp"
#include "CD3D12PipelineState.hpp"

namespace dlav {
	/**	@struct	RendererDesc
	 *	@brief	レンダラ初期化用データ
	 */
	struct RendererDesc final {
		//!	@brief	ウィンドウハンドラ
		HWND wnd_handler;
		//!	@brief	背景色
		SFloat4 color;
		//!	@brief	レンダーターゲットバッファサイズ
		unsigned int buffer_size;
		//!	@brief	フレームレート
		unsigned int frame_rate;
		//!	@brief	フルスクリーン設定
		bool fullscreen;
	};

	/**	@file	CD3D12Renderer
	 *	@brief	Direct3D12 を利用したレンダラ
	 */
	class CD3D12Renderer final :
		public INoncopyable<CD3D12Renderer>
	{
	public	:
		//!	@brief	ムーブコンストラクタ
		CD3D12Renderer(CD3D12Renderer&&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CD3D12Renderer& operator=(CD3D12Renderer&&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CD3D12Renderer() noexcept;
		//!	@brief	デストラクタ
		~CD3D12Renderer() noexcept;

		//!	@brief	初期化関数
		bool const init(RendererDesc const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	再初期化関数
		bool const reinit() noexcept;

		//!	@brief	前レンダリング処理関数
		bool const before_rendering() noexcept;
		//!	@brief	後レンダリング処理関数
		bool const after_rendering() noexcept;
		//!	@brief	描画処理関数
		bool const presenting() noexcept;
		//!	@brief	同期処理関数
		void waiting() noexcept;

		//!	@brief	ルートシグネチャ設定関数
		void setRootSignature(CD3D12RootSignature&) noexcept;
		//!	@brief	パイプラインステート設定関数
		void setGraphicsPipeline(CD3D12PipelineState&) noexcept;

		//!	@brief	コマンドリスト取得関数
		CD3D12CommandList& getCmdList() noexcept;
		//!	@brief	デプスステンシル取得関数
		CD3D12DepthStencil& getDSV() noexcept;

		//!	@brief	トリム矩形取得関数
		D3D12_RECT const getTrimRect() const noexcept;
		//!	@brief	ビューポート取得関数
		D3D12_VIEWPORT const getViewport() const noexcept;
		//!	@brief	フレームバッファ数取得関数
		unsigned int const getFrameBufferSize() const noexcept;
		//!	@brief	横幅取得関数
		float const getWidth() const noexcept;
		//!	@brief	縦幅取得関数
		float const getHeight() const noexcept;
		//!	@brief	アスペクト比取得関数
		float const getAspectRate() const noexcept;
		//!	@brief	カレントバッファインデックス取得関数
		unsigned int const getCurrentBufferIndex() const noexcept;

	private	:
		//!	@brief	ウィンドウハンドラ
		HWND m_hWnd;
		//!	@brief	バッファ数
		unsigned int m_bufferCount;
		//!	@brief	現在のフレームインデックス
		unsigned int m_currentIndex;

		//!	@brief	トリム矩形
		D3D12_RECT m_rect;
		//!	@brief	ビューポート
		D3D12_VIEWPORT m_viewport;
		//!	@brief	RTV リソースビュー
		CD3D12RenderTarget m_rtv;
		//!	@brief	DSV リソースビュー
		CD3D12DepthStencil m_dsv;
		//!	@brief	スワップチェイン
		CD3D12SwapChain m_chain;
		//!	@brief	リソースバリア
		CD3D12ResourceBarrier m_barrier;
		//!	@brief	コマンドキュー
		CD3D12CommandQueue m_queue;
		//!	@brief	コマンドリスト
		CD3D12CommandList m_list;
		//!	@brief	フェンス
		CD3D12Fence m_fence;
		//!	@brief	背景色
		SFloat4 m_color;
	};
}