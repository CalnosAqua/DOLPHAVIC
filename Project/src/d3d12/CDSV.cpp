/**	@file	CDSV.hpp
 *	@brief	深度バッファビュー
 */
#include "d3d12/CDSV.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12DepthStencil::CD3D12DepthStencil() noexcept :
		m_heap(),
		m_data()
	{}

	CD3D12DepthStencil::~CD3D12DepthStencil() noexcept {
		exit();
	}

	bool const CD3D12DepthStencil::init(HWND const& wnd_handle) noexcept {
		bool hResult = false;
		RECT rect = {};

		GetClientRect(wnd_handle, &rect);
		unsigned int width = static_cast<unsigned int>(labs(rect.right - rect.left));
		unsigned int height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

		hResult = m_heap.init(ED3D12ViewType::DSV, 1U);
		if (!hResult) {
			return false;
		}

		SDepthStencilDesc desc;
		desc.handle = m_heap.getCPUStartHandle();
		desc.height = height;
		desc.width = width;

		hResult = m_data.init(desc);
		if (!hResult) {
			return false;
		}

		return true;
	}

	void CD3D12DepthStencil::exit() noexcept {
		rsrc_release();
		m_heap.exit();
	}

	void CD3D12DepthStencil::rsrc_release() noexcept {
		m_data.exit();
	}

	CD3D12Resource const& CD3D12DepthStencil::get() const noexcept {
		return m_data;
	}
}