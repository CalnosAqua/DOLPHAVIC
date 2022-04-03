/**	@file	CD3D12DescriptorHeap.hpp
 *	@brief	記述子ヒープ
 */
#pragma once
#include <d3d12.h>

#include "util/INoncopyable.hpp"
#include "ED3D12ViewType.hpp"

namespace dlav {
	/**	@file	CD3D12DescriptorHeap
	 *	@brief	記述子ヒープ
	 */
	class CD3D12DescriptorHeap final :
		public INoncopyable<CD3D12DescriptorHeap>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12DescriptorHeap(CD3D12DescriptorHeap&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12DescriptorHeap& operator=(CD3D12DescriptorHeap&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CD3D12DescriptorHeap() noexcept;
		//!	@brief	デストラクタ
		~CD3D12DescriptorHeap() noexcept;

		//!	@brief	初期化関数
		bool const init(ED3D12ViewType const&, unsigned int const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	CPU ハンドル取得関数
		D3D12_CPU_DESCRIPTOR_HANDLE const getCPUStartHandle() const noexcept;
		//!	@brief	GPU ハンドル取得関数
		D3D12_GPU_DESCRIPTOR_HANDLE const getGPUStartHandle() const noexcept;

		//!	@brief	取得関数
		ID3D12DescriptorHeap* get() noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12DescriptorHeap* operator->() const noexcept;
	private:
		//!	@brief	記述子ヒープポインタ
		ID3D12DescriptorHeap* m_heap;
	};
}
