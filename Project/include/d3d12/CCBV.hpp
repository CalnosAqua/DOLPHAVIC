/**	@file	CCBV.hpp
 *	@brief	定数バッファビュー
 */
#pragma once
#pragma warning(disable : 26495)
#include "CD3D12DescriptorHeap.hpp"
#include "SD3D12Resource.hpp"
#include "CD3D12Device.hpp"
#include "CD3D12CommandList.hpp"
#include <array>

namespace dlav {
	/**	@struct CD3D12ConstantBufferView
	 *	@brief	定数バッファビュー
	 */
	template <typename T>
	class CD3D12ConstantBuffer final : public INoncopyable<CD3D12ConstantBuffer<T>> {
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12ConstantBuffer(CD3D12ConstantBuffer<T>&&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CD3D12ConstantBuffer<T>& operator=(CD3D12ConstantBuffer<T>&&) noexcept = default;

		//!	@brief	データ代入演算子
		CD3D12ConstantBuffer<T>& operator=(T const&) noexcept;
		//!	@brief	データキャスト演算子
		explicit operator T const& () const noexcept;

		//!	@brief	デフォルトコンストラクタ
		CD3D12ConstantBuffer() noexcept;
		//!	@brief	デストラクタ
		~CD3D12ConstantBuffer() noexcept;

		//!	@brief	初期化関数
		bool const init(T const& data) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	バッファ取得関数
		ID3D12Resource2*& get() const noexcept;

		//!	@brief	レンダラへ登録する関数
		void setRenderer(CD3D12CommandList&) noexcept;
		
	private:
		template<typename T>
		struct SConstantResource final :
			public SD3D12Resource
		{
			//!	@brief	定数バッファビュー
			D3D12_CONSTANT_BUFFER_VIEW_DESC cbv;
			//!	@brief	定数バッファビュー
			T* data;
		};

		//!	@brief	記述子ヒープ
		CD3D12DescriptorHeap m_heap;
		//!	@brief	リソース
		std::array<SConstantResource<T>, 2U> m_rsrces;
		//!	@brief	現在の対象インデックス
		unsigned int m_curIndex;
	};

	/* 実装 */

	template<typename T>
	inline CD3D12ConstantBuffer<T>& CD3D12ConstantBuffer<T>::operator=(T const& rhs) noexcept {
		for (SConstantResource<T>& rsrc : m_rsrces) {
			*rsrc.data = rhs;
		}
		return *this;
	}

	template<typename T>
	inline CD3D12ConstantBuffer<T>::operator T const& () const noexcept {
		return *m_rsrces[m_curIndex].data;
	}

	template<typename T>
	inline CD3D12ConstantBuffer<T>::CD3D12ConstantBuffer() noexcept :
		m_heap(),
		m_rsrces(),
		m_curIndex()
	{}

	template<typename T>
	inline CD3D12ConstantBuffer<T>::~CD3D12ConstantBuffer() noexcept {
		uninit();
	}

	template<typename T>
	inline bool const CD3D12ConstantBuffer<T>::init(T const& data) noexcept {
		if (m_rsrces[0].data != nullptr && m_rsrces[1].data != nullptr) {
			return true;
		}

		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1U;
		prop.VisibleNodeMask = 1U;

		D3D12_RESOURCE_DESC desc = {};
		desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment = 0U;
		desc.Width = sizeof(T);
		desc.Height = 1U;
		desc.DepthOrArraySize = 1U;
		desc.MipLevels = 1U;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count = 1U;
		desc.SampleDesc.Quality = 0U;
		desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		if (!m_heap.init(ED3D12ViewType::CBV, static_cast<unsigned int>(m_rsrces.size()))) {
			return false;
		}

		HRESULT hResult = S_OK;
		D3D12_CPU_DESCRIPTOR_HANDLE cpu = m_heap->GetCPUDescriptorHandleForHeapStart();
		D3D12_GPU_DESCRIPTOR_HANDLE gpu = m_heap->GetGPUDescriptorHandleForHeapStart();
		unsigned int const inc =
			CD3D12Device::getInstance()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		
		for (unsigned int idx = 0U; idx < m_rsrces.size(); ++idx) {
			hResult = CD3D12Device::getInstance()->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				__uuidof(m_rsrces[idx].rsrc),
				reinterpret_cast<void**>(&m_rsrces[idx].rsrc)
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : COMMITING FAILED CONSTANT BUFFER RESOURCE.\n");
				return false;
			}

			m_rsrces[idx].cbv.SizeInBytes = sizeof(T);
			m_rsrces[idx].cbv.BufferLocation = m_rsrces[idx]->GetGPUVirtualAddress();
			m_rsrces[idx].cpu = cpu;
			m_rsrces[idx].gpu = gpu;

			CD3D12Device::getInstance()->CreateConstantBufferView(
				&m_rsrces[idx].cbv,
				m_rsrces[idx].cpu
			);

			hResult = m_rsrces[idx]->Map(
				0U,
				nullptr,
				reinterpret_cast<void**>(&m_rsrces[idx].data)
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : MAPPING FAILED CONSTANT BUFFER RESOURCE.\n");
				return false;
			}

			*m_rsrces[idx].data = data;

			cpu.ptr += inc;
			gpu.ptr += inc;
		}

		return true;
	}

	template<typename T>
	inline void CD3D12ConstantBuffer<T>::uninit() noexcept {
		for (SConstantResource<T>& rsrc : m_rsrces) {
			rsrc->Unmap(0U, nullptr);
			safe_release(rsrc.rsrc);
		}
	}

	template<typename T>
	inline ID3D12Resource2*& CD3D12ConstantBuffer<T>::get() const noexcept {
		return *const_cast<ID3D12Resource2**>(&m_rsrces[m_curIndex].rsrc);
	}

	template<typename T>
	inline void CD3D12ConstantBuffer<T>::setRenderer(CD3D12CommandList& lst) noexcept {
		lst->SetDescriptorHeaps(1U, const_cast<ID3D12DescriptorHeap* const*>(&m_heap.get()));
		lst->SetGraphicsRootConstantBufferView(0U, m_rsrces[m_curIndex].cbv.BufferLocation);
		m_curIndex = (m_curIndex + 1U) % 2U;
	}
}