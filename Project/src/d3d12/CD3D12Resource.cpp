/**	@file	CD3D12Resource.cpp
 *	@brief	Direct3D12 用のリソースクラス
 */
#include "d3d12/CD3D12Resource.hpp"
#include "d3d12/CD3D12Device.hpp"
#include <crtdbg.h>

namespace dlav {
	CD3D12Resource::CD3D12Resource() noexcept :
		INoncopyable(),
		m_rsrc(),
		m_binded()
	{}

	bool const CD3D12Resource::init(SRenderTargetDesc const& desc) noexcept {
		HRESULT hResult = S_OK;

		hResult = desc.swapchain->GetBuffer(
			desc.index,
			__uuidof(m_rsrc.rsrc),
			reinterpret_cast<void**>(&m_rsrc.rsrc)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : LOAD FAILED DIRECT3D12 RENDER TARGET RESOURCE.\n");
			return false;
		}

		D3D12_RENDER_TARGET_VIEW_DESC rtv = {};
		rtv.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtv.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		rtv.Texture2D.MipSlice = 0;
		rtv.Texture2D.PlaneSlice = 0;

		m_rsrc.cpu = desc.handle;

		CD3D12Device::getInstance()->CreateRenderTargetView(
			m_rsrc.rsrc,
			&rtv,
			m_rsrc.cpu
		);

		return true;
	}

	bool const CD3D12Resource::init(SDepthStencilDesc const& desc) noexcept {
		HRESULT hResult = S_OK;

		m_rsrc.cpu = desc.handle;

		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_DEFAULT;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1U;
		prop.VisibleNodeMask = 1U;
		
		D3D12_RESOURCE_DESC desc_ = {};
		desc_.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		desc_.Alignment = 0U;
		desc_.Width = desc.width;
		desc_.Height = desc.height;
		desc_.DepthOrArraySize = 1U;
		desc_.MipLevels = 0U;
		desc_.Format = DXGI_FORMAT_D32_FLOAT;
		desc_.SampleDesc.Count = 1U;
		desc_.SampleDesc.Quality = 0U;
		desc_.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		desc_.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		D3D12_CLEAR_VALUE value = {};
		value.Format = DXGI_FORMAT_D32_FLOAT;
		value.DepthStencil.Depth = 1.0f;
		value.DepthStencil.Stencil = 0U;

		hResult = CD3D12Device::getInstance()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc_,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&value,
			__uuidof(m_rsrc.rsrc),
			reinterpret_cast<void**>(&m_rsrc.rsrc)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : COMMITING FAILED DEPTH STENCIL RESOURCE.\n");
			return false;
		}

		// 深度バッファビューを生成。
		D3D12_DEPTH_STENCIL_VIEW_DESC dsv = {};
		dsv.Format = DXGI_FORMAT_D32_FLOAT;
		dsv.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsv.Flags = D3D12_DSV_FLAG_NONE;

		CD3D12Device::getInstance()->CreateDepthStencilView(
			m_rsrc.rsrc,
			&dsv,
			m_rsrc.cpu
		);

		return true;
	}

	bool const CD3D12Resource::init(SIndexBufferDesc const& desc) noexcept {
		HRESULT hResult = S_OK;

		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1;
		prop.VisibleNodeMask = 1;

		D3D12_RESOURCE_DESC desc_ = {};
		desc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc_.Alignment = 0;
		desc_.Width = static_cast<UINT64>(sizeof(unsigned int)) * desc.count;
		desc_.Height = 1;
		desc_.DepthOrArraySize = 1;
		desc_.MipLevels = 1;
		desc_.Format = DXGI_FORMAT_UNKNOWN;
		desc_.SampleDesc.Count = 1;
		desc_.SampleDesc.Quality = 0;
		desc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc_.Flags = D3D12_RESOURCE_FLAG_NONE;

		hResult = CD3D12Device::getInstance()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc_,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			__uuidof(m_rsrc.rsrc),
			reinterpret_cast<void**>(&m_rsrc.rsrc)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : COMMITING FAILED INDEX BUFFER RESOURCE.\n");
			return false;
		}

		void* ptr = nullptr;
		hResult = m_rsrc->Map(0U, nullptr, &ptr);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : MAPPING FAILED INDEX BUFFER RESOURCE.\n");
			return false;
		}

		memcpy(ptr, desc.indecies, static_cast<UINT64>(sizeof(unsigned int)) * desc.count);

		m_rsrc->Unmap(0U, nullptr);

		desc.view.BufferLocation = m_rsrc->GetGPUVirtualAddress();
		desc.view.SizeInBytes = sizeof(unsigned int) * desc.count;
		desc.view.Format = DXGI_FORMAT_R32_UINT;

		return true;
	}

	void CD3D12Resource::uninit() noexcept {
		if (m_binded) {
			m_rsrc->Unmap(0U, nullptr);
			m_binded = false;
		}
		safe_release(m_rsrc.rsrc);
	}

	ID3D12Resource2* CD3D12Resource::operator->() const noexcept {
		return m_rsrc.rsrc;
	}

	ID3D12Resource2*& CD3D12Resource::get() const noexcept {
		return *const_cast<ID3D12Resource2**>(&m_rsrc.rsrc);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE& CD3D12Resource::getCPUDescriptorHandle() const noexcept {
		return *const_cast<D3D12_CPU_DESCRIPTOR_HANDLE*>(&m_rsrc.cpu);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE& CD3D12Resource::getGPUDescriptorHandle() const noexcept {
		return *const_cast<D3D12_GPU_DESCRIPTOR_HANDLE*>(&m_rsrc.gpu);
	}
}