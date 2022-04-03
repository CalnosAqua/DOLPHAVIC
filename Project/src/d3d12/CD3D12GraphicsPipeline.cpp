/**	@file	CD3D12GraphicsPipeline.cpp
 *	@brief	グラフィックスパイプライン
 */
#include "d3d12/CD3D12GraphicsPipeline.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12GraphicsPipeline::CD3D12GraphicsPipeline(CD3D12GraphicsPipeline&& arg) noexcept :
		CD3D12GraphicsPipeline()
	{
		m_signature = arg.m_signature;
		arg.m_signature = nullptr;

		m_state = arg.m_state;
		arg.m_state = nullptr;

		m_layout = move(arg.m_layout);

		m_flags = arg.m_flags;
	}

	CD3D12GraphicsPipeline& CD3D12GraphicsPipeline::operator=(CD3D12GraphicsPipeline&& rhs) noexcept {
		exit();

		m_signature = rhs.m_signature;
		rhs.m_signature = nullptr;

		m_state = rhs.m_state;
		rhs.m_state = nullptr;

		m_layout = move(rhs.m_layout);

		m_flags = rhs.m_flags;

		return *this;
	}

	CD3D12GraphicsPipeline::CD3D12GraphicsPipeline() noexcept :
		INoncopyable(),
		m_layout(),
		m_signature(),
		m_state(),
		m_flags(D3D12_ROOT_SIGNATURE_FLAG_NONE)
	{}

	CD3D12GraphicsPipeline::~CD3D12GraphicsPipeline() noexcept {
		exit();
	}

	bool const CD3D12GraphicsPipeline::init(SGraphicsPipelineDesc const& arg) noexcept {
		if (m_signature != nullptr && m_state != nullptr) {
			return true;
		}

		if (arg.vs == nullptr) {
			OutputDebugStringA("ERROR : VERTEX SHADERS ARE NOT SET.\n");
			return false;
		}
		if (arg.ps == nullptr) {
			OutputDebugStringA("ERROR : PIXEL SHADERS ARE NOT SET.\n");
			return false;
		}

		return true;
	}

	void CD3D12GraphicsPipeline::exit() noexcept {
		m_flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
		m_layout.clear();
		safe_release(m_signature);
		safe_release(m_state);
	}

	CD3D12GraphicsPipeline& CD3D12GraphicsPipeline::add(SInputLayoutDesc const& arg) noexcept {
		D3D12_INPUT_ELEMENT_DESC desc = {};
		desc.SemanticIndex = arg.index;
		desc.SemanticName = arg.name;
		desc.Format = arg.format;
		desc.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		desc.InputSlot = 0U;
		desc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0U;
		m_layout.emplace_back(desc);
		return *this;
	}

	CD3D12GraphicsPipeline& CD3D12GraphicsPipeline::remove(unsigned int const& index) noexcept {
		unsigned int idx = index;

		if (m_layout.size() == 0U) {
			return *this;
		}

		if (idx > m_layout.size()) {
			idx = static_cast<unsigned int>(m_layout.size()) - 1U;
		}

		m_layout.erase(m_layout.cbegin() + idx);

		return *this;
	}

	CD3D12GraphicsPipeline& CD3D12GraphicsPipeline::clear() noexcept {
		m_layout.clear();
		return *this;
	}

	void CD3D12GraphicsPipeline::setCmdList(CD3D12CommandList& lst) noexcept {

	}
}