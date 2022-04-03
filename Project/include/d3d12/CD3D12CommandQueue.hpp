/**	@file	CD3D12CommandQueue.hpp
 *	@brief	Direct3D12 用のコマンドキュー
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "ED3D12CommandType.hpp"
#include <d3d12.h>

namespace dlav {
	/**	@class	CD3D12CommandQueue
	 *	@brief	Direct3D12 用のデバイスクラス
	 */
	class CD3D12CommandQueue final :
		public INoncopyable<CD3D12CommandQueue>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12CommandQueue(CD3D12CommandQueue&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12CommandQueue& operator=(CD3D12CommandQueue&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CD3D12CommandQueue() noexcept;
		//!	@brief	デストラクタ
		~CD3D12CommandQueue() noexcept;

		//!	@brief	初期化関数
		bool const init(ED3D12CommandType const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	ポインタ取得
		ID3D12CommandQueue* get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12CommandQueue* operator->() const noexcept;

	private:
		//!	@brief	コマンドキュー
		ID3D12CommandQueue* m_queue;
	};
}