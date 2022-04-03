/**	@file	CRTV.hpp
 *	@brief	レンダーターゲットビュー
 */
#include "d3d12/CRTV.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12RenderTarget::CD3D12RenderTarget() noexcept :
		m_heap(),
		m_datas()
	{}

	CD3D12RenderTarget::~CD3D12RenderTarget() noexcept {
		exit();
	}

	bool const CD3D12RenderTarget::init(SRenderTargetViewDesc const& desc) noexcept {
		bool hResult = false;

		m_datas.resize(desc.FrameSize);

		hResult = m_heap.init(ED3D12ViewType::RTV, desc.FrameSize);
		if (!hResult) {
			return false;
		}

		size_t inc = CD3D12Device::getInstance()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		SRenderTargetDesc desc_;
		desc_.swapchain = (*desc.pSwapchain).get();
		desc_.handle = m_heap->GetCPUDescriptorHandleForHeapStart();

		for (UINT idx = 0U; idx < desc.FrameSize; ++idx) {
			desc_.index = idx;

			hResult = m_datas[idx].init(desc_);
			if (!hResult) {
				return false;
			}

			desc_.handle.ptr += inc;
		}

		return true;
	}

	void CD3D12RenderTarget::exit() noexcept {
		rsrc_release();
		m_heap.exit();
	}

	void CD3D12RenderTarget::rsrc_release() noexcept {
		for (CD3D12Resource& rsrc : m_datas) {
			rsrc.exit();
		}
	}

	CD3D12Resource const& CD3D12RenderTarget::get(unsigned int const& idx) const noexcept {
		return m_datas[idx];
	}
}