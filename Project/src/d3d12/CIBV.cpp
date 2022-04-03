#include "d3d12/CIBV.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12IndexBuffer::CD3D12IndexBuffer() noexcept :
		m_view(),
		m_rsrc()
	{}

	bool const CD3D12IndexBuffer::init(std::vector<unsigned int> const& indecies) noexcept {
		bool hResult = false;

		SIndexBufferDesc desc;
		desc.indecies = const_cast<unsigned int*>(indecies.data());
		desc.count = static_cast<unsigned int>(indecies.size());
		desc.view = {};

		hResult = m_rsrc.init(desc);
		if (!hResult) {
			return false;
		}

		m_view = desc.view;

		return true;
	}

	void CD3D12IndexBuffer::exit() noexcept {
		m_rsrc.exit();
	}

	D3D12_INDEX_BUFFER_VIEW const& CD3D12IndexBuffer::get() const noexcept {
		return m_view;
	}
}