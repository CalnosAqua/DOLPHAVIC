/**	@file	CD3D12Shader.cpp
 *	@brief	シェーダ
 */
#include "d3d12/CD3D12Shader.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	CD3D12Shader::CD3D12Shader(CD3D12Shader&& arg) noexcept :
		CD3D12Shader()
	{
		m_shader = arg.m_shader;
		arg.m_shader = nullptr;
	}

	CD3D12Shader& CD3D12Shader::operator=(CD3D12Shader&& rhs) noexcept {
		exit();

		m_shader = rhs.m_shader;
		rhs.m_shader = nullptr;

		return *this;
	}

	CD3D12Shader::CD3D12Shader() noexcept :
		INoncopyable(),
		m_shader(nullptr)
	{}

	CD3D12Shader::~CD3D12Shader() noexcept {
		exit();
	}

	bool const CD3D12Shader::init(LPCWSTR const& path) noexcept {
		HRESULT hResult = D3DReadFileToBlob(path, &m_shader);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : READING FAILED SHADER FILE.\n");
			return false;
		}
		return true;
	}

	void CD3D12Shader::exit() noexcept {
		safe_release(m_shader);
	}

	D3D12_SHADER_BYTECODE const CD3D12Shader::get() const noexcept {
		D3D12_SHADER_BYTECODE result;
		result.pShaderBytecode = m_shader->GetBufferPointer();
		result.BytecodeLength = m_shader->GetBufferSize();
		return result;
	}
}