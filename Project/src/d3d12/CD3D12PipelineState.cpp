/**	@file	CD3D12PipelineState.hpp
 *	@brief	パイプラインステート
 */
#include "d3d12/CD3D12PipelineState.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	//!	@brief	ムーブコンストラクタ
	CD3D12PipelineState::CD3D12PipelineState(CD3D12PipelineState&& arg) noexcept :
		CD3D12PipelineState()
	{
		m_state = arg.m_state;
		arg.m_state = nullptr;
	}

	//!	@brief	ムーブ代入演算子
	CD3D12PipelineState& CD3D12PipelineState::operator=(CD3D12PipelineState&& rhs) noexcept {
		exit();
		m_state = rhs.m_state;
		rhs.m_state = nullptr;
		return *this;
	}

	CD3D12PipelineState::CD3D12PipelineState() noexcept :
		m_state(nullptr)
	{}

	CD3D12PipelineState::~CD3D12PipelineState() noexcept {
		exit();
	}

	bool const CD3D12PipelineState::init(SPSODesc const& arg) noexcept {
		HRESULT hResult = S_OK;

		D3D12_RASTERIZER_DESC raster = {};
		raster.FillMode = D3D12_FILL_MODE_SOLID;
		raster.CullMode = D3D12_CULL_MODE_NONE;
		raster.FrontCounterClockwise = false;
		raster.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		raster.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		raster.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		raster.DepthClipEnable = false;
		raster.MultisampleEnable = false;
		raster.AntialiasedLineEnable = false;
		raster.ForcedSampleCount = 0U;
		raster.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

		D3D12_RENDER_TARGET_BLEND_DESC rtblend = {};
		rtblend.BlendEnable = false;
		rtblend.LogicOpEnable = false;
		rtblend.SrcBlend = rtblend.SrcBlendAlpha = D3D12_BLEND_ONE;
		rtblend.DestBlend = rtblend.DestBlendAlpha = D3D12_BLEND_ZERO;
		rtblend.BlendOp = rtblend.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		rtblend.LogicOp = D3D12_LOGIC_OP_NOOP;
		rtblend.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		D3D12_BLEND_DESC blend = {};
		blend.AlphaToCoverageEnable = false;
		blend.IndependentBlendEnable = false;
		for (unsigned int idx = 0U; idx < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++idx) {
			blend.RenderTarget[idx] = rtblend;
		}
		
		D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
		desc.InputLayout.pInputElementDescs = arg.il->getAddress();
		desc.InputLayout.NumElements = static_cast<UINT>(arg.il->getCount());
		desc.pRootSignature = arg.rs->get();
		desc.VS = arg.vs;
		desc.PS = arg.ps;
		desc.RasterizerState = raster;
		desc.BlendState = blend;
		desc.SampleMask = UINT_MAX;
		desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		desc.NumRenderTargets = 1;
		desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		if (arg.ds) {
			desc.DepthStencilState.DepthEnable = true;
			desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			desc.DepthStencilState.StencilEnable = false;
			desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		}
		else {
			desc.DepthStencilState.DepthEnable = false;
			desc.DepthStencilState.StencilEnable = false;
			desc.DSVFormat = DXGI_FORMAT_UNKNOWN;
		}

		hResult = CD3D12Device::getInstance()->CreateGraphicsPipelineState(
			&desc,
			__uuidof(m_state),
			reinterpret_cast<void**>(&m_state)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED DIRECT3D12 PIPELINE STATE.\n");
			return false;
		}

		return true;
	}

	void CD3D12PipelineState::exit() noexcept {
		safe_release(m_state);
	}

	ID3D12PipelineState* CD3D12PipelineState::get() const noexcept {
		return m_state;
	}

	ID3D12PipelineState* CD3D12PipelineState::operator->() const noexcept {
		return m_state;
	}
}