/**	@file	CD3D12ResourceBarrier.hpp
 *	@brief	Direct3D12 用のリソースバリアクラス宣言ファイル
 */
#pragma once
#include <d3d12.h>
#include "util/INonmovable.hpp"
#include "CD3D12CommandList.hpp"
#include "CD3D12Resource.hpp"

namespace dlav {
	/**	@file	CD3D12ResourceBarrier
	 *	@brief	Direct3D12 用のリソースバリアクラス
	 */
	class CD3D12ResourceBarrier final {
	public	:
		//!	@brief	ムーブコンストラクタ
		CD3D12ResourceBarrier(CD3D12ResourceBarrier&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CD3D12ResourceBarrier(CD3D12ResourceBarrier const&) noexcept = default;
		//!	@brief	ムーブコンストラクタ
		CD3D12ResourceBarrier& operator=(CD3D12ResourceBarrier&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CD3D12ResourceBarrier& operator=(CD3D12ResourceBarrier const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CD3D12ResourceBarrier() noexcept;
		//!	@brief	デストラクタ
		~CD3D12ResourceBarrier() noexcept = default;

		//!	@brief	レンダーターゲットモードに切り替える関数
		CD3D12ResourceBarrier& toRTMode(CD3D12CommandList&, CD3D12Resource&) noexcept;
		//!	@brief	プレゼントモードに切り替える関数
		CD3D12ResourceBarrier& toPresentMode(CD3D12CommandList&, CD3D12Resource&) noexcept;

	private	:
		//!	@brief	リソースバリア
		D3D12_RESOURCE_BARRIER m_barrier;
	};
}