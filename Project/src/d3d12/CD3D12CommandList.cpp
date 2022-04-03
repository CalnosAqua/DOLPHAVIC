/**	@file	CD3D12CommandList.cpp
 *	@brief	Direct3D12 用のコマンドリストクラス
 */
#include "d3d12/CD3D12CommandList.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12CommandList::CD3D12CommandList(CD3D12CommandList&& arg) noexcept :
		CD3D12CommandList()
	{
		m_alloc = arg.m_alloc;
		arg.m_alloc = nullptr;
		
		m_list = arg.m_list;
		arg.m_list = nullptr;

		m_opened = arg.m_opened;
	}

	CD3D12CommandList& CD3D12CommandList::operator=(CD3D12CommandList&& rhs) noexcept {
		exit();
		
		m_alloc = rhs.m_alloc;
		rhs.m_alloc = nullptr;

		m_list = rhs.m_list;
		rhs.m_list = nullptr;

		m_opened = rhs.m_opened;

		return *this;
	}

	CD3D12CommandList::CD3D12CommandList() noexcept :
		m_alloc(nullptr),
		m_list(nullptr),
		m_opened()
	{}

	CD3D12CommandList::~CD3D12CommandList() noexcept {
		exit();
	}

	bool const CD3D12CommandList::init(ED3D12CommandType const& type) noexcept {
		if (m_list && m_alloc) {
			return true;
		}
		HRESULT hResult = S_OK;
		D3D12_COMMAND_LIST_TYPE type_;

		switch (type) {
		case ED3D12CommandType::Direct:
			type_ = D3D12_COMMAND_LIST_TYPE_DIRECT;
			break;
		case ED3D12CommandType::Copy:
			type_ = D3D12_COMMAND_LIST_TYPE_COPY;
			break;
		case ED3D12CommandType::Compute:
			type_ = D3D12_COMMAND_LIST_TYPE_COMPUTE;
			break;
		case ED3D12CommandType::Bundle:
			type_ = D3D12_COMMAND_LIST_TYPE_BUNDLE;
			break;
		default:
			OutputDebugStringA("ERROR : THE TYPE SETTING IS INCOLLECT.\n");
			return false;
		}

		hResult = CD3D12Device::getInstance()->CreateCommandAllocator(
			type_,
			__uuidof(m_alloc),
			reinterpret_cast<void**>(&m_alloc)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED COMMAND ALLOCATOR.\n");
			return false;
		}

		hResult = CD3D12Device::getInstance()->CreateCommandList(
			0U,
			type_,
			m_alloc,
			nullptr,
			__uuidof(m_list),
			reinterpret_cast<void**>(&m_list)
		);
		if (FAILED(hResult)) {
			safe_release(m_alloc);
			OutputDebugStringA("ERROR : CREATE FAILED COMMAND LIST.\n");
			return false;
		}

		if (!closing()) {
			return false;
		}

		return true;
	}

	void CD3D12CommandList::exit() noexcept {
		safe_release(m_list);
		safe_release(m_alloc);
	}

	bool const CD3D12CommandList::recording() noexcept {
		HRESULT hResult = S_OK;

		hResult = m_alloc->Reset();
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : RESET FAILED COMMAND ALLOCATOR.\n");
			return false;
		}
		
		hResult = m_list->Reset(m_alloc, nullptr);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : RESET FAILED COMMAND LIST.\n");
			return false;
		}
		
		m_opened = true;
		return true;
	}

	bool const CD3D12CommandList::closing() noexcept {
		HRESULT hResult = S_OK;

		hResult = m_list->Close();
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CLOSE FAILED COMMAND LIST.\n");
			return false;
		}

		m_opened = false;
		return true;
	}

	ID3D12GraphicsCommandList6* CD3D12CommandList::get() const noexcept {
		return m_list;
	}

	ID3D12GraphicsCommandList6* CD3D12CommandList::operator->() const noexcept {
		return m_list;
	}

	bool const CD3D12CommandList::isOpened() const noexcept {
		return m_opened;
	}
}