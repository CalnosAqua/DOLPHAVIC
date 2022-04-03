/**	@file	CVBV.hpp
 *	@brief	頂点バッファ
 */
#pragma once
#include "util/INonmovable.hpp"
#include "CD3D12Resource.hpp"
#include "CD3D12Device.hpp"
#include <d3d12.h>
#include <vector>
#include <memory>

namespace dlav {
	/**	@struct CD3D12VertexBuffer
	 *	@brief	頂点バッファ
	 */
	template <typename Vertex>
	class CD3D12VertexBuffer final : public INonmovable<CD3D12VertexBuffer<Vertex>> {
	public	:
		//!	@brief	デフォルトコンストラクタ
		CD3D12VertexBuffer() noexcept;
		//!	@brief	デストラクタ
		~CD3D12VertexBuffer() noexcept;

		//!	@brief	初期化関数
		bool const init(std::vector<Vertex> const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	リソース取得関数
		D3D12_VERTEX_BUFFER_VIEW const& get() const noexcept;

	private	:
		//!	@brief	ビュー記述子
		D3D12_VERTEX_BUFFER_VIEW m_view;
		//!	@brief	リソース
		SD3D12Resource m_rsrc;
	};

	/* 実装 */

	template<typename Vertex>
	inline CD3D12VertexBuffer<Vertex>::CD3D12VertexBuffer() noexcept :
		m_view(),
		m_rsrc()
	{}

	template<typename Vertex>
	inline CD3D12VertexBuffer<Vertex>::~CD3D12VertexBuffer() noexcept {
		exit();
	}

	template<typename Vertex>
	inline bool const CD3D12VertexBuffer<Vertex>::init(std::vector<Vertex> const& vertices) noexcept {
		HRESULT hResult = S_OK;

		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1;
		prop.VisibleNodeMask = 1;

		D3D12_RESOURCE_DESC desc = {};
		desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment = 0;
		desc.Width = static_cast<UINT64>(sizeof(Vertex)) * vertices.size();
		desc.Height = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		hResult = CD3D12Device::getInstance()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			__uuidof(m_rsrc.rsrc),
			reinterpret_cast<void**>(&m_rsrc.rsrc)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : COMMITING FAILED CONSTANT BUFFER RESOURCE.\n");
			return false;
		}

		void* ptr = nullptr;
		m_rsrc->Map(0U, nullptr, &ptr);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : MAPPING FAILED CONSTANT BUFFER RESOURCE.\n");
			return false;
		}

		memcpy(ptr, vertices.data(), vertices.size() * sizeof(Vertex));

		m_rsrc->Unmap(0U, nullptr);

		m_view.BufferLocation = m_rsrc->GetGPUVirtualAddress();
		m_view.SizeInBytes = sizeof(Vertex) * static_cast<unsigned int>(vertices.size());
		m_view.StrideInBytes = sizeof(Vertex);

		return true;
	}

	template<typename Vertex>
	inline void CD3D12VertexBuffer<Vertex>::exit() noexcept {
		safe_release(m_rsrc.rsrc);
	}

	template<typename Vertex>
	inline D3D12_VERTEX_BUFFER_VIEW const& CD3D12VertexBuffer<Vertex>::get() const noexcept {
		return m_view;
	}
}