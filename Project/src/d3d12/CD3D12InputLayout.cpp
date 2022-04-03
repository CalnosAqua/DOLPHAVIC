/**	@file	CD3D12InputLayout.cpp
 *	@brief	Direct3D12 用の入力レイアウト
 */
#include "d3d12/CD3D12InputLayout.hpp"

namespace dlav {
	CD3D12InputLayout::CD3D12InputLayout() noexcept :
		m_elems()
	{}

	CD3D12InputLayout& CD3D12InputLayout::add(SInputLayoutDesc const& desc) noexcept {
		D3D12_INPUT_ELEMENT_DESC desc_ = {};
		desc_.SemanticIndex = desc.index;
		desc_.SemanticName = desc.name;
		desc_.Format = desc.format;
		desc_.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		desc_.InputSlot = 0U;
		desc_.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		desc_.InstanceDataStepRate = 0U;
		m_elems.emplace_back(desc_);
		return *this;
	}

	CD3D12InputLayout& CD3D12InputLayout::remove(unsigned int const& index) noexcept {
		unsigned int idx = index;

		if (m_elems.size() == 0U) {
			return *this;
		}

		if (idx > m_elems.size()) {
			idx = static_cast<unsigned int>(m_elems.size()) - 1U;
		}

		m_elems.erase(m_elems.cbegin() + idx);

		return *this;
	}

	CD3D12InputLayout& CD3D12InputLayout::clear() noexcept {
		m_elems.clear();
		return *this;
	}

	D3D12_INPUT_ELEMENT_DESC* CD3D12InputLayout::getAddress() const noexcept {
		return const_cast<D3D12_INPUT_ELEMENT_DESC*>(m_elems.data());
	}
	
	unsigned int const CD3D12InputLayout::getCount() const noexcept {
		return static_cast<unsigned int>(m_elems.size());
	}
}