/**	@file	CCD3D12Renderer.cpp
 *	@brief	Direct3D12 を利用したレンダラ
 */
#include "d3d12/CD3D12Renderer.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12Renderer::CD3D12Renderer() noexcept :
		m_barrier(),
		m_rtv(),
		m_dsv(),
		m_chain(),
		m_queue(),
		m_list(),
		m_fence(),
		m_rect(),
		m_viewport(),
		m_bufferCount(0U),
		m_currentIndex(0U),
		m_color(),
		m_hWnd(nullptr)
	{}

	CD3D12Renderer::~CD3D12Renderer() noexcept {
		uninit();
	}

	bool const CD3D12Renderer::init(RendererDesc const& desc) noexcept {
		if (m_hWnd) {
			return true;
		}

		RECT rect;
		GetClientRect(desc.wnd_handler, &rect);
		unsigned int width = static_cast<unsigned int>(labs(rect.right - rect.left));
		unsigned int height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

#if defined(DEBUG) | defined(_DEBUG)
		{
			ID3D12Debug* debug;
			HRESULT hResult = D3D12GetDebugInterface(
				__uuidof(debug),
				reinterpret_cast<void**>(&debug)
			);
			if (SUCCEEDED(hResult)) {
				debug->EnableDebugLayer();
			}
			safe_release(debug);
		}
#endif

		if (!CD3D12Device::getInstance().init()) {
			return false;
		}

		if (!m_queue.init(ED3D12CommandType::Direct)) {
			return false;
		}

		SSwapChainDesc chain;
		chain.wnd_handler = desc.wnd_handler;
		chain.frame_rate = desc.frame_rate;
		chain.buffer_size = desc.buffer_size;
		chain.cmd_queue = m_queue.get();
		chain.fullscreen = desc.fullscreen;
		if (!m_chain.init(chain)) {
			return false;
		}

		if (!m_list.init(ED3D12CommandType::Direct)) {
			return false;
		}

		SRenderTargetViewDesc rtv_desc;
		rtv_desc.pSwapchain = &m_chain;
		rtv_desc.FrameSize = desc.buffer_size;
		if (!m_rtv.init(rtv_desc)) {
			return false;
		}

		if (!m_dsv.init(desc.wnd_handler)) {
			return false;
		}

		if (!m_fence.init()) {
			return false;
		}

		m_hWnd = desc.wnd_handler;
		m_color = desc.color;
		m_bufferCount = desc.buffer_size;

		m_rect.top = 0U;
		m_rect.bottom = height;
		m_rect.left = 0U;
		m_rect.right = width;

		m_viewport.Height = static_cast<float>(height);
		m_viewport.Width = static_cast<float>(width);
		m_viewport.TopLeftX = 0.0f;
		m_viewport.TopLeftY = 0.0f;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		return true;
	}

	bool const CD3D12Renderer::reinit() noexcept {
		if (!m_hWnd) {
			OutputDebugStringA("ERROR : THE RENDERER HAS NOT BEEN INITIALIZED.\n");
			return false;
		}

		RECT rect;
		GetClientRect(m_hWnd, &rect);
		unsigned int width = static_cast<unsigned int>(labs(rect.right - rect.left));
		unsigned int height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

		if (width > 0U && height > 0U) {
			m_rtv.uninit();
			m_dsv.uninit();

			HRESULT hResult = m_chain->ResizeBuffers(
				m_bufferCount,
				width,
				height,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : SWAP CHAIN BUFFER SIZE RESIZING FAILED.\n");
				return false;
			}

			SRenderTargetViewDesc rtv_desc;
			rtv_desc.pSwapchain = &m_chain;
			rtv_desc.FrameSize = m_bufferCount;

			if (!m_rtv.init(rtv_desc)) {
				return false;
			}

			if (!m_dsv.init(m_hWnd)) {
				return false;
			}
		}

		m_rect.top = 0U;
		m_rect.bottom = height;
		m_rect.left = 0U;
		m_rect.right = width;

		m_viewport.Height = static_cast<float>(height);
		m_viewport.Width = static_cast<float>(width);
		m_viewport.TopLeftX = 0.0f;
		m_viewport.TopLeftY = 0.0f;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		return true;
	}

	void CD3D12Renderer::uninit() noexcept {
		waiting();
		return;
	}

	bool const CD3D12Renderer::before_rendering() noexcept {
		m_currentIndex = m_chain->GetCurrentBackBufferIndex();

		if (!m_list.recording()) {
			return false;
		}

		m_barrier.toRTMode(m_list, *const_cast<CD3D12Resource*>(&m_rtv.get(m_currentIndex)));

		if (m_dsv.get().get()) {
			m_list->OMSetRenderTargets(1U, const_cast<D3D12_CPU_DESCRIPTOR_HANDLE*>(&m_rtv.get(m_currentIndex).getCPUDescriptorHandle()), false, &m_dsv.get().getCPUDescriptorHandle());
			m_list->ClearDepthStencilView(m_dsv.get().getCPUDescriptorHandle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0U, 0U, nullptr);
		}
		else {
			m_list->OMSetRenderTargets(1U, const_cast<D3D12_CPU_DESCRIPTOR_HANDLE*>(&m_rtv.get(m_currentIndex).getCPUDescriptorHandle()), false, nullptr);
		}

		m_list->ClearRenderTargetView(*const_cast<D3D12_CPU_DESCRIPTOR_HANDLE*>(&m_rtv.get(m_currentIndex).getCPUDescriptorHandle()), m_color.p, 0, nullptr);

		m_list->RSSetViewports(1, &m_viewport);
		m_list->RSSetScissorRects(1, &m_rect);

		return true;
	}

	bool const CD3D12Renderer::after_rendering() noexcept {
		m_barrier.toPresentMode(m_list, *const_cast<CD3D12Resource*>(&m_rtv.get(m_currentIndex)));

		m_list.closing();

		ID3D12CommandList* pCmdLists[] = { m_list.get() };
		m_queue->ExecuteCommandLists(1U, pCmdLists);

		return true;
	}

	bool const CD3D12Renderer::presenting() noexcept {
		HRESULT hResult = S_OK;

		hResult = m_chain->Present(1U, 0U);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : PRESENTE FAILED DIRECT3D12 SWAP CHAIN.\n");
			return false;
		}

		if (!m_fence.presenting(m_queue)) {
			return false;
		}

		return true;
	}

	void CD3D12Renderer::waiting() noexcept {
		m_fence.wait(m_queue);
	}

	void CD3D12Renderer::setRootSignature(CD3D12RootSignature& rs) noexcept {
		if (m_list.isOpened()) {
			m_list->SetGraphicsRootSignature(rs.get());
		}
	}

	void CD3D12Renderer::setGraphicsPipeline(CD3D12PipelineState& pso) noexcept {
		if (m_list.isOpened()) {
			m_list->SetPipelineState(pso.get());
		}
	}

	CD3D12CommandList& CD3D12Renderer::getCmdList() noexcept {
		return m_list;
	}

	CD3D12DepthStencil& CD3D12Renderer::getDSV() noexcept {
		return m_dsv;
	}

	D3D12_RECT const CD3D12Renderer::getTrimRect() const noexcept {
		return m_rect;
	}

	D3D12_VIEWPORT const CD3D12Renderer::getViewport() const noexcept {
		return m_viewport;
	}

	unsigned int const CD3D12Renderer::getFrameBufferSize() const noexcept {
		return m_bufferCount;
	}

	float const CD3D12Renderer::getWidth() const noexcept {
		return m_viewport.Width;
	}

	float const CD3D12Renderer::getHeight() const noexcept {
		return m_viewport.Height;
	}

	float const CD3D12Renderer::getAspectRate() const noexcept {
		return static_cast<float>(m_viewport.Width) / static_cast<float>(m_viewport.Height);
	}

	unsigned int const CD3D12Renderer::getCurrentBufferIndex() const noexcept {
		return m_chain->GetCurrentBackBufferIndex();
	}
}