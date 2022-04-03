/**	@file	CIBV.hpp
 *	@brief	インデックスバッファビュー
 */
#pragma once
#include "util/INonmovable.hpp"
#include "CD3D12Resource.hpp"
#include <d3d12.h>
#include <vector>

namespace dlav {
	/**	@file	CD3D12IndexBuffer
	 *	@brief	インデックスバッファビュー
	 */
	class CD3D12IndexBuffer final : public INonmovable<CD3D12IndexBuffer> {
	public	:
		//!	@brief	デフォルトコンストラクタ
		CD3D12IndexBuffer() noexcept;
		//!	@brief	デストラクタ
		~CD3D12IndexBuffer() noexcept = default;

		//!	@brief	初期化関数
		bool const init(std::vector<unsigned int> const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	ビュー記述子取得
		D3D12_INDEX_BUFFER_VIEW const& get() const noexcept;

	private:
		//!	@brief	インデックスバッファビュー記述子
		D3D12_INDEX_BUFFER_VIEW m_view;
		//!	@brief	リソース
		CD3D12Resource m_rsrc;
	};
}