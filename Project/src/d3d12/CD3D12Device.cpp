/**	@file	CD3D12Device.cpp
 *	@brief	Direct3D12 用のデバイスクラス
 */
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12Device::CD3D12Device() noexcept :
		ISingleton(),
		m_device(nullptr)
	{}

	CD3D12Device::~CD3D12Device() noexcept {
		exit();
	}

	bool const CD3D12Device::init() noexcept {
		if (m_device != nullptr) {
			return true;
		}

		HRESULT hResult = S_OK;
		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_1
		};

		static unsigned int COUNT = static_cast<unsigned int>(sizeof(levels) / sizeof(levels[0]));
		for (unsigned int idx = 0U; idx < COUNT; ++idx) {
			hResult = D3D12CreateDevice(
				nullptr,
				levels[idx],
				__uuidof(m_device),
				reinterpret_cast<void**>(&m_device)
			);
			if (SUCCEEDED(hResult)) {
				break;
			}
		}
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED DIRECT3D12 DEVICE.\n");
			return false;
		}

		return true;
	}

	void CD3D12Device::exit() noexcept {
		safe_release(m_device);
	}

	ID3D12Device8* CD3D12Device::operator->() const noexcept {
		return m_device;
	}
}