/**	@file	CD3D12RootSignature.cpp
 *	@brief	ルートシグネチャ
 */
#include "d3d12/CD3D12RootSignature.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12RootSignature::CD3D12RootSignature(CD3D12RootSignature&& arg) noexcept :
		CD3D12RootSignature()
	{
		m_signature = arg.m_signature;
		arg.m_signature = nullptr;
	}
	
	CD3D12RootSignature& CD3D12RootSignature::operator=(CD3D12RootSignature&& rhs) noexcept {
		exit();
		m_signature = rhs.m_signature;
		rhs.m_signature = nullptr;
		return *this;
	}

	CD3D12RootSignature::CD3D12RootSignature() noexcept :
		m_signature(nullptr)
	{}

	CD3D12RootSignature::~CD3D12RootSignature() noexcept {
		exit();
	}

	bool const CD3D12RootSignature::init(std::vector<D3D12_ROOT_PARAMETER> const& prms, D3D12_ROOT_SIGNATURE_FLAGS const& flags) noexcept {
		HRESULT hResult = S_OK;
		ID3DBlob* blob;
		ID3DBlob* error;

		D3D12_ROOT_SIGNATURE_DESC desc = {};
		desc.Flags = flags;
		desc.NumParameters = static_cast<unsigned int>(prms.size());
		desc.pParameters = prms.data();
		desc.NumStaticSamplers = 0;
		desc.pStaticSamplers = nullptr;

		hResult = D3D12SerializeRootSignature(
			&desc,
			D3D_ROOT_SIGNATURE_VERSION_1_0,
			&blob,
			&error
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : SERIALIZE FAILED DIRECT3D12 ROOT SIGNATURE.\n");
			return false;
		}

		hResult = CD3D12Device::getInstance()->CreateRootSignature(
			0U,
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			__uuidof(m_signature),
			reinterpret_cast<void**>(&m_signature)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED DIRECT3D12 ROOT SIGNATURE.\n");
			return false;
		}

		return true;
	}

	void CD3D12RootSignature::exit() noexcept {
		safe_release(m_signature);
	}

	ID3D12RootSignature* CD3D12RootSignature::get() const noexcept {
		return m_signature;
	}

	ID3D12RootSignature* CD3D12RootSignature::operator->() const noexcept {
		return m_signature;
	}
}