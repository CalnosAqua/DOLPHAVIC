/**	@file	CCBV.hpp
 *	@brief	定数バッファビュー
 */
#pragma once
#include "CD3D12DescriptorHeap.hpp"
#include "SD3D12Resource.hpp"
#include "CD3D12Device.hpp"
#include "CD3D12Renderer.hpp"
#include <vector>

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
		CD3D12ConstantBuffer& operator=(CD3D12ConstantBuffer<T>&&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CD3D12ConstantBuffer() noexcept;
		//!	@brief	デストラクタ
		~CD3D12ConstantBuffer() noexcept;

		//!	@brief	初期化関数
		bool const init(T const& data, unsigned int const& size) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	記述子ヒープ取得関数
		ID3D12DescriptorHeap* getHeap() const noexcept;
		//!	@brief	バッファ取得関数
		ID3D12Resource2*& get(unsigned int const&) const noexcept;
		//!	@brief	設定データ取得関数
		D3D12_CONSTANT_BUFFER_VIEW_DESC& getCBVDesc(unsigned int const&) const noexcept;
		//!	@brief	データ取得関数
		T& getData(unsigned int const&) noexcept;

		//!	@brief	レンダラへ登録
		void setRenderer(CD3D12Renderer&) noexcept;
		
	private:
		//!	@brief	記述子ヒープ
		CD3D12DescriptorHeap m_heap;
		//!	@brief	設定データ
		std::vector<D3D12_CONSTANT_BUFFER_VIEW_DESC> m_settings;
		//!	@brief	バッファ
		std::vector<SD3D12Resource> m_buffers;
		//!	@brief	データ
		std::vector<T*> m_datas;
		//!	@brief	初期化済みかどうか
		bool m_inited;
	};

	/* 実装 */

	template<typename T>
	inline CD3D12ConstantBuffer<T>::CD3D12ConstantBuffer() noexcept :
		m_heap(),
		m_settings(),
		m_buffers(),
		m_datas(),
		m_inited()
	{}

	template<typename T>
	inline CD3D12ConstantBuffer<T>::~CD3D12ConstantBuffer() noexcept {
		uninit();
	}

	template<typename T>
	inline bool const CD3D12ConstantBuffer<T>::init(T const& data, unsigned int const& size) noexcept {
		unsigned int const inc = CD3D12Device::getInstance()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		if (m_inited) {
			return true;
		}

		HRESULT hResult = S_OK;
		D3D12_CPU_DESCRIPTOR_HANDLE cpu;
		D3D12_GPU_DESCRIPTOR_HANDLE gpu;

		m_heap.init(ED3D12ViewType::CBV, size);
		m_settings.resize(size);
		m_buffers.resize(size);
		m_datas.resize(size);

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

		cpu = m_heap->GetCPUDescriptorHandleForHeapStart();
		gpu = m_heap->GetGPUDescriptorHandleForHeapStart();
		
		for (unsigned int idx = 0U; idx < size; ++idx) {
			hResult = CD3D12Device::getInstance()->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				__uuidof(m_buffers[idx].rsrc),
				reinterpret_cast<void**>(&m_buffers[idx].rsrc)
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : COMMITING FAILED CONSTANT BUFFER RESOURCE.\n");
				return false;
			}

			m_settings[idx].SizeInBytes = sizeof(T);
			m_settings[idx].BufferLocation = m_buffers[idx]->GetGPUVirtualAddress();
			m_buffers[idx].cpu = cpu;
			m_buffers[idx].gpu = gpu;

			CD3D12Device::getInstance()->CreateConstantBufferView(
				&m_settings[idx],
				m_buffers[idx].cpu
			);

			hResult = m_buffers[idx]->Map(
				0U,
				nullptr,
				reinterpret_cast<void**>(&m_datas[idx])
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : MAPPING FAILED CONSTANT BUFFER RESOURCE.\n");
				return false;
			}

			*m_datas[idx] = data;

			cpu.ptr += inc;
			gpu.ptr += inc;
		}

		m_inited = true;
		return true;
	}

	template<typename T>
	inline void CD3D12ConstantBuffer<T>::uninit() noexcept {
		for (SD3D12Resource& buffer : m_buffers) {
			buffer->Unmap(0U, nullptr);
			safe_release(buffer.rsrc);
		}
	}

	template<typename T>
	inline ID3D12Resource2*& CD3D12ConstantBuffer<T>::get(unsigned int const& idx) const noexcept {
		return *const_cast<ID3D12Resource2**>(&m_buffers[idx].rsrc);
	}

	template<typename T>
	inline D3D12_CONSTANT_BUFFER_VIEW_DESC& CD3D12ConstantBuffer<T>::getCBVDesc(unsigned int const& idx) const noexcept {
		return *const_cast<D3D12_CONSTANT_BUFFER_VIEW_DESC*>(&m_settings[idx]);
	}

	template<typename T>
	inline T& CD3D12ConstantBuffer<T>::getData(unsigned int const& idx) noexcept {
		return *const_cast<T*>(m_datas[idx]);
	}

	template<typename T>
	inline void CD3D12ConstantBuffer<T>::setRenderer(CD3D12Renderer& rend) noexcept {
		ID3D12DescriptorHeap* heap = getHeap();
		rend.getCmdList()->SetDescriptorHeaps(1, const_cast<ID3D12DescriptorHeap* const*>(&heap));
		rend.getCmdList()->SetGraphicsRootConstantBufferView(0, getCBVDesc(rend.getCurrentBufferIndex()).BufferLocation);
		heap = nullptr;
	}

	template<typename T>
	inline ID3D12DescriptorHeap* CD3D12ConstantBuffer<T>::getHeap() const noexcept {
		return const_cast<CD3D12DescriptorHeap*>(&m_heap)->get();
	}
}