/**	@file	CD3D12SwapChain.hpp
 *	@brief	スワップチェイン
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "CD3D12CommandQueue.hpp"
#include <dxgi1_6.h>

namespace dlav {
	/** @struct	CHN_DESC
	 *	@brief	スワップチェイン生成用データ一式
	 */
	struct SSwapChainDesc final {
		//!	@brief	ウィンドウハンドラ
		HWND wnd_handler;
		//!	@brief	コマンドキュー
		mutable ID3D12CommandQueue* cmd_queue;
		//!	@brief	バッファサイズ
		unsigned int buffer_size;
		//!	@brief	フレームレート
		unsigned int frame_rate;
		//!	@brief	ウィンドウ/フルスクリーン モード
		bool fullscreen;
	};

	/**	@enum	CD3D12SwapChain
	 *	@brief	スワップチェイン
	 */
	class CD3D12SwapChain final :
		public INoncopyable<CD3D12SwapChain>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12SwapChain(CD3D12SwapChain&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12SwapChain& operator=(CD3D12SwapChain&&) noexcept;
		
		//!	@brief	デフォルトコンストラクタ
		CD3D12SwapChain() noexcept;
		//!	@brief	デストラクタ
		~CD3D12SwapChain() noexcept;

		//!	@brief	初期化関数
		bool const init(SSwapChainDesc const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	取得関数
		IDXGISwapChain4*& get() const noexcept;
		//!	@brief	メンバアクセス演算子
		IDXGISwapChain4* operator->() const noexcept;
	private:
		//!	@brief	スワップチェインポインタ
		IDXGISwapChain4* m_chain;
	};
}