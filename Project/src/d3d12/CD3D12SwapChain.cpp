/**	@file	CD3D12SwapChain.cpp
 *	@brief	スワップチェイン
 */
#include "d3d12/CD3D12SwapChain.hpp"
#include "d3d12/CD3D12Device.hpp"
#include <exception>
#include <iostream>

namespace dlav {
	CD3D12SwapChain::CD3D12SwapChain(CD3D12SwapChain&& arg) noexcept :
		CD3D12SwapChain()
	{
		m_chain = arg.m_chain;
		arg.m_chain = nullptr;
	}

	CD3D12SwapChain& CD3D12SwapChain::operator=(CD3D12SwapChain&& rhs) noexcept {
		uninit();

		m_chain = rhs.m_chain;
		rhs.m_chain = nullptr;

		return *this;
	}

	CD3D12SwapChain::CD3D12SwapChain() noexcept :
		INoncopyable(),
		m_chain(nullptr)
	{}

	CD3D12SwapChain::~CD3D12SwapChain() noexcept {
		uninit();
	}

	bool const CD3D12SwapChain::init(SSwapChainDesc const& desc) noexcept {
		if (m_chain) {
			return true;
		}
		RECT rect;
		HRESULT hResult = S_OK;
		unsigned int width, height;

		GetClientRect(desc.wnd_handler, &rect);
		width = static_cast<unsigned int>(labs(rect.right - rect.left));
		height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

		DXGI_SWAP_CHAIN_DESC desc_ = {};
		desc_.BufferDesc.Width = width;
		desc_.BufferDesc.Height = height;
		desc_.BufferDesc.RefreshRate.Numerator = desc.frame_rate;
		desc_.BufferDesc.RefreshRate.Denominator = 1;
		desc_.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc_.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc_.SampleDesc.Count = 1;
		desc_.SampleDesc.Quality = 0;
		desc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc_.BufferCount = desc.buffer_size;
		desc_.OutputWindow = desc.wnd_handler;
		desc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc_.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		desc_.Windowed = !desc.fullscreen;

		IDXGIFactory4* factory = nullptr;
		hResult = CreateDXGIFactory2(
#			if defined(DEBUG) | defined(_DEBUG)
			DXGI_CREATE_FACTORY_DEBUG,
#			else
			0,
#			endif
			__uuidof(factory),
			reinterpret_cast<void**>(&factory)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED FACTORY.\n");
			return false;
		}

		IDXGIFactory7* fact = nullptr;
		hResult = factory->QueryInterface(
			__uuidof(fact),
			reinterpret_cast<void**>(&fact)
		);
		safe_release(factory);
		if (FAILED(hResult))
		{
			OutputDebugStringA("ERROR : REVERT FAILED SWAPCHAIN.\n");
			return false;
		}

		IDXGISwapChain* chain = nullptr;
		hResult = fact->CreateSwapChain(
			desc.cmd_queue,
			&desc_,
			&chain
		);
		safe_release(fact);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED SWAPCHAIN.\n");
			return false;
		}

		hResult = chain->QueryInterface(
			__uuidof(m_chain),
			reinterpret_cast<void**>(&m_chain)
		);
		safe_release(chain);
		if (FAILED(hResult))
		{
			OutputDebugStringA("ERROR : REVERT FAILED SWAPCHAIN.\n");
			return false;
		}

		return true;
	}

	void CD3D12SwapChain::uninit() noexcept {
		safe_release(m_chain);
	}

	IDXGISwapChain4* CD3D12SwapChain::get() const noexcept {
		return m_chain;
	}

	IDXGISwapChain4* CD3D12SwapChain::operator->() const noexcept {
		return m_chain;
	}
}