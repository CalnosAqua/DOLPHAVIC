/**	@file	CD3D12ResourceBarrier.cpp
 *	@brief	Direct3D12 用のリソースバリアクラス定義ファイル
 */
#include "d3d12/CD3D12ResourceBarrier.hpp"

namespace dlav {
	CD3D12ResourceBarrier::CD3D12ResourceBarrier() noexcept :
		m_barrier()
	{}

	CD3D12ResourceBarrier& CD3D12ResourceBarrier::toRTMode(CD3D12CommandList& list, CD3D12Resource& rsrc) noexcept {
		m_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		m_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_barrier.Transition.pResource = rsrc.get();
		m_barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		m_barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		m_barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		list->ResourceBarrier(1, &m_barrier);
		return *this;
	}

	CD3D12ResourceBarrier& CD3D12ResourceBarrier::toPresentMode(CD3D12CommandList& list, CD3D12Resource& rsrc) noexcept {
		m_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		m_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_barrier.Transition.pResource = rsrc.get();
		m_barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		m_barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		m_barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		list->ResourceBarrier(1, &m_barrier);
		return *this;
	}
}