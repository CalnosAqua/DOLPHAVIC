/**	@file	CD3D12DescriptorHeap.cpp
 *	@brief	記述子ヒープ
 */
#include "d3d12/CD3D12DescriptorHeap.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12DescriptorHeap::CD3D12DescriptorHeap(CD3D12DescriptorHeap&& arg) noexcept :
		CD3D12DescriptorHeap()
	{
		m_heap = arg.m_heap;
		arg.m_heap = nullptr;
	}

	CD3D12DescriptorHeap& CD3D12DescriptorHeap::operator=(CD3D12DescriptorHeap&& rhs) noexcept {
		uninit();

		m_heap = rhs.m_heap;
		rhs.m_heap = nullptr;

		return *this;
	}

	CD3D12DescriptorHeap::CD3D12DescriptorHeap() noexcept :
		INoncopyable(),
		m_heap(nullptr)
	{}

	CD3D12DescriptorHeap::~CD3D12DescriptorHeap() noexcept {
		uninit();
	}

	bool const CD3D12DescriptorHeap::init(ED3D12ViewType const& type, unsigned int const& size) noexcept {
		if (m_heap) {
			return true;
		}

		HRESULT hResult = S_OK;
		D3D12_DESCRIPTOR_HEAP_DESC heap = {};

		heap.NodeMask = 0U;
		heap.NumDescriptors = size;

		switch (type) {
		case ED3D12ViewType::RTV:
			heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			break;
		case ED3D12ViewType::DSV:
			heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			break;
		case ED3D12ViewType::CBV:
		case ED3D12ViewType::SRV:
		case ED3D12ViewType::UAV:
			heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			break;
		case ED3D12ViewType::Sampler:
			heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
			heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			break;
		default:
			OutputDebugStringA("ERROR : SELECT DESCRIPTOR TYPE CORRUPTED.\n");
			return false;
		}

		hResult = CD3D12Device::getInstance()->CreateDescriptorHeap(
			&heap,
			__uuidof(m_heap),
			reinterpret_cast<void**>(&m_heap)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED DIREDT3D12 DESCRIPTOR HEAP.\n");
			return false;
		}

		return true;
	}

	void CD3D12DescriptorHeap::uninit() noexcept {
		safe_release(m_heap);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE const CD3D12DescriptorHeap::getCPUStartHandle() const noexcept {
		return m_heap->GetCPUDescriptorHandleForHeapStart();
	}

	D3D12_GPU_DESCRIPTOR_HANDLE const CD3D12DescriptorHeap::getGPUStartHandle() const noexcept {
		return m_heap->GetGPUDescriptorHandleForHeapStart();
	}

	ID3D12DescriptorHeap* CD3D12DescriptorHeap::get() noexcept {
		return m_heap;
	}

	ID3D12DescriptorHeap* CD3D12DescriptorHeap::operator->() const noexcept {
		return m_heap;
	}
}