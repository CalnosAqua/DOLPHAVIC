/**	@file	CD3D12CommandQueue.cpp
 *	@brief	Direct3D12 用のコマンドキュークラス
 */
#include "d3d12/CD3D12CommandQueue.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12CommandQueue::CD3D12CommandQueue(CD3D12CommandQueue&& arg) noexcept :
		CD3D12CommandQueue()
	{
		m_queue = arg.m_queue;
		arg.m_queue = nullptr;
	}

	CD3D12CommandQueue& CD3D12CommandQueue::operator=(CD3D12CommandQueue&& rhs) noexcept {
		uninit();
		
		m_queue = rhs.m_queue;
		rhs.m_queue = nullptr;

		return *this;
	}

	CD3D12CommandQueue::CD3D12CommandQueue() noexcept :
		INoncopyable(),
		m_queue(nullptr)
	{}

	CD3D12CommandQueue::~CD3D12CommandQueue() noexcept {
		uninit();
	}

	bool const CD3D12CommandQueue::init(ED3D12CommandType const& type) noexcept {
		if (m_queue) {
			return true;
		}

		HRESULT hResult = S_OK;
		D3D12_COMMAND_QUEUE_DESC desc_ = {};

		desc_.NodeMask = 0U;
		desc_.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc_.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

		switch (type) {
		case ED3D12CommandType::Direct:
			desc_.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			break;
		case ED3D12CommandType::Copy:
			desc_.Type = D3D12_COMMAND_LIST_TYPE_COPY;
			break;
		case ED3D12CommandType::Compute:
			desc_.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
			break;
		default:
			OutputDebugStringA("ERROR : THE TYPE SETTING IS INCOLLECT.\n");
			return false;
		}

		hResult = CD3D12Device::getInstance()->CreateCommandQueue(
			&desc_,
			__uuidof(m_queue),
			reinterpret_cast<void**>(&m_queue)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED DIRECT3D12 COMMAND QUEUE.\n");
			return false;
		}

		return true;
	}

	void CD3D12CommandQueue::uninit() noexcept {
		safe_release(m_queue);
	}

	ID3D12CommandQueue*& CD3D12CommandQueue::get() const noexcept {
		return *const_cast<ID3D12CommandQueue**>(&m_queue);
	}

	ID3D12CommandQueue* CD3D12CommandQueue::operator->() const noexcept {
		return m_queue;
	}
}