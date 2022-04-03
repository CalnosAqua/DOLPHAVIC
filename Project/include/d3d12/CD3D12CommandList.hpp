/**	@file	CD3D12CommandList.hpp
 *	@brief	Direct3D12 用のコマンドリスト
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "ED3D12CommandType.hpp"
#include <d3d12.h>

namespace dlav {
	/**	@class	CD3D12CommandList
	 *	@brief	Direct3D12 用のデバイスクラス
	 */
	class CD3D12CommandList final :
		public INoncopyable<CD3D12CommandList>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12CommandList(CD3D12CommandList&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12CommandList& operator=(CD3D12CommandList&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CD3D12CommandList() noexcept;
		//!	@brief	デストラクタ
		~CD3D12CommandList() noexcept;

		//!	@brief	初期化関数
		bool const init(ED3D12CommandType const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	コマンド記録開始
		bool const recording() noexcept;
		//!	@brief	コマンド記録終了
		bool const closing() noexcept;

		//!	@brief	ポインタ取得
		ID3D12GraphicsCommandList6* get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12GraphicsCommandList6* operator->() const noexcept;

		//!	@brief	記録可能状態取得
		bool const isOpened() const noexcept;

	private:
		//!	@brief	コマンドアロケータ
		ID3D12CommandAllocator* m_alloc;
		//!	@brief	コマンドリスト
		ID3D12GraphicsCommandList6* m_list;
		//!	@brief	記録可能かどうか
		bool m_opened;
	};
}